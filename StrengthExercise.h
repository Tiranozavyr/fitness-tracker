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

    vector<Set> getSets() const { return sets; }

    void addSet(int reps, double weight)
    {
        Set s(reps, weight);

        double maxSoFar = 0;
        for (int i = 0; i < sets.size(); i++)
        {
            if (sets[i].getWeight() > maxSoFar)
                maxSoFar = sets[i].getWeight();
        }

        if (weight > maxSoFar)
        {
            s.setIsPR(true);
        }

        sets.push_back(s);
    }

    double getMaxWeight()
    {
        double max = 0;
        for (int i = 0; i < sets.size(); i++)
        {
            if (sets[i].getWeight() > max)
                max = sets[i].getWeight();
        }
        return max;
    }

    double getCalories() const override
    {
        double total = 0;
        for (int i = 0; i < sets.size(); i++)
        {
            total += sets[i].getWeight() * sets[i].getReps();
        }
        return total * 0.1;
    }

    string getSummary() const override
    {
        string result = "Силово: " + name + "\n";
        for (int i = 0; i < sets.size(); i++)
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