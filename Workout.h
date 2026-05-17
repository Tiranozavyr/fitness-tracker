#ifndef WORKOUT_H
#define WORKOUT_H

#include "Exercise.h"
#include <vector>
#include <string>
using namespace std;

class Workout
{
private:
    string date;
    string notes;
    vector<Exercise *> exercises;

public:
    Workout(string d, string n = "")
    {
        date = d;
        notes = n;
    }

    string getDate() { return date; }
    string getNotes() { return notes; }
    vector<Exercise *> getExercises() { return exercises; }

    void addExercise(Exercise *ex)
    {
        exercises.push_back(ex);
    }

    double getTotalCalories()
    {
        double total = 0;
        for (int i = 0; i < exercises.size(); i++)
        {
            total += exercises[i]->getCalories();
        }
        return total;
    }

    string getSummary()
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