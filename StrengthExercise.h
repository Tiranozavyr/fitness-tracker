#ifndef STRENGTH_H
#define STRENGTH_H

#include "Exercise.h"
#include "Set.h"
#include <vector>

class StrengthExercise : public Exercise
{
private:
    vector<Set> sets;

public:
    StrengthExercise(const string &n, const string &d) : Exercise(n, d) {}

    void addSet(Set s)
    {
        double maxSoFar = 0;
        for (size_t i = 0; i < sets.size(); i++)
        {
            if (sets[i].getWeight() > maxSoFar)
                maxSoFar = sets[i].getWeight();
        }

        if (!sets.empty() && s.getWeight() > maxSoFar)
        {
            s.setIsPR(true);
        }

        sets.push_back(s);
    }

    vector<Set> &getSets() { return sets; }
    const vector<Set> &getSets() const { return sets; }

    double getVolume() const override
    {
        double vol = 0;
        for (size_t i = 0; i < sets.size(); i++)
        {
            vol += sets[i].getWeight() * sets[i].getReps();
        }
        return vol;
    }

    double getMaxWeight() const
    {
        double max = 0;
        for (size_t i = 0; i < sets.size(); i++)
        {
            if (sets[i].getWeight() > max)
                max = sets[i].getWeight();
        }
        return max;
    }

    double getCalories() const override
    {
        double total = 0;
        for (size_t i = 0; i < sets.size(); i++)
        {
            total += sets[i].getWeight() * sets[i].getReps();
        }
        return total * 0.1;
    }

    Exercise* clone() const override { return new StrengthExercise(*this); }

    string getSummary() const override
    {
        string result = "Силово: " + name + "\n";
        for (size_t i = 0; i < sets.size(); i++)
        {
            result += "  Серия " + to_string(i + 1) + ": ";
            result += to_string(sets[i].getReps()) + " повт x ";
            result += to_string((int)sets[i].getWeight()) + " кг";
            if (sets[i].getIsPR())
                result += "  <-- ЛИЧЕН РЕКОРД!";
            result += "\n";
        }
        result += "  Калории: ~" + to_string((int)getCalories());
        return result;
    }
};

#endif // STRENGTH_H
