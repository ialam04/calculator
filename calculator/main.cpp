#define CATCH_CONFIG_MAIN
#include <iostream>
#include <stdexcept>
#include <string>
#include <cmath>
#include <map>
#include "catch.hpp"
#include "token.h"
#include "token_stream.h"

std::map<std::string, double> variables;

std::string const prompt = "> ";
std::string const result = "= ";

token_stream ts;

double expression(token_stream& ts);

double primary(token_stream& ts) {
    token t = ts.get();
    switch (t.kind()) {
        case '(':
        {
            double d = expression(ts);
            t = ts.get();
            if (t.kind() != ')') throw std::runtime_error("')' expected");
            return d;
        }
        case number:
            return t.value();
        case name:
        {
            token next = ts.get();
            if (next.kind() == assign) {
                double d = expression(ts);
                variables[t.getName()] = d;
                return d;
            } else {
                ts.putback(next);
                return variables[t.getName()];
            }
        }
        case '-':
            return -primary(ts);
        default:
            throw std::runtime_error("Primary expected");
    }
}


double term(token_stream& ts) {
    double left = primary(ts);
    token t = ts.get();

    while (true) {
        switch (t.kind()) {
            case '*':
                left *= primary(ts);
                t = ts.get();
                break;
            case '/':
            {
                double d = primary(ts);
                if (d == 0) throw std::runtime_error("Divide by zero");
                left /= d;
                t = ts.get();
                break;
            }
            case '%':
            {
                double d = primary(ts);
                if (d == 0) throw std::runtime_error("Divide by zero");
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


double expression(token_stream& ts) {
    double left = term(ts);
    token t = ts.get();

    while (true) {
        switch (t.kind()) {
            case '+':
                left += term(ts);
                t = ts.get();
                break;
            case '-':
                left -= term(ts);
                t = ts.get();
                break;
            default:
                ts.putback(t);
                return left;
        }
    }
}

void calculate(token_stream& ts) {
    variables["pi"] = 3.14159;
    variables["e"] = 2.71828;
    while (true) {
        try {
            std::cout << prompt;
            token t = ts.get();
            while (t.kind() == print) t = ts.get();
            if (t.kind() == quit) return;
            ts.putback(t);
            std::cout << result << expression(ts) << std::endl;
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
            ts.ignore(print);
            if (ts.is_end()) break;
        }
    }
}

int calculator(std::istream& input = std::cin) {
    token_stream ts(input);

    try {
        calculate(ts);
        return 0;
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}

TEST_CASE("Checking Basic Operation: ") {
    std::istringstream testInput("1+5; q");
    token_stream ts(testInput);
    std::streambuf* originalCoutStreamBuf = std::cout.rdbuf();
    std::ostringstream capturedOutput;
    std::cout.rdbuf(capturedOutput.rdbuf());
    calculate(ts);
    std::cout.rdbuf(originalCoutStreamBuf);
    std::string output = capturedOutput.str();
    CHECK(output == "> = 6\n> ");
}

TEST_CASE("Checking Basic Operation with Negative Numbers: ") {
    std::istringstream testInput("-1+5; q");
    token_stream ts(testInput);
    std::streambuf* originalCoutStreamBuf = std::cout.rdbuf();
    std::ostringstream capturedOutput;
    std::cout.rdbuf(capturedOutput.rdbuf());
    calculate(ts);
    std::cout.rdbuf(originalCoutStreamBuf);
    std::string output = capturedOutput.str();
    CHECK(output == "> = 4\n> ");
}

TEST_CASE("Checking Basic Operation with Multiplication: ") {
    std::istringstream testInput("2*5; q");
    token_stream ts(testInput);
    std::streambuf* originalCoutStreamBuf = std::cout.rdbuf();
    std::ostringstream capturedOutput;
    std::cout.rdbuf(capturedOutput.rdbuf());
    calculate(ts);
    std::cout.rdbuf(originalCoutStreamBuf);
    std::string output = capturedOutput.str();
    CHECK(output == "> = 10\n> ");
}

