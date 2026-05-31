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

    void setName(const string &n) { name = n; }
    void setDescription(const string &d) { description = d; }

    string getName() const { return name; }
    string getDescription() const { return description; }

    virtual double getCalories() const = 0;
    virtual string getSummary() const = 0;
    virtual double getVolume() const { return 0.0; }
    virtual Exercise* clone() const = 0;
};

#endif // EXERCISE_H
