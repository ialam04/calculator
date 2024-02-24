//
// Created by Ibrahim Alam on 2/20/24.
//

#ifndef CALCULATOR_TOKEN_STREAM_H
#define CALCULATOR_TOKEN_STREAM_H
#include "token.h"
#include <istream>
#include <iostream>

class token_stream {
    bool full;
    token buffer;
    std::istream& input;

public:
    explicit token_stream(std::istream& is = std::cin);

    token get();
    void putback(token t);
    void ignore(char c);
    bool is_end() const {
        return input.eof();
    }
    void clear() {
        input.clear();
    }
};

#endif //CALCULATOR_TOKEN_STREAM_H //CALCULATOR_TOKEN_STREAM_H
