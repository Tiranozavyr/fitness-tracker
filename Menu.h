#ifndef MENU_H
#define MENU_H

#include "UserProfile.h"
#include "CardioExercise.h"
#include "StrengthExercise.h"
#include "Workout.h"
#include "Goal.h"
#include <iostream>
#include <string>

using namespace std;

static void clearInput()
{
    cin.ignore(1, '\n');
}

static void menuAddExercise(Workout &workout)
{
    cout << "  Тип (1=Кардио, 2=Силово): ";
    int type;
    cin >> type;
    clearInput();

    cout << "  Име на упражнението: ";
    string name;
    getline(cin, name);

    cout << "  Описание: ";
    string desc;
    getline(cin, desc);

    if (type == 1)
    {
        cout << "  Продължителност (мин): ";
        double dur;
        cin >> dur;

        cout << "  Дистанция (км): ";
        double dist;
        cin >> dist;
        clearInput();

        workout.addExercise(new CardioExercise(name, desc, dur, dist));
        cout << "  Кардио упражнението е добавено.\n";
    }
    else
    {
        StrengthExercise *se = new StrengthExercise(name, desc);

        int setNum = 1;
        while (true)
        {
            cout << "  Серия " << setNum << " - повторения (0 за край): ";
            int reps;
            cin >> reps;
            if (reps == 0) { clearInput(); break; }

            cout << "  Серия " << setNum << " - тежест (кг): ";
            double weight;
            cin >> weight;
            clearInput();

            se->addSet(Set(reps, weight));
            setNum++;
        }

        workout.addExercise(se);
        cout << "  Силовото упражнение е добавено.\n";
    }
}

static void menuAddWorkout(UserProfile &profile)
{
    cout << "\nДата на тренировката (напр. 2026-W22-Monday): ";
    string date;
    getline(cin, date);

    cout << "Бележки (Enter за пропускане): ";
    string notes;
    getline(cin, notes);

    Workout workout(date, notes);

    while (true)
    {
        cout << "\nДобави упражнение? (1=Да, 0=Край): ";
        int choice;
        cin >> choice;
        clearInput();
        if (choice == 0) break;
        menuAddExercise(workout);
    }

    profile.addWorkout(workout);
    cout << "Тренировката е записана!\n";
}

static void menuAddGoal(UserProfile &profile)
{
    cout << "\nТип цел (1=тренировки, 2=калории, 3=обем): ";
    int typeChoice;
    cin >> typeChoice;
    clearInput();

    string type;
    if (typeChoice == 1) type = "workouts";
    else if (typeChoice == 2) type = "calories";
    else type = "volume";

    cout << "Целева стойност: ";
    double target;
    cin >> target;
    clearInput();

    cout << "Седмица (трябва да съвпада с датите на тренировките, напр. 2026-W22): ";
    string deadline;
    getline(cin, deadline);

    profile.addGoal(Goal(type, target, deadline));
    cout << "Целта е добавена!\n";
}

static void menuViewWeeklySummary(const UserProfile &profile)
{
    cout << "\nСедмица (напр. 2026-W22): ";
    string week;
    getline(cin, week);
    cout << "\n" << profile.getWeeklySummary(week) << "\n";
}

static void menuViewProgress(const UserProfile &profile)
{
    cout << "\nИме на упражнение: ";
    string name;
    getline(cin, name);
    cout << "\n" << profile.getExerciseProgress(name) << "\n";
}

static void menuViewPR(const UserProfile &profile)
{
    cout << "\nИме на упражнение: ";
    string name;
    getline(cin, name);
    double pr = profile.getPersonalRecord(name);
    if (pr == 0)
        cout << "Няма данни за \"" << name << "\".\n";
    else
        cout << "Личен рекорд за \"" << name << "\": " << pr << " кг\n";
}

static void menuComparePeriods(const UserProfile &profile)
{
    cout << "\nПърва седмица (напр. 2026-W21): ";
    string w1;
    getline(cin, w1);

    cout << "Втора седмица (напр. 2026-W22): ";
    string w2;
    getline(cin, w2);

    cout << "\n" << profile.comparePeriods(w1, w2) << "\n";
}

static void menuViewGoals(const UserProfile &profile)
{
    const vector<Goal> &goals = profile.getGoals();
    if (goals.empty())
    {
        cout << "Няма зададени цели.\n";
        return;
    }
    cout << "\n=== Цели ===\n";
    for (size_t i = 0; i < goals.size(); i++)
    {
        double progress = goals[i].getProgress(profile);
        cout << i + 1 << ". Тип: " << goals[i].getType()
             << " | Цел: " << goals[i].getTarget()
             << " | Срок: " << goals[i].getDeadline()
             << " | Прогрес: " << progress << "%"
             << " | " << (goals[i].isCompleted(profile) ? "ИЗПЪЛНЕНА" : "В процес");
        if (progress == 0)
            cout << "  (няма тренировки за седмица \"" << goals[i].getDeadline() << "\")";
        cout << "\n";
    }
}

#endif // MENU_H
