#include <iostream>
#include <string>
#include <windows.h>
#include "UserProfile.h"
#include "Storage.h"
#include "Menu.h"

using namespace std;

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    cout << "=== Фитнес Тракер ===" << endl;
    cout << "Вашето име: ";
    string userName;
    getline(cin, userName);

    string filename = userName + ".txt";
    UserProfile profile = loadProfile(filename, userName);

    cout << "Здравей, " << profile.getName() << "!\n";

    int choice;
    do
    {
        cout << "\n--- Меню ---\n";
        cout << "1. Добави тренировка\n";
        cout << "2. Добави цел\n";
        cout << "3. Седмично обобщение\n";
        cout << "4. Прогрес на упражнение\n";
        cout << "5. Личен рекорд\n";
        cout << "6. Сравнение на периоди\n";
        cout << "7. Всички цели\n";
        cout << "0. Изход\n";
        cout << "Избор: ";
        cin >> choice;
        clearInput();

        switch (choice)
        {
        case 1: menuAddWorkout(profile);          break;
        case 2: menuAddGoal(profile);             break;
        case 3: menuViewWeeklySummary(profile);   break;
        case 4: menuViewProgress(profile);        break;
        case 5: menuViewPR(profile);              break;
        case 6: menuComparePeriods(profile);      break;
        case 7: menuViewGoals(profile);           break;
        case 0: break;
        default: cout << "Невалиден избор.\n";
        }
    } while (choice != 0);

    saveProfile(profile, filename);
    cout << "Данните са записани. Довиждане!\n";

    return 0;
}
