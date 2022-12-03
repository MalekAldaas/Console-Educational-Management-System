#ifndef DATE_H
#define DATE_H

#include <ctime>

class Date {
    private :
        int year;
        int mounth;
        int day;
    public:
        Date(int day, int mounth , int year);
        Date();
        bool operator<(Date other);
        bool operator>(Date other);
        void ShowDate();
};
Date GetCurentDate();
#endif // DATE_H