#ifndef STORAGE_H
#define STORAGE_H

#include "UserProfile.h"
#include "CardioExercise.h"
#include "StrengthExercise.h"
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

void saveProfile(const UserProfile &profile, const string &filename)
{
    ofstream file(filename);

    const vector<Workout> &workouts = profile.getWorkouts();
    for (size_t i = 0; i < workouts.size(); i++)
    {
        const string &date = workouts[i].getDate();
        string notes = workouts[i].getNotes();
        if (notes.empty())
            notes = "-";

        const vector<Exercise *> exs = workouts[i].getExercises();
        for (size_t j = 0; j < exs.size(); j++)
        {
            CardioExercise *ce = dynamic_cast<CardioExercise *>(exs[j]);
            StrengthExercise *se = dynamic_cast<StrengthExercise *>(exs[j]);

            if (ce != nullptr)
            {
                file << "CARDIO,"
                     << date << ","
                     << notes << ","
                     << ce->getName() << ","
                     << ce->getDescription() << ","
                     << ce->getDuration() << ","
                     << ce->getDistance() << "\n";
            }
            else if (se != nullptr)
            {
                file << "STRENGTH,"
                     << date << ","
                     << notes << ","
                     << se->getName() << ","
                     << se->getDescription();

                const vector<Set> &sets = se->getSets();
                for (size_t s = 0; s < sets.size(); s++)
                {
                    file << "," << sets[s].getReps()
                         << "," << sets[s].getWeight();
                }
                file << "\n";
            }
        }
    }

    const vector<Goal> &goals = profile.getGoals();
    for (size_t i = 0; i < goals.size(); i++)
    {
        file << "GOAL,"
             << goals[i].getType() << ","
             << goals[i].getTarget() << ","
             << goals[i].getDeadline() << "\n";
    }
}

UserProfile loadProfile(const string &filename, const string &name)
{
    UserProfile profile(name);
    ifstream file(filename);
    if (!file.is_open())
        return profile;

    string line;
    string currentDate = "";
    string currentNotes = "";
    Workout *currentWorkout = nullptr;
    vector<Exercise *> allocatedExercises;

    auto flushWorkout = [&]()
    {
        if (currentWorkout != nullptr)
        {
            profile.addWorkout(*currentWorkout);
            delete currentWorkout;
            currentWorkout = nullptr;
        }
    };

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        istringstream ss(line);
        string tag;
        getline(ss, tag, ',');

        if (tag == "CARDIO")
        {
            string date, notes, exName, desc, durStr, distStr;
            getline(ss, date, ',');
            getline(ss, notes, ',');
            getline(ss, exName, ',');
            getline(ss, desc, ',');
            getline(ss, durStr, ',');
            getline(ss, distStr, ',');

            if (notes == "-")
                notes = "";

            if (date != currentDate || notes != currentNotes)
            {
                flushWorkout();
                currentDate = date;
                currentNotes = notes;
                currentWorkout = new Workout(date, notes);
            }

            CardioExercise *ce = new CardioExercise(
                exName, desc, stod(durStr), stod(distStr));
            allocatedExercises.push_back(ce);
            currentWorkout->addExercise(ce);
        }
        else if (tag == "STRENGTH")
        {
            string date, notes, exName, desc;
            getline(ss, date, ',');
            getline(ss, notes, ',');
            getline(ss, exName, ',');
            getline(ss, desc, ',');

            if (notes == "-")
                notes = "";

            if (date != currentDate || notes != currentNotes)
            {
                flushWorkout();
                currentDate = date;
                currentNotes = notes;
                currentWorkout = new Workout(date, notes);
            }

            StrengthExercise *se = new StrengthExercise(exName, desc);
            allocatedExercises.push_back(se);

            string repsStr, weightStr;
            while (getline(ss, repsStr, ',') && getline(ss, weightStr, ','))
            {
                se->addSet(Set(stoi(repsStr), stod(weightStr)));
            }

            currentWorkout->addExercise(se);
        }
        else if (tag == "GOAL")
        {
            flushWorkout();

            string type, targetStr, deadline;
            getline(ss, type, ',');
            getline(ss, targetStr, ',');
            getline(ss, deadline, ',');

            profile.addGoal(Goal(type, stod(targetStr), deadline));
        }
    }

    flushWorkout();
    return profile;
}

#endif // STORAGE_H
