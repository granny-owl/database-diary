#pragma once
#include "date.h"
#include <stdexcept>
#include <functional>
#include <fstream>
#include <map>
#include <set>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>

class Database {
public:
    using predicate = std::function<bool(const Date &, const std::string &)>;
    void Add(const Date& date, const std::string& event);
    int RemoveIf(predicate func);
    void Print(std::ostream& os) const;
    std::string Last(const Date& date) const;
    std::vector<std::string> FindIf(predicate func) const;
    //
    void Load(std::string name);
    void Save(std::string name);
    //

private:
    std::map<Date, std::vector<std::string>> events;
    std::map<Date, std::set<std::string>> events_2;
};

