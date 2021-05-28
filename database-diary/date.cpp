#include "date.h"


Date::Date (int YYYY, int MM, int DD) : year(YYYY), month(MM), day(DD) {}

int Date::GetYear() const {
        return year;    
}

int Date::GetMonth() const {
    return month;
}

int Date::GetDay() const {
    return day;
}


std::ostream& operator<<(std::ostream& os, const Date& date) {
    os << std::setfill('0');
    os << std::setw(4) << date.GetYear() << '-';
    os << std::setw(2) << date.GetMonth() << '-';
    os << std::setw(2) << date.GetDay();
    return os;
}


std::string DateString(const Date& date) {
    std::stringstream ss;
    ss << std::setfill('0');
    ss << std::setw(4) << date.GetYear() << '-';
    ss << std::setw(2) << date.GetMonth() << '-';
    ss << std::setw(2) << date.GetDay();
    std::string ret_str = ss.str();
    return ret_str;
}


bool operator<(const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() > rhs.GetYear()) return false;
    if (lhs.GetYear() < rhs.GetYear()) return true;
    if (lhs.GetMonth() > rhs.GetMonth()) return false;
    if (lhs.GetMonth() < rhs.GetMonth()) return true;
    return lhs.GetDay() < rhs.GetDay();
}

bool operator>(const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() < rhs.GetYear()) return false;
    if (lhs.GetYear() > rhs.GetYear()) return true;
    if (lhs.GetMonth() < rhs.GetMonth()) return false;
    if (lhs.GetMonth() > rhs.GetMonth()) return true;
    return lhs.GetDay() > rhs.GetDay();    
}

bool operator==(const Date& lhs, const Date& rhs) {
    return lhs.GetYear() == rhs.GetYear() 
    && lhs.GetMonth() == rhs.GetMonth() 
    && lhs.GetDay() == rhs.GetDay();
}

bool operator<=(const Date& lhs, const Date& rhs) {
    return (lhs < rhs) || (lhs == rhs);
}

bool operator>=(const Date& lhs, const Date& rhs) {
    return (lhs > rhs) || (lhs == rhs);
}

bool operator!=(const Date& lhs, const Date& rhs) {
    return !(lhs == rhs);
}


Date ParseDate(std::istream& date) {
    int y, m, d;
    std::string temp;

    if (date.peek() == '-') {
        date.ignore(1);
        std::getline(date, temp, '-');
        y = std::stoi(temp);
        y *= (-1);
    } else if (date.peek() != '-') {
        std::getline(date, temp, '-');
        y = std::stoi(temp);
    }

    if (date.peek() == '-') {
        date.ignore(1);
        std::getline(date, temp, '-');
        m = std::stoi(temp);
        m *= (-1);
    } else if (date.peek() != '-') {
        std::getline(date, temp, '-');
        m = std::stoi(temp);
    }

    std::getline(date, temp, ' ');
    d = std::stoi(temp);

    return {y, m, d};
}