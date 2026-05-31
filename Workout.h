#ifndef WORKOUT_H
#define WORKOUT_H

#include "Exercise.h"
#include <vector>
#include <string>

class Workout
{
private:
    string date;
    string notes;
    vector<Exercise *> exercises;

public:
    Workout(const string &d, const string &n = "")
    {
        date = d;
        notes = n;
    }

    string getDate() const { return date; }
    string getNotes() const { return notes; }
    vector<Exercise *> getExercises() const { return exercises; }

    void addExercise(Exercise *ex)
    {
        exercises.push_back(ex);
    }

    double getTotalCalories() const
    {
        double total = 0;
        for (int i = 0; i < exercises.size(); i++)
        {
            total += exercises[i]->getCalories();
        }
        return total;
    }

    string getSummary() const
    {
        string result = "Тренировка: " + date + "\n";
        for (int i = 0; i < exercises.size(); i++)
        {
            result += exercises[i]->getSummary() + "\n";
        }
        result += "Общо калории: ~" + to_string((int)getTotalCalories());
        return result;
    }
};

#endif // WORKOUT_H