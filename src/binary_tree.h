#pragma once

#include <cctype>
#include <map>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

template <class T>
struct Node {
    T value;
    Node *l = nullptr, *r = nullptr;
    Node *leftThread = nullptr, *rightThread = nullptr;

    Node(T x) : value(x) {
    }
};

template <class T>
class BinaryTree {
public:
    BinaryTree() {
    }

    BinaryTree(Node<T>* root) : root(root) {
    }

    void Insert(T x) {
        if (Search(x)) {
            return;
        }
        root = Insert(root, x);
    }

    bool Search(T x) {
        return Search(root, x);
    }

    void Erase(T x) {
        if (!Search(x)) {
            throw std::out_of_range("No such key in tree");
        }
        root = Erase(root, x);
    }

    template <class F>
    BinaryTree<T> Map(F func) {
        BinaryTree<T> res;
        Map(root, func, res);
        return res;
    }

    template <class F>
    BinaryTree<T> Where(F pred) {
        BinaryTree<T> res;
        Where(root, pred, res);
        return res;
    }

    template <class F>
    T Reduce(F func, T c) {
        T res = c;
        Reduce(root, func, res);
        return res;
    }

    bool CheckOrder(const std::string& order) {
        if (order.size() != 3) {
            return false;
        }
        int l = (order[0] == 'L') + (order[1] == 'L') + (order[2] == 'L');
        int n = (order[0] == 'N') + (order[1] == 'N') + (order[2] == 'N');
        int r = (order[0] == 'R') + (order[1] == 'R') + (order[2] == 'R');
        return l == 1 && n == 1 && r == 1;
    }

    bool CheckFormat(const std::string& format) {
        if (format.size() != 9) {
            return false;
        }
        std::string order{format[1], format[4], format[7]};
        if (!CheckOrder(order)) {
            return false;
        }
        for (int i = 0; i < format.size(); ++i) {
            for (int j = i + 1; j < format.size(); ++j) {
                if (format[i] == format[j]) {
                    return false;
                }
            }
        }
        return true;
    }

    void ThreadTree(const std::string& order = "LNR") {
        if (!CheckOrder(order)) {
            throw std::invalid_argument("Invalid order");
        }
        Node<T>* prev = nullptr;
        ThreadTree(root, order, prev);
    }

    std::string ToString(const std::string& format = "{L}(N)[R]") {
        if (!CheckFormat(format)) {
            throw std::invalid_argument("Invalid format");
        }
        std::string res;
        Traverse(root, format, res);
        return res;
    }

    BinaryTree<T> GetSubTree(int x) {
        if (!Search(x)) {
            throw std::invalid_argument("No such key");
        }
        BinaryTree<T> res(Clone(Find(root, x)));
        return res;
    }

    bool FindSubTree(BinaryTree<T>& subTree) {
        if (subTree.root == nullptr) {
            throw std::invalid_argument("subTree is empty");
        }
        T x = subTree.root->value;
        if (!Search(x)) {
            return false;
        }
        Node<T>* v = Find(root, x);
        std::string traversedV;
        Traverse(v, "{L}(N)[R]", traversedV);
        std::string traversedS = subTree.ToString();
        return traversedV == traversedS;
    }

    static bool CheckTree(Node<T>* v, std::optional<T> mn, std::optional<T> mx) {
        if (v == nullptr) {
            return true;
        }
        if (mn && v->value <= *mn) {
            return false;
        }
        if (mx && v->value >= *mx) {
            return false;
        }
        return CheckTree(v->l, mn, v->value) && CheckTree(v->r, v->value, mx);
    }

    static BinaryTree<T> FromPairs(std::vector<std::pair<T, T>>& tree) {
        std::map<T, Node<T>*> nodes;
        std::map<T, std::vector<T>> g;
        for (auto [v, p] : tree) {
            if (!nodes.count(v)) {
                nodes[v] = new Node(v);
            }
            if (!nodes.count(p)) {
                nodes[p] = new Node(p);
            }
            g[v].push_back(p);
            g[p].push_back(v);
            if (v == p) {
                throw std::invalid_argument("Invalid tree");
            }
            if (v < p) {
                if (nodes[p]->l != nullptr) {
                    throw std::invalid_argument("Invalid tree");
                }
                nodes[p]->l = nodes[v];
            } else {
                if (nodes[p]->r != nullptr) {
                    throw std::invalid_argument("Invalid tree");
                }
                nodes[p]->r = nodes[v];
            }
        }
        std::map<T, bool> used;
        auto dfs = [&](auto dfs, T v, T p) -> void {
            used[v] = 1;
            for (auto u : g[v]) {
                if (u == p) {
                    continue;
                }
                if (!used[u]) {
                    dfs(dfs, u, v);
                } else {
                    throw std::invalid_argument("Invalid tree");
                }
            }
        };
        for (const auto& [v, _] : g) {
            if (!used[v]) {
                dfs(dfs, v, -1);
            }
        }
        std::map<T, int> cnt;
        for (auto [v, p] : tree) {
            ++cnt[v];
        }
        BinaryTree<T> tr;
        for (auto [x, v] : nodes) {
            if (cnt[x] > 1) {
                throw std::invalid_argument("Invalid tree");
            }
            if (cnt[x] == 0) {
                if (tr.root != nullptr) {
                    throw std::invalid_argument("Invalid tree");
                }
                tr.root = v;
            }
        }
        if (!CheckTree(tr.root, std::nullopt, std::nullopt)) {
            throw std::invalid_argument("Invalid tree");
        }
        return tr;
    }

private:
    Node<T>* root = nullptr;

