#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>


class Date {
public:
    Date (int YYYY, int MM, int DD);
    int GetYear() const;
    int GetMonth() const;
    int GetDay() const;

private:
    const int year;
    const int month;
    const int day;
};

std::ostream& operator<<(std::ostream& os, const Date& date);

std::string DateString(const Date& date);

bool operator<(const Date& lhs, const Date& rhs);
bool operator>(const Date& lhs, const Date& rhs);
bool operator==(const Date& lhs, const Date& rhs);
bool operator<=(const Date& lhs, const Date& rhs);
bool operator>=(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);

Date ParseDate(std::istream& date);

