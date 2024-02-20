#include "token_stream.h"
#include <iostream>
#include <cctype>
#include <stdexcept>

token_stream::token_stream() : full(false), buffer('\0') {}

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
    std::cin >> ch;

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
            std::cin.putback(ch);
            double val;
            std::cin >> val;
            return token(val);
        }
        default:
            if (isalpha(ch)) {
                std::string s;
                s += ch;
                while (std::cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_')) {
                    s += ch;
                }
                std::cin.putback(ch);
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
    while (std::cin >> ch)
        if (ch == c) return;
}
