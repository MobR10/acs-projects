// Să se implementeze o clasă cu constructor default care
// să afișeze data curentă (ziua și ora) în momentul instanțierii
// și să se calculeze câte ore mai sunt până la finalul zilei.
#include <ctime>
#include <iostream>
#include <string>

using namespace std;

class Clock
{
    string date, month, dayName;
    int year, dayNumber, hour,minute, sec;

public:
    Clock()
    {
        time_t curr_time;
        curr_time = time(NULL);

        tm *tm_local = localtime(&curr_time);
        date = asctime(tm_local);

        dayName = date.substr(0, 3);
        if (dayName == "Mon")
            dayName = "Luni";
        else if (dayName == "Tue")
            dayName = "Marti";
        else if (dayName == "Wed")
            dayName = "Miercuri";
        else if (dayName == "Thu")
            dayName = "Joi";
        else if (dayName == "Fri")
            dayName = "Vineri";
        else if (dayName == "Sat")
            dayName = "Sambata";
        else
            dayName = "Duminica";

        month = date.substr(4, 3);
        dayNumber = stoi(date.substr(8, 2));
        hour = stoi(date.substr(11, 2));
        sec = tm_local->tm_sec;
        year = 1900 + tm_local->tm_year;
        
        cout << "Astazi este " << this->dayName << ", ora " << this->hour << endl;
        cout << "Pana la finalul zilei mai sunt " << 24 - this->hour << " ore.";
    }

    ~Clock()
    {
        cout << endl
             << "Se distruge obiect Clock";
    }
};

int main()
{
    Clock clock;
}