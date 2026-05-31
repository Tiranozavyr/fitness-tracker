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

    void setReps(int r) { reps = r; }
    void setWeight(double w) { weightKg = w; }
    void setIsPR(bool val) { isPersonalRecord = val; }

    int getReps() const { return reps; }
    double getWeight() const { return weightKg; }
    bool getIsPR() const { return isPersonalRecord; }
};

#endif // SET_H
