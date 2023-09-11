#ifndef DATE_H
#define DATE_H

#include <ctime>

class Date
{
private:
    int year;
    int month;
    int day;

public:
    Date(int day, int month, int year);
    Date();
    bool operator<(Date other);
    bool operator>(Date other);
    void ShowDate();

    int getDay();
    int getMonth();
    int getYear();
};
Date GetCurentDate();

#endif // DATE_H