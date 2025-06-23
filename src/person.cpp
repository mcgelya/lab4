#include "person.h"

Person::Person(const std::string& firstName, const std::string& middleName, const std::string& lastName, int day,
               int month, int year, int id)
    : firstName(firstName), middleName(middleName), lastName(lastName), day(day), month(month), year(year), id(id) {
}

bool Person::operator<(const Person& other) const {
    if (id == other.id) {
        return lastName < other.lastName || (lastName == other.lastName && firstName < other.firstName);
    }
    return id < other.id;
}

bool Person::operator>(const Person& other) const {
    if (id == other.id) {
        return lastName > other.lastName || (lastName == other.lastName && firstName > other.firstName);
    }
    return id > other.id;
}

bool Person::operator==(const Person& other) const {
    return id == other.id && firstName == other.firstName && lastName == other.lastName;
}

int Person::GetID() const {
    return id;
}

std::string Person::GetFirstName() const {
    return firstName;
}

std::string Person::GetMiddleName() const {
    return middleName;
}

std::string Person::GetLastName() const {
    return lastName;
}

int Person::GetBirthdayDay() const {
    return day;
}

int Person::GetBirthdayMonth() const {
    return month;
}

int Person::GetBirthdayYear() const {
    return year;
}

std::ostream& operator<<(std::ostream& os, const Person& p) {
    os << p.GetID() << ": " << p.GetLastName() << " " << p.GetFirstName() << " " << p.GetMiddleName() << " "
       << p.GetBirthdayDay() << "." << p.GetBirthdayMonth() << "." << p.GetBirthdayYear();
    return os;
}
