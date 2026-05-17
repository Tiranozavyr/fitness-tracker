#include <iostream>
#include <windows.h>
#include "CardioExercise.h"
#include "StrengthExercise.h"
#include "Workout.h"
#include "UserProfile.h"
#include "Goal.h"
using namespace std;

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    cout << "=== Фитнес Тракер ===" << endl
         << endl;

    // --- Функционалност 1: Управление на упражнения ---
    CardioExercise run("Бягане", "Утрин", 30, 5.0);
    CardioExercise bike("Колело", "Зала", 45, 15.0);
    StrengthExercise bench("Bench Press", "Гърди");
    StrengthExercise squat("Клек", "Крака");

    cout << "-- Упражнения --" << endl;
    cout << run.getSummary() << endl;
    cout << bike.getSummary() << endl
         << endl;

    // --- Функционалност 3: Личен рекорд ---
    bench.addSet(8, 60.0);
    bench.addSet(6, 70.0); // PR!
    bench.addSet(4, 75.0); // PR!

    squat.addSet(5, 80.0);
    squat.addSet(5, 90.0); // PR!

    cout << "-- Силови упражнения с PR засичане --" << endl;
    cout << bench.getSummary() << endl;
    cout << squat.getSummary() << endl;

    // --- Функционалност 2: Записване на тренировки ---
    Workout w1("2025-W20-Monday", "Сутрешна тренировка");
    w1.addExercise(&run);
    w1.addExercise(&bench);

    Workout w2("2025-W20-Wednesday", "Обедна тренировка");
    w2.addExercise(&bike);
    w2.addExercise(&squat);

    Workout w3("2025-W21-Monday", "Следваща седмица");
    w3.addExercise(&run);

    // --- Функционалност 6: Потребителски профил ---
    UserProfile ivan("Иван");
    ivan.addWorkout(w1);
    ivan.addWorkout(w2);
    ivan.addWorkout(w3);

    // --- Функционалност 7: Цели ---
    Goal g1("workouts", 3, "2025-W20");
    Goal g2("calories", 500, "2025-W20");
    ivan.addGoal(g1);
    ivan.addGoal(g2);

    cout << "-- Цели --" << endl;
    cout << "Цел: " << g1.getTarget() << " тренировки до " << g1.getDeadline() << endl;
    cout << "Цел: " << g2.getTarget() << " калории до " << g2.getDeadline() << endl
         << endl;

    // --- Функционалност 5: Седмично обобщение ---
    cout << "-- Седмично обобщение --" << endl;
    cout << ivan.getWeeklySummary("2025-W20") << endl
         << endl;

    // --- Функционалност 4: Личен рекорд по упражнение ---
    cout << "-- Личен рекорд --" << endl;
    cout << "PR за Bench Press: " << ivan.getPersonalRecord("Bench Press") << " кг" << endl;
    cout << "PR за Клек: " << ivan.getPersonalRecord("Клек") << " кг" << endl
         << endl;

    // --- Функционалност 9: Сравнение на периоди ---
    cout << "-- Сравнение на периоди --" << endl;
    cout << ivan.comparePeriods("2025-W20", "2025-W21") << endl;

    return 0;
}