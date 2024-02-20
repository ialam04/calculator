//
// Created by Ibrahim Alam on 2/20/24.
//

#ifndef CALCULATOR_TOKEN_H
#define CALCULATOR_TOKEN_H
#include <string>


const char number = '8';    // a floating-point number
const char quit = 'q';      // an exit command
const char print = ';';     // a print command
const char name = 'a';      // a variable name
const char assign = '=';    // an assignment command

class token {
    char kind_;
    double value_;
    std::string name_;

public:
    token(char ch);
    token(double val);
    token(char ch, std::string n);

    char kind() const;
    double value() const;
    std::string getName() const;
};
#endif //CALCULATOR_TOKEN_H
