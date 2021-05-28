#include "database.h"

void Database::Add(const Date& date, const std::string& event) {
    if (events_2[date].count(event) == 0) {
        events[date].push_back(event); //добавляем событие в мап из дат и вектора строк
        events_2[date].insert(event); //добавляем событие в мап из дат и сета строк   
    }
}

int Database::RemoveIf(predicate func) {
    int i = 0;
    int one, two;
    std::vector<Date> del_dates;
    for (auto& [date, evs] : events) {
        auto pred = [d = date, f = func](auto& ev){ return !f(d, ev); };
        two = std::distance(evs.begin(), evs.end()); 
        auto it = std::stable_partition(evs.begin(), evs.end(), pred);
        one = std::distance(evs.begin(), it);                                                 
        if (one == 0) { //если нужно удалять все элементы
            del_dates.push_back(date);
            i += two;
        } else {
            auto& set_evs = events_2.at(date);
            for (auto& ev_t = it; ev_t != evs.begin() + two; ev_t++) {
                set_evs.erase(*ev_t); //удаление из сета элементов, подходящих под условие
                i++;
            }
            evs.erase(evs.begin() + one, evs.begin() + two); //удаление из вектора
        }                          
    }
    for (const auto& dd : del_dates) {
        events.erase(dd);
        events_2.erase(dd);
    }
    return i;   
}

void Database::Print(std::ostream& os) const {
    for (const auto& pairs : events) {
        for (const auto& acts : pairs.second) {
            os << pairs.first << ' ' << acts << '\n';
        }
    }   
}

std::string Database::Last(const Date& date) const {
    std::string ret_str = "No entries\n";
    auto next_evs = events.upper_bound(date); //ищем элемент, у которого дата больше необходимой

    if (next_evs == events.begin()) { //если он оказался в начале, то элемента с нужной (или меньшей) датой нет
        throw std::invalid_argument("No entries");
    } 

    auto ev = std::prev(next_evs); //отходим назад от элемента, который точно больше нужного
    ret_str = DateString(ev->first); //строка с датой в формате "YYYY-MM-DD"
    ret_str += " ";
    ret_str += ev->second.back(); //докидываем последнее событие из вектора строк с событиями
    return ret_str;
}

std::vector<std::string> Database::FindIf(predicate func) const {
    std::vector<std::string> ret_vec;
    std::string str;
    for (auto& [date, evs] : events) {
        std::vector<std::string> temp; //вектор для подходящих событий за одну дату
        auto pred = [d = date, f = func](auto& ev){ return f(d, ev); }; //докидываем недостающие данные в предикат
        std::copy_if(evs.begin(), evs.end(), std::back_inserter(temp), pred); //копируем подходящие события в вектор temp
        if (!temp.empty()) { //если подходящие события нашлись
            str = DateString(date); //строка с датой подходящих событий
            for (const auto& el : temp) {
                ret_vec.emplace_back(str + " " + el); //добавляем дату + подходящее событие в возвращаемый вектор
            }
        }
    }
    return ret_vec;
}

//

std::string Parse_Event(std::stringstream& ss) {
    std::string ret_str;
    std::getline(ss >> std::ws, ret_str);
    return ret_str;
}

void Database::Load(std::string name) {
    std::ifstream get_data(name);
    if (get_data) {
        std::string temp;
        while (std::getline(get_data, temp)) {
            std::stringstream ss(temp);
            const auto date = ParseDate(ss);
            const auto event = Parse_Event(ss);
            Add(date, event);
        }
    }
}

void Database::Save(std::string name) {
    std::ofstream put_data(name);
    for (const auto& pairs : events) {
        for (const auto& acts : pairs.second) {
            put_data << pairs.first << ' ' << acts << '\n';
        }
    }  
}
//
