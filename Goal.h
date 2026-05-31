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
    Goal(const string &t, double val, const string &d)
    {
        type = t;
        targetValue = val;
        deadline = d;
    }

    string getType() const { return type; }
    double getTarget() const { return targetValue; }
    string getDeadline() const { return deadline; }
};

#endif // GOAL_H