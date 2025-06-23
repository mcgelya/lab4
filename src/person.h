#pragma once

#include <iostream>
#include <string>

class Person {
public:
    Person(const std::string& firstName, const std::string& middleName, const std::string& lastName, int day, int month,
           int year, int id);

    bool operator<(const Person& other) const;

    bool operator>(const Person& other) const;

    bool operator==(const Person& other) const;

    int GetID() const;

    std::string GetFirstName() const;

    std::string GetMiddleName() const;

    std::string GetLastName() const;

    int GetBirthdayDay() const;

    int GetBirthdayMonth() const;

    int GetBirthdayYear() const;

private:
    std::string firstName;
    std::string middleName;
    std::string lastName;
    int day, month, year;
    int id;
};

std::ostream& operator<<(std::ostream& os, const Person& p);
