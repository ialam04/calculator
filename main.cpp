#include <iostream>
#include <stdexcept>
#include <string>
#include <cmath>
#include <map>
#include "token.h"
#include "token_stream.h"

std::map<std::string, double> variables;    // table of variables

std::string const prompt = "> ";
std::string const result = "= ";

token_stream ts;

double expression(); // Forward declaration

double primary() {
    token t = ts.get();
    switch (t.kind()) {
        case '(': {
            double d = expression();
            t = ts.get();
            if (t.kind() != ')') throw std::runtime_error("')' expected");
            return d;
        }
        case number:
            return t.value();
        case name: {
            token next = ts.get();
            if (next.kind() == assign) {
                double d = expression();
                variables[t.getName()] = d;
                return d;
            } else {
                ts.putback(next);
                return variables[t.getName()];
            }
        }
        case '-':
            return -primary();
        default:
            throw std::runtime_error("Primary expected");
    }
}

double term() {
    double left = primary();
    token t = ts.get();

    while (true) {
        switch (t.kind()) {
            case '*':
                left *= primary();
                t = ts.get();
                break;
            case '/': {
                double d = primary();
                if (d == 0) {
                    throw std::runtime_error("Divide by zero");
                }
                left /= d;
                t = ts.get();
                break;
            }
            case '%': {
                double d = primary();
                if (d == 0) {
                    throw std::runtime_error("Divide by zero");
                }
                left = std::fmod(left, d);
                t = ts.get();
                break;
            }
            default:
                ts.putback(t);
                return left;
        }
    }
}

double expression() {
    double left = term();
    token t = ts.get();

    while (true) {
        switch (t.kind()) {
            case '+':
                left += term();
                t = ts.get();
                break;
            case '-':
                left -= term();
                t = ts.get();
                break;
            default:
                ts.putback(t);
                return left;
        }
    }
}

void calculate() {
    while (std::cin) {
        try {
            std::cout << prompt;
            token t = ts.get();
            while (t.kind() == print) t = ts.get();
            if (t.kind() == quit) {
                return;
            }
            ts.putback(t);
            std::cout << result << expression() << std::endl;
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
            ts.ignore(print);
        }
    }
}

int main() {
    variables["pi"] = 3.14159;
    variables["e"] = 2.71828;

    try {
        calculate();
        return 0;
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}

