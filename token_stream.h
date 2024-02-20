//
// Created by Ibrahim Alam on 2/20/24.
//

#ifndef CALCULATOR_TOKEN_STREAM_H
#define CALCULATOR_TOKEN_STREAM_H
#include "token.h"

class token_stream {
    bool full;
    token buffer;

public:
    token_stream();

    token get();
    void putback(token t);
    void ignore(char c);
};

#endif //CALCULATOR_TOKEN_STREAM_H
