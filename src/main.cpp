#include <climits>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>

#include "binary_tree.h"

int parseInteger(std::string& s, bool& ok, int l = INT_MIN, int r = INT_MAX) {
    long long x = 0;
    bool minus = false;
    ok = 1;
    for (int i = 0; i < s.size(); ++i) {
        if (i == 0 && s[i] == '-') {
            minus = true;
            continue;
        }
        if (!std::isdigit(s[i])) {
            ok = 0;
            return -1;
        }
        x = x * 10 + (s[i] - '0');
        if (x < l || x > r) {
            ok = 0;
            return -1;
        }
    }
    if (x < l || x > r) {
        ok = 0;
        return -1;
    }
    if (minus) {
        x = -x;
    }
    return x;
}

int getInteger(bool& ok, int l = INT_MIN, int r = INT_MAX) {
    std::string s;
    std::getline(std::cin, s);
    return parseInteger(s, ok, l, r);
}

int main() {
    std::vector<BinaryTree<int>> trs(1);
    while (true) {
        std::cout << "Currently available " << trs.size() << " trees\n";
        for (int i = 0; i < trs.size(); ++i) {
            std::cout << i + 1 << ". ";
            std::cout << trs[i].ToString() << std::endl;
        }
        std::cout << std::endl;

        std::cout << "\nChoose operation:\n"
                     "1. Insert element\n"
                     "2. Erase element\n"
                     "3. Traverse in given order\n"
                     "4. Add tree from vector val-par\n"
                     "5. Quit\n"
                  << std::endl;
        std::string c;
        std::getline(std::cin, c);
        if (c == "1") {
            std::cout << "Enter index of tree: ";
            bool ok = 1;
            int ind = getInteger(ok, 1, trs.size());
            --ind;
            if (!ok) {
                std::cout << "Incorrect number!\n";
                continue;
            }
            std::cout << "Enter number: ";
            int x = getInteger(ok);
            if (!ok) {
                std::cout << "Incorrect number!\n";
                continue;
            }
            trs[ind].Insert(x);
        } else if (c == "2") {
            std::cout << "Enter index of tree: ";
            bool ok = 1;
            int ind = getInteger(ok, 1, trs.size());
            --ind;
            if (!ok) {
                std::cout << "Incorrect number!\n";
                continue;
            }
            std::cout << "Enter number: ";
            int x = getInteger(ok);
            if (!ok) {
                std::cout << "Incorrect number!\n";
                continue;
            }
            if (!trs[ind].Search(x)) {
                std::cout << "No such number in this tree!\n";
                continue;
            }
            trs[ind].Erase(x);
        } else if (c == "3") {
            std::cout << "Enter index of tree: ";
            bool ok = 1;
            int ind = getInteger(ok, 1, trs.size());
            --ind;
            if (!ok) {
                std::cout << "Incorrect number!\n";
                continue;
            }
            std::string format;
            std::getline(std::cin, format);
            try {
                std::cout << ind + 1 << ". " << trs[ind].ToString(format) << std::endl;
            } catch (std::invalid_argument& e) {
                std::cout << "Invalid format!\n";
                continue;
            }
        } else if (c == "4") {
            std::cout << "Enter vector in format + val-par, when you are done type '!'\n";
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
                bool ok = 1;
                int val = parseInteger(a, ok);
                if (!ok) {
                    std::cout << "Incorrect number!\n";
                    break;
                }
                int par = parseInteger(b, ok);
                if (!ok) {
                    std::cout << "Incorrect number!\n";
                    break;
                }
                cur.push_back({val, par});
            }
            try {
                BinaryTree<int> tr = BinaryTree<int>::FromPairs(cur);
                trs.push_back(tr);
            } catch (std::invalid_argument e) {
                std::cout << "Invalid tree!\n";
            }
        } else if (c == "5") {
            break;
        } else {
            std::cout << "Incorrect option!\n";
        }
    }
}
