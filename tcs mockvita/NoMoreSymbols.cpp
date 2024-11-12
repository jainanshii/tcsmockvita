#include <iostream>
#include <sstream>
#include <stack>
#include <vector>
#include <unordered_map>
#include<bits/stdc++.h>
using namespace std;

// Helper function to check if a string is a number
bool isNumber(const string& str) {
    for (char const &c : str) {
        if (!isdigit(c)) return false;
    }
    return true;
}

// Function to map word numbers to integer values
int mapping(string word) {
    unordered_map<string, int> m;
    m["one"] = 1;
    m["two"] = 2;
    m["three"] = 3;
    m["four"] = 4;
    m["five"] = 5;
    m["six"] = 6;
    m["seven"] = 7;
    m["eight"] = 8;
    m["nine"] = 9;
    m["zero"] = 0;

    int num = 0;
    string ans = "";
    if (m.find(word) == m.end()) {
        for (size_t i = 0; i < word.size(); i++) {
            if (word[i] == 'c') {
                if (m.find(ans) == m.end()) {
                    return -1; // Invalid word
                }
                num = num * 10 + m[ans];
                ans = "";
            } else {
                ans += word[i];
            }
        }
        if (m.find(ans) == m.end()) return -1; // Invalid last part
        num = num * 10 + m[ans];
        return num;
    }
    return m[word];
}

// Function to map operations (e.g., add -> +)
string map1(string word) {
    unordered_map<string, string> m;
    m["add"] = "+";
    m["sub"] = "-";
    m["mul"] = "*";
    m["rem"] = "%";
    m["pow"] = "^";
    m["div"] = "/";

    if (m.find(word) == m.end()) return "-1";
    return m[word];
}

// Function to evaluate expression
int help(string input) {
    stringstream ss(input);
    string token;
    vector<string> v;
    
    // Parse input into vector
    while (ss >> token) {
        string op = map1(token);
        if (op == "-1") {
            int num = mapping(token);
            if (num == -1) {
                cout << "expression evaluation stopped invalid words present" << endl;
                return -1;
            }
            v.push_back(to_string(num));
        } else {
            v.push_back(op);
        }
    }
    
    if (v.empty()) {
        return -1;
    }

    stack<int> s;
    int n = v.size();
    
    // Process the expression in reverse order
    for (int i = n - 1; i >= 0; i--) {
        if (isNumber(v[i])) {
            s.push(stoi(v[i]));
        } else {
            if (s.size() < 2) {
                return -1;
            }
            int o1 = s.top(); s.pop();
            int o2 = s.top(); s.pop();
            
            switch (v[i][0]) { // Use the first character to determine the operation
                case '+':
                    s.push(o1 + o2);
                    break;
                case '-':
                    s.push(o1 - o2);
                    break;
                case '*':
                    s.push(o1 * o2);
                    break;
                case '/':
                    if (o2 == 0) {
                        cout << "division by zero is not allowed" << endl;
                        return -1;
                    }
                    s.push(o1 / o2);
                    break;
                case '%':
                    s.push(o1 % o2);
                    break;
                case '^':
                    s.push(pow(o1,o2));
                    break;    
                default:
                    cout << "expression is not complete or invalid" << endl;
                    return -1;
            }
        }
    }

    if (s.size() != 1) {
        cout << "expression is not complete or invalid" << endl;
        return -1;
    }

    return s.top();
}

int main() {
    string in;
    getline(cin, in);
    int result = help(in);
    if (result != -1) {
        cout << result << endl;
    }
    return 0;
}
