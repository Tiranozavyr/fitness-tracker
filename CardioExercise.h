#ifndef CARDIO_H
#define CARDIO_H

#include "Exercise.h"

class CardioExercise : public Exercise
{
private:
    double durationMin;
    double distanceKm;

public:
    CardioExercise(string n, string d, double dur, double dist)
        : Exercise(n, d)
    {
        durationMin = dur;
        distanceKm = dist;
    }

    double getDuration() { return durationMin; }
    double getDistance() { return distanceKm; }

    double getCalories()
    {
        return durationMin * 8 + distanceKm * 50;
    }

    string getSummary()
    {
        return "Кардио: " + name +
               " | " + to_string((int)durationMin) + " мин" +
               " | " + to_string((int)distanceKm) + " км" +
               " | ~" + to_string((int)getCalories()) + " кал";
    }
};

#endif // CARDIO_H