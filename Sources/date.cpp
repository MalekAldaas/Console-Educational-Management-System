#include "../Headers/date.h"
#include <iostream>

Date::Date(int day, int month, int year)
{
    this->day = day;
    this->month = month;
    this->year = year;
}
Date::Date() {}
bool Date::operator<(Date other)
{
    if (this->year < other.year)
        return true;
    if (this->year == other.year && this->month < other.month)
        return true;
    if (this->year == other.year && this->month == other.month && this->day < other.day)
        return true;
    return false;
}
bool Date::operator>(Date other)
{
    if (this->year > other.year)
        return true;
    if (this->year == other.year && this->month > other.month)
        return true;
    if (this->year == other.year && this->month == other.month && this->day > other.day)
        return true;
    return false;
}
Date GetCurentDate()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int year = 1900 + ltm->tm_year;
    int month = 1 + ltm->tm_mon;
    int day = ltm->tm_mday;
    Date Today = Date(day, month, year);
    return Today;
}
void Date::ShowDate()
{
    std::cout << day << '/' << month << '/' << year << std::endl;
}

int Date::getDay()
{
    return this->day;
}
int Date::getMonth()
{
    return this->month;
}
int Date::getYear()
{
    return this->year;
}