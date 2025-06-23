#pragma once

#include <iostream>
#include <string>

class Person {
public:
    Person(const std::string& firstName, const std::string& lastName, int id);

    bool operator<(const Person& other) const;

    bool operator>(const Person& other) const;

    bool operator==(const Person& other) const;

    int GetID() const;

    std::string GetFirstName() const;

    std::string GetLastName() const;

private:
    std::string firstName;
    std::string lastName;
    int id;
};

std::ostream& operator<<(std::ostream& os, const Person& p);
