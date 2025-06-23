#include "person.h"

Person::Person(const std::string& firstName, const std::string& lastName, int id)
    : firstName(firstName), lastName(lastName), id(id) {
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

std::string Person::GetLastName() const {
    return lastName;
}

std::ostream& operator<<(std::ostream& os, const Person& p) {
    os << p.GetID() << ": " << p.GetLastName() << " " << p.GetFirstName();
    return os;
}