    Node<T>* Insert(Node<T>* v, T x) {
        if (v == nullptr) {
            return new Node<T>(x);
        }
        if (x < v->value) {
            v->l = Insert(v->l, x);
        } else {
            v->r = Insert(v->r, x);
        }
        return v;
    }

    bool Search(Node<T>* v, T x) {
        if (v == nullptr) {
            return false;
        }
        if (v->value == x) {
            return true;
        }
        if (x < v->value) {
            return Search(v->l, x);
        } else {
            return Search(v->r, x);
        }
    }

    Node<T>* Find(Node<T>* v, T x) {
        if (v == nullptr) {
            return nullptr;
        }
        if (v->value == x) {
            return v;
        }
        if (x < v->value) {
            return Find(v->l, x);
        } else {
            return Find(v->r, x);
        }
    }

    Node<T>* Erase(Node<T>* v, T x) {
        if (v == nullptr) {
            return v;
        }
        if (x < v->value) {
            v->l = Erase(v->l, x);
        } else if (x > v->value) {
            v->r = Erase(v->r, x);
        } else {
            if (v->l == nullptr) {
                return v->r;
            } else if (v->r == nullptr) {
                return v->l;
            }
            Node<T>* newV = v->r;
            while (newV->l != nullptr) {
                newV = newV->l;
            }
            v->value = newV->value;
            v->r = Erase(v->r, newV->value);
        }
        return v;
    }

    template <class F>
    void Map(Node<T>* v, F func, BinaryTree<T>& res) {
        if (v == nullptr) {
            return;
        }
        Map(v->l, func, res);
        res.Insert(func(v->value));
        Map(v->r, func, res);
    }

    template <class F>
    void Where(Node<T>* v, F pred, BinaryTree<T>& res) {
        if (v == nullptr) {
            return;
        }
        Where(v->l, pred, res);
        if (pred(v->value)) {
            res.Insert(v->value);
        }
        Where(v->r, pred, res);
    }

    template <class F>
    void Reduce(Node<T>* v, F func, T& res) {
        if (v == nullptr) {
            return;
        }
        Reduce(v->l, func, res);
        res = func(v->value, res);
        Reduce(v->r, func, res);
    }

    void ThreadTree(Node<T>* v, const std::string& order, Node<T>*& prev) {
        if (v == nullptr) {
            return;
        }
        for (char c : order) {
            if (c == 'N') {
                if (v->l == nullptr) {
                    v->leftThread = prev;
                }
                if (prev && prev->r == nullptr) {
                    prev->rightThread = v;
                }
                prev = v;
            } else if (c == 'L') {
                Traverse(v->l, order, prev);
            } else {
                Traverse(v->r, order, prev);
            }
        }
    }

    void Traverse(Node<T>* v, const std::string& format, std::string& res) {
        if (v == nullptr) {
            return;
        }
        for (int i = 1; i <= 7; i += 3) {
            if (format[i] == 'N') {
                res += format[i - 1];
                res += std::to_string(v->value);
                res += format[i + 1];
            } else if (format[i] == 'L') {
                if (v->l != nullptr) {
                    res += format[i - 1];
                    Traverse(v->l, format, res);
                    res += format[i + 1];
                }
            } else {
                if (v->r != nullptr) {
                    res += format[i - 1];
                    Traverse(v->r, format, res);
                    res += format[i + 1];
                }
            }
        }
    }

    Node<T>* Clone(Node<T>* v) {
        if (v == nullptr) {
            return nullptr;
        }
        Node<T>* newV = new Node<T>(v->value);
        newV->l = Clone(v->l);
        newV->r = Clone(v->r);
        return newV;
    }
};
