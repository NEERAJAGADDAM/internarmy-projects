#include <iostream>
#include <iomanip>
#include <conio.h>
#include <time.h>
#include <vector>
#include <algorithm> 

using namespace std;

struct Event {
    int day;
    int month;
    int year;
    string description;
};

struct Reminder {
    int day;
    int month;
    int year;
    string description;
};
struct Task {
    int day;
    int month;
    int year;
    int hour;
    int minute;
    string description;
};

class Calendar {
private:
    vector<Event> events;
    vector<Reminder> reminders;
    vector<Task> tasks;

public:
    void addEvent(int day, int month, int year, const string& description) {
        Event newEvent = {day, month, year, description};
        events.push_back(newEvent);
    }
    
     void editEvent(int index, int day, int month, int year, const string& description) {
        if (index >= 0 && index < events.size()) {
            events[index] = {day, month, year, description};
            cout << "Event edited successfully!" << endl;
        } else {
            cout << "Invalid Event!" << endl;
        }
    }

    void deleteEvent(int index) {
        if (index >= 0 && index < events.size()) {
            events.erase(events.begin() + index);
            cout << "Event deleted successfully!" << endl;
        } else {
            cout << "Invalid Event!" << endl;
        }
    }

    void printEventsOnDate(int day, int month, int year) {
        for (const auto& event : events) {
            if (event.day == day && event.month == month && event.year == year) {
                cout << "Event on " << day << "/" << month << "/" << year << ": " << event.description << endl;
                return;
            }
        }
    }

    void setReminder(int day, int month, int year, const string& description) {
        auto it = find_if(reminders.begin(), reminders.end(),
                          [day, month, year](const Reminder& r) { return r.day == day && r.month == month && r.year == year; });

        if (it == reminders.end()) {
            Reminder newReminder = {day, month, year, description};
            reminders.push_back(newReminder);
            cout << "Reminder set successfully!" << endl;
        } else {
            cout << "Reminder already exists for this date and month with year." << endl;
        }
    }
    
     void editReminder(int index, int day, int month, int year, const string& description) {
        if (index >= 0 && index < reminders.size()) {
            reminders[index] = {day, month, year, description};
            cout << "Reminder edited successfully!" << endl;
        } else {
            cout << "Invalid reminder!" << endl;
        }
    }

    void deleteReminder(int index) {
        if (index >= 0 && index < reminders.size()) {
            reminders.erase(reminders.begin() + index);
            cout << "Reminder deleted successfully!" << endl;
        } else {
            cout << "Invalid  reminder!" << endl;
        }
    }

    void printRemindersOnDate(int day, int month, int year) {
        auto it = find_if(reminders.begin(), reminders.end(),
                          [day, month, year](const Reminder& r) { return r.day == day && r.month == month && r.year == year; });

        if (it != reminders.end()) {
            cout << "Reminder on " << day << "/" << month << "/" << year << ": " << it->description << endl;
        }
    }
      void addTask(int day, int month, int year, int hour, int minute, const string& description) {
        Task newTask = {day, month, year, hour, minute, description};
        tasks.push_back(newTask);
        cout << "Task added successfully!" << endl;
    }

    void editTask(int index, int day, int month, int year, int hour, int minute, const string& description) {
        if (index >= 0 && index < tasks.size()) {
            tasks[index] = {day, month, year, hour, minute, description};
            cout << "Task edited successfully!" << endl;
        } else {
            cout << "Invalid task index!" << endl;
        }
    }

    void deleteTask(int index) {
        if (index >= 0 && index < tasks.size()) {
            tasks.erase(tasks.begin() + index);
            cout << "Task deleted successfully!" << endl;
        } else {
            cout << "Invalid task index!" << endl;
        }
    }

    void printTasksOnDate(int day, int month, int year) {
        cout << "Tasks on " << day << "/" << month << "/" << year << ":" << endl;

        for (const auto& task : tasks) {
            if (task.day == day && task.month == month && task.year == year) {
                cout << " - " << setw(2) << setfill('0') << task.hour << ":" << setw(2) << setfill('0') << task.minute
                     << " - " << task.description << endl;
            }
        }
    }
};

