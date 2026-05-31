#ifndef GOAL_H
#define GOAL_H

#include <string>

class Goal
{
private:
    std::string type;
    double targetValue;
    std::string deadline;

public:
    Goal(const std::string& t, double val, const std::string& d)
    {
        type = t;
        targetValue = val;
        deadline = d;
    }

    std::string getType() const { return type; }
    double getTarget() const { return targetValue; }
    std::string getDeadline() const { return deadline; }
};

#endif // GOAL_H