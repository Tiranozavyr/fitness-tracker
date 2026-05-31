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
        : date(d), notes(n) {}

    Workout(const Workout &other) : date(other.date), notes(other.notes)
    {
        for (size_t i = 0; i < other.exercises.size(); i++)
            exercises.push_back(other.exercises[i]->clone());
    }

    Workout &operator=(const Workout &other)
    {
        if (this == &other) return *this;
        for (size_t i = 0; i < exercises.size(); i++)
            delete exercises[i];
        exercises.clear();
        date = other.date;
        notes = other.notes;
        for (size_t i = 0; i < other.exercises.size(); i++)
            exercises.push_back(other.exercises[i]->clone());
        return *this;
    }

    void addExercise(Exercise *ex)
    {
        exercises.push_back(ex);
    }

    string getDate() const { return date; }
    string getNotes() const { return notes; }
    vector<Exercise *> getExercises() const { return exercises; }

    ~Workout()
    {
        for (size_t i = 0; i < exercises.size(); i++)
            delete exercises[i];
    }

    double getTotalCalories() const
    {
        double total = 0;
        for (size_t i = 0; i < exercises.size(); i++)
        {
            total += exercises[i]->getCalories();
        }
        return total;
    }

    double getTotalVolume() const
    {
        double total = 0;
        for (size_t i = 0; i < exercises.size(); i++)
        {
            total += exercises[i]->getVolume();
        }
        return total;
    }

    string getSummary() const
    {
        string result = "Тренировка: " + date + "\n";
        for (size_t i = 0; i < exercises.size(); i++)
        {
            result += exercises[i]->getSummary() + "\n";
        }
        result += "Общо калории: ~" + to_string((int)getTotalCalories());
        return result;
    }
};

#endif // WORKOUT_H