void printCalendar(int year, Calendar& myCalendar) {
    int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    int mDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    string monthList[] = {"January", "February", "March", "April", "May",
                           "June", "July", "August", "September", "October",
                           "November", "December"};

    cout << "------------------------------------" << endl;
    cout << "            Welcome to " << year << endl;
    cout << "------------------------------------" << endl;

    int days;
    int current;

    int y = year - 1;
    current = (y + y / 4 - y / 100 + y / 400 + t[0] + 1) % 7;

    for (int i = 0; i < 12; i++) {
        if (i == 1) {
            if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
                days = 29;
            else
                days = mDays[i];
        } else {
            days = mDays[i];
        }

        cout << endl
             << "-------------" << monthList[i] << "--------------" << endl;
        cout << "Sun  Mon  Tue  Wed  Thu  Fri  Sat" << endl;

        int k;
        for (k = 0; k < current; k++) {
            cout <<setw(5) <<" ";
        }
        for (int j = 1; j <= days; j++) {
            cout << setw(5) << j;
            myCalendar.printEventsOnDate(j, i + 1, year);
            myCalendar.printRemindersOnDate(j, i + 1, year);
           
            k++;
            if (k > 6) {
                k = 0;
                cout << endl;
            }
        }

        if (k)
            cout << endl;
        current = k;
    }
}

