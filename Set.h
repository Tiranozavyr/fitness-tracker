#ifndef SET_H
#define SET_H

class Set
{
private:
    int reps;
    double weightKg;
    bool isPersonalRecord;

public:
    Set(int reps, double weightKg)
        : reps(reps), weightKg(weightKg), isPersonalRecord(false) {}

    int getReps() const { return reps; }
    double getWeight() const { return weightKg; }
    bool getIsPR() const { return isPersonalRecord; }
    void setIsPR(bool val) { isPersonalRecord = val; }
};

#endif // SET_H