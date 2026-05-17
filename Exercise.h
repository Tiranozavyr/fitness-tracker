#ifndef EXERCISE_H
#define EXERCISE_H

#include <string>
using namespace std;

class Exercise
{
protected:
    string name;
    string description;

public:
    Exercise(const string &name, const string &desc)
        : name(name), description(desc) {}

    virtual ~Exercise() = default;

    string getName() const { return name; }
    string getDescription() const { return description; }

    virtual double getCalories() const = 0;
    virtual string getSummary() const = 0;
};

#endif // EXERCISE_H