int main() {
    system("cls");

    time_t ttime = time(0);
    tm* local_time = localtime(&ttime);

    int year = 1900 + local_time->tm_year;
    char option;
    Calendar myCalendar;
    
    printCalendar(year, myCalendar);
    do {
        system("cls");

        cout << endl << endl;
        cout << "Press" << endl;
        cout << "-n for next year" << endl;
        cout << "-p for previous year" << endl;
        cout << "-a to add an event" << endl;
        cout << "1. Edit Event" << endl;
        cout << "2. Delete Event" << endl;
        cout << "3. View Events on a Date" << endl;
        cout << "-r to set a reminder" << endl;
        cout << "4. Edit Reminer" << endl;
        cout << "5. Delete Reminder" << endl;
        cout << "6. View reminders on a Date" << endl;
        cout << "-t. Add Task" << endl;
        cout << "7. Edit Task" << endl;
        cout << "8. Delete Task" << endl;
        cout << "9. View Tasks on a Date" << endl;
        cout << "-e for exit" << endl;
        option = getch();
         int dayEvent, monthEvent, yearEvent;
         string descriptionEvent;

        switch (option) {
            case 'n':
                year++;
                break;
            case 'p':
                year--;
                break;
            case 'a':
                cout << "Enter event details:" << endl;
                cout << "Day: ";
                cin >> dayEvent;

                cout << "Month: ";
                cin >> monthEvent;

                cout << "Year: ";
                cin >> yearEvent;

                cout << "Description: ";
                cin.ignore();
                getline(cin, descriptionEvent);

                myCalendar.addEvent(dayEvent, monthEvent, yearEvent, descriptionEvent);
                myCalendar.printEventsOnDate(dayEvent, monthEvent, yearEvent);
                break;
        
            case '1':
                {
                    int index, day, month, year;
                    string description;

                    cout << "Enter event index to edit: ";
                    cin >> index;

                    cout << "Enter new event details:" << endl;
                    cout << "Day: ";
                    cin >> day;

                    cout << "Month: ";
                    cin >> month;

                    cout << "Year: ";
                    cin >> year;

                    cout << "Description: ";
                    cin.ignore();
                    getline(cin, descriptionEvent);

                    myCalendar.editEvent(index, day, month, year,descriptionEvent);
                }
                break;

            case '2':
                {
                    int index;
                    cout << "Enter Event index to delete: ";
                    cin >> index;
                  myCalendar.deleteEvent(index);
                }
                break;
            case '3':
                {
                    int day, month, year;
                    cout << "Enter date to view events:" << endl;
                    cout << "Day: ";
                    cin >> day;

                    cout << "Month: ";
                    cin >> month;

                    cout << "Year: ";
                    cin >> year;

                    myCalendar.printEventsOnDate(day, month, year);
                }
                break;
            case 'r':
            	{
                int dayReminder, monthReminder, yearReminder;
                string descriptionReminder;
                
                cout << "Enter remainder details:" << endl;
                cout << "Day: ";
                cin >> dayReminder;

                cout << "Month: ";
                cin >> monthReminder;

                cout << "Year: ";
                cin >> yearReminder;

                cout << "Description: ";
                cin.ignore();
                getline(cin, descriptionReminder);

                myCalendar.setReminder(dayReminder, monthReminder, yearReminder, descriptionReminder);
                myCalendar.printRemindersOnDate(dayReminder, monthReminder, yearReminder);
            }
                break;

            case '4':
                {
                    int index, day, month, year;
                    string descriptionReminder;

                    cout << "Enter reminder index to edit: ";
                    cin >> index;

                    cout << "Enter new reminder details:" << endl;
                    cout << "Day: ";
                    cin >> day;

                    cout << "Month: ";
                    cin >> month;

                    cout << "Year: ";
                    cin >> year;
        
                    cout << "Description: ";
                    cin.ignore();
                    getline(cin,descriptionReminder);

                    myCalendar.editReminder(index, day, month, year,descriptionReminder);
                }
                break;

            case '5':
                {
                    int index;
                    cout << "Enter reminder index to delete: ";
                    cin >> index;
                  myCalendar.deleteReminder(index);
                }
                break;
            case '6':
                {
                    int day, month, year;
                    cout << "Enter date to view reminders:" << endl;
                    cout << "Day: ";
                    cin >> day;

                    cout << "Month: ";
                    cin >> month;

                    cout << "Year: ";
                    cin >> year;

                    myCalendar.printRemindersOnDate(day, month, year);
                }
                break;
         case 't':
                {
                    int day, month, year, hour, minute;
                    string descriptionTask;

                    cout << "Enter task details:" << endl;
                    cout << "Day: ";
                    cin >> day;

                    cout << "Month: ";
                    cin >> month;

                    cout << "Year: ";
                    cin >> year;

                    cout << "Hour (24-hour format): ";
                    cin >> hour;

                    cout << "Minute: ";
                    cin >> minute;

                    cout << "Description: ";
                    cin.ignore();
                    getline(cin, descriptionTask);

                     myCalendar.addTask(day, month, year, hour, minute, descriptionTask);
                }
                break;

            case '7':
                {
                    int index, day, month, year, hour, minute;
                    string descriptionTask;

                    cout << "Enter task index to edit: ";
                    cin >> index;

                    cout << "Enter new task details:" << endl;
                    cout << "Day: ";
                    cin >> day;

                    cout << "Month: ";
                    cin >> month;

                    cout << "Year: ";
                    cin >> year;

                    cout << "Hour (24-hour format): ";
                    cin >> hour;

                    cout << "Minute: ";
                    cin >> minute;

                    cout << "Description: ";
                    cin.ignore();
                    getline(cin, descriptionTask);

                     myCalendar.editTask(index, day, month, year, hour, minute, descriptionTask);
                }
                break;

            case '8':
                {
                    int index;
                    cout << "Enter task index to delete: ";
                    cin >> index;
                     myCalendar.deleteTask(index);
                }
                break;

            case '9':
                {
                    int day, month, year;
                    cout << "Enter date to view tasks:" << endl;
                    cout << "Day: ";
                    cin >> day;

                    cout << "Month: ";
                    cin >> month;

                    cout << "Year: ";
                    cin >> year;

                    myCalendar.printTasksOnDate(day, month, year);
                }
                break;
            default:
              cout << "Invalid option! Please try again." << endl;
              break;
            }
    } while (option != 'e' && option != 'E');

    return 0;
}

