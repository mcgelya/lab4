#include <climits>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>

#include "binary_tree.h"
#include "person.h"

int parseInteger(std::string& s, bool& err, int l = INT_MIN, int r = INT_MAX) {
    long long x = 0;
    bool minus = false;
    err = 0;
    for (int i = 0; i < s.size(); ++i) {
        if (i == 0 && s[i] == '-') {
            minus = true;
            continue;
        }
        if (!std::isdigit(s[i])) {
            std::cout << "\nNot a number!\n";
            err = 1;
            return -1;
        }
        x = x * 10 + (s[i] - '0');
        if (x < l || x > r) {
            std::cout << "\nNumber is out of range!\n";
            err = 1;
            return -1;
        }
    }
    if (x < l || x > r) {
        std::cout << "\nNumber is out of range!\n";
        err = 1;
        return -1;
    }
    if (minus) {
        x = -x;
    }
    return x;
}

int getInteger(bool& err, int l = INT_MIN, int r = INT_MAX) {
    std::string s;
    std::getline(std::cin, s);
    return parseInteger(s, err, l, r);
}

int main() {
    std::cout << "Choose mode:\n"
                 "1. Integers\n"
                 "2. Persons\n"
              << std::endl;
    while (true) {
        std::string mode;
        std::getline(std::cin, mode);
        if (mode == "1") {
            std::vector<BinaryTree<int>> trs(1);
            while (true) {
                std::cout << "\nCurrently available " << trs.size() << " trees\n";
                for (int i = 0; i < trs.size(); ++i) {
                    std::cout << i + 1 << ". ";
                    std::cout << trs[i].ToString() << std::endl;
                }
                std::cout << std::endl;

                std::cout << "\nChoose operation:\n"
                             "1. Insert element\n"
                             "2. Erase element\n"
                             "3. Save to string in given order\n"
                             "4. Add tree from vector val-par\n"
                             "5. Extract subtree\n"
                             "6. Find subtree\n"
                             "7. Map (multiply everything by 2)\n"
                             "8. Where (filter to leave only odd numbers)\n"
                             "9. Reduce (find sum)\n"
                             "10. Quit\n"
                          << std::endl;
                std::string c;
                std::getline(std::cin, c);
                if (c == "1") {
                    std::cout << "Enter index of tree: ";
                    bool err = 0;
                    int ind = getInteger(err, 1, trs.size());
                    --ind;
                    if (err) {
                        continue;
                    }
                    std::cout << "Enter number: ";
                    int x = getInteger(err);
                    if (err) {
                        continue;
                    }
                    trs[ind].Insert(x);
                } else if (c == "2") {
                    std::cout << "Enter index of tree: ";
                    bool err = 0;
                    int ind = getInteger(err, 1, trs.size());
                    --ind;
                    if (err) {
                        continue;
                    }
                    std::cout << "Enter number: ";
                    int x = getInteger(err);
                    if (err) {
                        continue;
                    }
                    if (!trs[ind].Search(x)) {
                        std::cout << "\nNo such number in this tree!\n";
                        continue;
                    }
                    trs[ind].Erase(x);
                } else if (c == "3") {
                    std::cout << "Enter index of tree: ";
                    bool err = 0;
                    int ind = getInteger(err, 1, trs.size());
                    --ind;
                    if (err) {
                        continue;
                    }
                    std::cout << "Enter format: ";
                    std::string format;
                    std::getline(std::cin, format);
                    try {
                        std::cout << "\n" << ind + 1 << ". " << trs[ind].ToString(format) << std::endl;
                    } catch (std::invalid_argument& e) {
                        std::cout << "\nInvalid format!\n";
                        continue;
                    }
                } else if (c == "4") {
                    std::cout << "Enter vector in format + val par, when you are done type '!'\n";
                    std::string s;
                    std::vector<std::pair<int, int>> cur;
                    while (std::getline(std::cin, s)) {
                        std::istringstream ss(s);
                        char t;
                        ss >> t;
                        if (t == '!') {
                            break;
                        }
                        std::string a, b;
                        ss >> a >> b;
                        bool err = 0;
                        int val = parseInteger(a, err);
                        if (err) {
                            break;
                        }
                        int par = parseInteger(b, err);
                        if (err) {
                            break;
                        }
                        cur.push_back({val, par});
                    }
                    try {
                        BinaryTree<int> tr = BinaryTree<int>::FromPairs(cur);
                        trs.push_back(tr);
                    } catch (std::invalid_argument e) {
                        std::cout << "\nInvalid tree!\n";
                    }
                } else if (c == "5") {
                    std::cout << "Enter index of tree: ";
                    bool err = 0;
                    int ind = getInteger(err, 1, trs.size());
                    --ind;
                    if (err) {
                        continue;
                    }
                    std::cout << "Enter node (value): ";
                    int x = getInteger(err);
                    if (err) {
                        continue;
                    }
                    try {
                        BinaryTree<int> t = trs[ind].GetSubTree(x);
                        trs.push_back(t);
                    } catch (std::invalid_argument e) {
                        std::cout << "No such value in tree!\n";
                    }
                } else if (c == "6") {
                    std::cout << "Enter index of tree that you want to find: ";
                    bool err = 0;
                    int ind1 = getInteger(err, 1, trs.size());
                    --ind1;
                    if (err) {
                        continue;
                    }
                    std::cout << "Enter index of tree where you want to find: ";
                    int ind2 = getInteger(err, 1, trs.size());
                    --ind2;
                    if (err) {
                        continue;
                    }
                    if (trs[ind2].FindSubTree(trs[ind1])) {
                        std::cout << "\nYes, it is included as subtree\n";
                    } else {
                        std::cout << "\nNo, it is not included\n";
                    }
                } else if (c == "7") {
                    std::cout << "Enter index of tree: ";
                    bool err = 0;
                    int ind = getInteger(err, 1, trs.size());
                    --ind;
                    if (err) {
                        continue;
                    }
                    BinaryTree<int> mp = trs[ind].Map([](int x) {
                        return 2 * x;
                    });
                    trs.push_back(mp);
                    std::cout << "\nHere it is: " << mp.ToString() << "\n";
                } else if (c == "8") {
                    std::cout << "Enter index of tree: ";
                    bool err = 0;
                    int ind = getInteger(err, 1, trs.size());
                    --ind;
                    if (err) {
                        continue;
                    }
                    BinaryTree<int> whr = trs[ind].Where([](int x) {
                        return x % 2 == 1;
                    });
                    trs.push_back(whr);
                    std::cout << "\nHere it is: " << whr.ToString() << "\n";
                } else if (c == "9") {
                    std::cout << "Enter index of tree: ";
                    bool err = 0;
                    int ind = getInteger(err, 1, trs.size());
                    --ind;
                    if (err) {
                        continue;
                    }
                    int res = trs[ind].Reduce(
                        [](int x, int acc) {
                            return x + acc;
                        },
                        0);
                    std::cout << "\nHere it is: " << res << "\n";
                } else if (c == "10") {
                    return 0;
                } else {
                    std::cout << "\nIncorrect option!\n";
                }
            }
        } else if (mode == "2") {
            std::vector<BinaryTree<Person>> trs(1);
            while (true) {
                std::cout << "\nCurrently available " << trs.size() << " trees\n";
                for (int i = 0; i < trs.size(); ++i) {
                    std::cout << i + 1 << ". ";
                    std::cout << trs[i].ToString() << std::endl;
                }
                std::cout << std::endl;

                std::cout << "\nChoose operation:\n"
                             "1. Insert element\n"
                             "2. Erase element\n"
                             "3. Save to string in given order\n"
                             "4. Extract subtree\n"
                             "5. Find subtree\n"
                             "6. Map (decrease all id's by one)\n"
                             "7. Where (leave only persons with name 'Ivan')\n"
                             "8. Quit\n"
                          << std::endl;
                std::string c;
                std::getline(std::cin, c);
                if (c == "1") {
                    std::cout << "Enter index of tree: ";
                    bool err = 0;
                    int ind = getInteger(err, 1, trs.size());
                    --ind;
                    if (err) {
                        continue;
                    }
                    std::cout << "Enter id: ";
                    int id = getInteger(err);
                    if (err) {
                        continue;
                    }
                    std::cout << "Enter firstName: ";
                    std::string firstName, lastName;
                    std::getline(std::cin, firstName);
                    std::cout << "Enter lastName: ";
                    std::getline(std::cin, lastName);
                    trs[ind].Insert(Person(firstName, lastName, id));
                } else if (c == "2") {
                    std::cout << "Enter index of tree: ";
                    bool err = 0;
                    int ind = getInteger(err, 1, trs.size());
                    --ind;
                    if (err) {
                        continue;
                    }
                    std::cout << "Enter id: ";
                    int id = getInteger(err);
                    if (err) {
                        continue;
                    }
                    std::cout << "Enter firstName: ";
                    std::string firstName, lastName;
                    std::getline(std::cin, firstName);
                    std::cout << "Enter lastName: ";
                    std::getline(std::cin, lastName);
                    Person p(firstName, lastName, id);
                    if (!trs[ind].Search(p)) {
                        std::cout << "\nNo such person in this tree!\n";
                        continue;
                    }
                    trs[ind].Erase(p);
                } else if (c == "3") {
                    std::cout << "Enter index of tree: ";
                    bool err = 0;
                    int ind = getInteger(err, 1, trs.size());
                    --ind;
                    if (err) {
                        continue;
                    }
                    std::cout << "Enter format: ";
                    std::string format;
                    std::getline(std::cin, format);
                    try {
                        std::cout << "\n" << ind + 1 << ". " << trs[ind].ToString(format) << std::endl;
                    } catch (std::invalid_argument& e) {
                        std::cout << "\nInvalid format!\n";
                        continue;
                    }
                } else if (c == "4") {
                    std::cout << "Enter index of tree: ";
                    bool err = 0;
                    int ind = getInteger(err, 1, trs.size());
                    --ind;
                    if (err) {
                        continue;
                    }
                    std::cout << "Enter id: ";
                    int id = getInteger(err);
                    if (err) {
                        continue;
                    }
                    std::cout << "Enter firstName: ";
                    std::string firstName, lastName;
                    std::getline(std::cin, firstName);
                    std::cout << "Enter lastName: ";
                    std::getline(std::cin, lastName);
                    Person p(firstName, lastName, id);
                    try {
                        BinaryTree<Person> t = trs[ind].GetSubTree(p);
                        trs.push_back(t);
                    } catch (std::invalid_argument e) {
                        std::cout << "No such value in tree!\n";
                    }
                } else if (c == "5") {
                    std::cout << "Enter index of tree that you want to find: ";
                    bool err = 0;
                    int ind1 = getInteger(err, 1, trs.size());
                    --ind1;
                    if (err) {
                        continue;
                    }
                    std::cout << "Enter index of tree where you want to find: ";
                    int ind2 = getInteger(err, 1, trs.size());
                    --ind2;
                    if (err) {
                        continue;
                    }
                    if (trs[ind2].FindSubTree(trs[ind1])) {
                        std::cout << "\nYes, it is included as subtree\n";
                    } else {
                        std::cout << "\nNo, it is not included\n";
                    }
                } else if (c == "6") {
                    std::cout << "Enter index of tree: ";
                    bool err = 0;
                    int ind = getInteger(err, 1, trs.size());
                    --ind;
                    if (err) {
                        continue;
                    }
                    BinaryTree<Person> mp = trs[ind].Map([](const Person& p) {
                        return Person(p.GetFirstName(), p.GetLastName(), p.GetID() - 1);
                    });
                    trs.push_back(mp);
                    std::cout << "\nHere it is: " << mp.ToString() << "\n";
                } else if (c == "7") {
                    std::cout << "Enter index of tree: ";
                    bool err = 0;
                    int ind = getInteger(err, 1, trs.size());
                    --ind;
                    if (err) {
                        continue;
                    }
                    BinaryTree<Person> whr = trs[ind].Where([](const Person& p) {
                        return p.GetFirstName() == "Ivan";
                    });
                    trs.push_back(whr);
                    std::cout << "\nHere it is: " << whr.ToString() << "\n";
                } else if (c == "8") {
                    return 0;
                } else {
                    std::cout << "\nIncorrect option!\n";
                }
            }
        } else {
            std::cout << "Incorrect mode!\n";
        }
    }
}
