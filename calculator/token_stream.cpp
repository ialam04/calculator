//
// Created by Ibrahim Alam on 2/20/24.
//

#include "token_stream.h"
#include <iostream>
#include <cctype>
#include <stdexcept>

token_stream::token_stream(std::istream& is) : full(false), buffer('\0'), input(is) {}

void token_stream::putback(token t) {
    if (full) throw std::runtime_error("putback() into a full buffer");
    buffer = t;
    full = true;
}

token token_stream::get() {
    if (full) {
        full = false;
        return buffer;
    }

    char ch;
    input >> ch;

    switch (ch) {
        case print:
        case quit:
        case '(':
        case ')':
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
        case assign:
            return token(ch);
        case '.':
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9': {
            input.putback(ch);
            double val;
            input >> val;
            return token(val);
        }
        default:
            if (isalpha(ch)) {
                std::string s;
                s += ch;
                while (std::cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_')) {
                    s += ch;
                }
                input.putback(ch);
                if (s == "let") {
                    return token(name, s);
                }
                else {
                    return token(name, s);
                }
            }
            throw std::runtime_error("Bad token");
    }
}

void token_stream::ignore(char c) {
    if (full && c == buffer.kind()) {
        full = false;
        return;
    }
    full = false;

    char ch = 0;
    while (input >> ch)
        if (ch == c) return;
}