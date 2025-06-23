#pragma once

#include <iostream>
#include <string>

class Person {
public:
    Person(const std::string& firstName, const std::string& middleName, const std::string& lastName,
           const std::string& birthday, int id);

    bool operator<(const Person& other) const;

    bool operator>(const Person& other) const;

    bool operator==(const Person& other) const;

    int GetID() const;

    std::string GetFirstName() const;

    std::string GetMiddleName() const;

    std::string GetLastName() const;

    std::string GetBirthday() const;

private:
    std::string firstName;
    std::string middleName;
    std::string lastName;
    std::string birthday;
    int id;
};

std::ostream& operator<<(std::ostream& os, const Person& p);
