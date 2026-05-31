#ifndef USERPROFILE_H
#define USERPROFILE_H

#include "Workout.h"
#include "Goal.h"
#include "StrengthExercise.h"
#include <vector>
#include <string>

class UserProfile
{
private:
    string name;
    vector<Workout> workouts;
    vector<Goal> goals;

public:
    UserProfile(const string &n)
    {
        name = n;
    }

    string getName() const { return name; }
    vector<Workout> getWorkouts() const { return workouts; }
    vector<Goal> getGoals() const { return goals; }

    void addWorkout(Workout w)
    {
        workouts.push_back(w);
    }

    void addGoal(Goal g)
    {
        goals.push_back(g);
    }

    string getWeeklySummary(const string &week) const
    {
        string result = "=== Седмица " + week + " ===\n";
        int count = 0;
        double totalCal = 0;

        for (int i = 0; i < workouts.size(); i++)
        {
            if (workouts[i].getDate().find(week) != string::npos)
            {
                count++;
                totalCal += workouts[i].getTotalCalories();
                result += workouts[i].getSummary() + "\n";
            }
        }

        result += "Брой тренировки: " + to_string(count) + "\n";
        result += "Общо калории: ~" + to_string((int)totalCal);
        return result;
    }

    double getPersonalRecord(const string &exerciseName) const
    {
        double maxPR = 0;
        for (int i = 0; i < workouts.size(); i++)
        {
            vector<Exercise *> exs = workouts[i].getExercises();
            for (int j = 0; j < exs.size(); j++)
            {
                if (exs[j]->getName() == exerciseName)
                {
                    StrengthExercise *se = dynamic_cast<StrengthExercise *>(exs[j]);
                    if (se != nullptr && se->getMaxWeight() > maxPR)
                    {
                        maxPR = se->getMaxWeight();
                    }
                }
            }
        }
        return maxPR;
    }

    string comparePeriods(const string &week1, const string &week2) const
    {
        int count1 = 0, count2 = 0;
        double cal1 = 0, cal2 = 0;

        for (int i = 0; i < workouts.size(); i++)
        {
            if (workouts[i].getDate().find(week1) != string::npos)
            {
                count1++;
                cal1 += workouts[i].getTotalCalories();
            }
            if (workouts[i].getDate().find(week2) != string::npos)
            {
                count2++;
                cal2 += workouts[i].getTotalCalories();
            }
        }

        string result = "=== Сравнение: " + week1 + " vs " + week2 + " ===\n";
        result += week1 + ": " + to_string(count1) + " тренировки, ~" + to_string((int)cal1) + " кал\n";
        result += week2 + ": " + to_string(count2) + " тренировки, ~" + to_string((int)cal2) + " кал\n";

        if (cal2 > cal1)
            result += "Подобрение: +" + to_string((int)(cal2 - cal1)) + " кал";
        else if (cal1 > cal2)
            result += "Спад: -" + to_string((int)(cal1 - cal2)) + " кал";
        else
            result += "Без промяна";

        return result;
    }
};

#endif // USERPROFILE_H