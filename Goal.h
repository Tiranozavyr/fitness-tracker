#ifndef GOAL_H
#define GOAL_H

#include <string>
using namespace std;

class Goal
{
private:
    string type;
    double targetValue;
    string deadline;

public:
    Goal(string t, double val, string d)
    {
        type = t;
        targetValue = val;
        deadline = d;
    }

    string getType() { return type; }
    double getTarget() { return targetValue; }
    string getDeadline() { return deadline; }
};

#endif // GOAL_H