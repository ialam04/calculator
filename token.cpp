#include "token.h"

token::token(char ch) : kind_(ch), value_(0) {}
token::token(double val) : kind_(number), value_(val) {}
token::token(char ch, std::string n) : kind_(ch), value_(0), name_(n) {}

char token::kind() const{
    return kind_;
}
double token::value() const {
    return value_;
}
std::string token::getName() const {
    return name_;
}
