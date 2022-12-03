#include "../Headers/date.h"
#include <iostream>

Date::Date(int day, int mounth , int year)
{
    this->day=day;
    this->mounth=mounth;
    this->year=year;
}
Date::Date(){}
bool Date::operator<(Date other)
{
    if(this->year < other.year)return true;
    if(this->year==other.year && this->mounth < other.mounth)return true;
    if(this->year==other.year && this->mounth == other.mounth && this->day < other.day)return true;
    return false;
}
bool Date::operator>(Date other)
{
    if(this->year > other.year)return true;
    if(this->year==other.year && this->mounth > other.mounth)return true;
    if(this->year==other.year && this->mounth == other.mounth && this->day > other.day)return true;
    return false;
}
Date GetCurentDate()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int year=1900 + ltm->tm_year;
    int mounth=1 + ltm->tm_mon;
    int day=ltm->tm_mday;
    Date Today=Date(day,mounth,year);
    return Today;
}
void Date::ShowDate()
{
    std::cout<<day<<'/'<<mounth<<'/'<<year << std::endl;
}