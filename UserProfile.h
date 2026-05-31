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
    UserProfile(const string &n) : name(n) {}

    void addWorkout(Workout w)
    {
        vector<Exercise *> incoming = w.getExercises();
        for (size_t j = 0; j < incoming.size(); j++)
        {
            StrengthExercise *se = dynamic_cast<StrengthExercise *>(incoming[j]);
            if (se == nullptr)
                continue;

            double histMax = 0;
            for (size_t i = 0; i < workouts.size(); i++)
            {
                vector<Exercise *> exs = workouts[i].getExercises();
                for (size_t k = 0; k < exs.size(); k++)
                {
                    if (exs[k]->getName() == se->getName())
                    {
                        StrengthExercise *prev = dynamic_cast<StrengthExercise *>(exs[k]);
                        if (prev && prev->getMaxWeight() > histMax)
                            histMax = prev->getMaxWeight();
                    }
                }
            }

            double runningMax = histMax;
            vector<Set> &sets = se->getSets();
            for (size_t s = 0; s < sets.size(); s++)
            {
                if (sets[s].getWeight() > runningMax)
                {
                    sets[s].setIsPR(true);
                    runningMax = sets[s].getWeight();
                }
                else
                {
                    sets[s].setIsPR(false);
                }
            }
        }

        workouts.push_back(w);
    }

    void addGoal(Goal g)
    {
        goals.push_back(g);
    }

    string getName() const { return name; }
    vector<Workout> getWorkouts() const { return workouts; }
    vector<Goal> getGoals() const { return goals; }

    string getWeeklySummary(const string &week) const
    {
        string result = "=== Седмица " + week + " ===\n";
        int count = 0;
        double totalCal = 0;
        double totalVol = 0;

        for (size_t i = 0; i < workouts.size(); i++)
        {
            if (workouts[i].getDate().find(week) != string::npos)
            {
                count++;
                totalCal += workouts[i].getTotalCalories();
                totalVol += workouts[i].getTotalVolume();
                result += workouts[i].getSummary() + "\n";
            }
        }

        result += "Брой тренировки: " + to_string(count) + "\n";
        result += "Общо калории: ~" + to_string((int)totalCal) + "\n";
        result += "Общ обем: " + to_string((int)totalVol) + " кг";
        return result;
    }

    double getPersonalRecord(const string &exerciseName) const
    {
        double maxPR = 0;
        for (size_t i = 0; i < workouts.size(); i++)
        {
            vector<Exercise *> exs = workouts[i].getExercises();
            for (size_t j = 0; j < exs.size(); j++)
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

    string getExerciseProgress(const string &exerciseName) const
    {
        string result = "=== Прогрес за " + exerciseName + " ===\n";
        bool found = false;

        for (size_t i = 0; i < workouts.size(); i++)
        {
            vector<Exercise *> exs = workouts[i].getExercises();
            for (size_t j = 0; j < exs.size(); j++)
            {
                if (exs[j]->getName() == exerciseName)
                {
                    found = true;
                    result += "Дата: " + workouts[i].getDate() + " | ";
                    StrengthExercise *se = dynamic_cast<StrengthExercise *>(exs[j]);
                    if (se != nullptr)
                    {
                        result += "Макс. тежест: " + to_string((int)se->getMaxWeight()) + " кг. | ";
                        result += "Общ обем: " + to_string((int)se->getVolume()) + " кг.\n";
                    }
                    else
                    {
                        result += "Калории: ~" + to_string((int)exs[j]->getCalories()) + " кал.\n";
                    }
                }
            }
        }
        if (!found)
            result += "Няма данни.\n";
        return result;
    }

    string comparePeriods(const string &week1, const string &week2) const
    {
        int count1 = 0, count2 = 0;
        double cal1 = 0, cal2 = 0;
        double vol1 = 0, vol2 = 0;

        for (size_t i = 0; i < workouts.size(); i++)
        {
            if (workouts[i].getDate().find(week1) != string::npos)
            {
                count1++;
                cal1 += workouts[i].getTotalCalories();
                vol1 += workouts[i].getTotalVolume();
            }
            if (workouts[i].getDate().find(week2) != string::npos)
            {
                count2++;
                cal2 += workouts[i].getTotalCalories();
                vol2 += workouts[i].getTotalVolume();
            }
        }

        string result = "=== Сравнение: " + week1 + " vs " + week2 + " ===\n";
        result += week1 + ": " + to_string(count1) + " тренировки, ~" + to_string((int)cal1) + " кал, " + to_string((int)vol1) + " кг обем\n";
        result += week2 + ": " + to_string(count2) + " тренировки, ~" + to_string((int)cal2) + " кал, " + to_string((int)vol2) + " кг обем\n";

        if (cal2 > cal1)
            result += "Подобрение: +" + to_string((int)(cal2 - cal1)) + " кал";
        else if (cal1 > cal2)
            result += "Спад: -" + to_string((int)(cal1 - cal2)) + " кал";
        else
            result += "Без промяна в калориите";

        result += " | ";

        if (vol2 > vol1)
            result += "Подобрение обем: +" + to_string((int)(vol2 - vol1)) + " кг";
        else if (vol1 > vol2)
            result += "Спад обем: -" + to_string((int)(vol1 - vol2)) + " кг";
        else
            result += "Без промяна в обема";

        return result;
    }
};

inline double Goal::getProgress(const UserProfile &profile) const
{
    double current = 0;

    for (const auto &w : profile.getWorkouts())
    {
        if (!deadline.empty() && w.getDate().find(deadline) == string::npos)
            continue;

        if (type == "workouts")
            current += 1;
        else if (type == "calories")
            current += w.getTotalCalories();
        else if (type == "volume")
            current += w.getTotalVolume();
    }

    if (targetValue == 0)
        return 100.0;
    return (current / targetValue) * 100.0;
}

inline bool Goal::isCompleted(const UserProfile &profile) const
{
    return getProgress(profile) >= 100.0;
}

#endif // USERPROFILE_H
