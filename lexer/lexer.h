//
// Created by root on 08.11.2020.
//

#ifndef CRAINFUCK_LEXER_H
#define CRAINFUCK_LEXER_H

#include "token_type.h"
#include "range.h"

class Token {
    public:
        const Range range;
        const TokenType type;
        const char val;

        Token(const Range& range, TokenType type, char val);
};

class Stream {
    public:
    Token get_next();
    Token predict_next();

    explicit Stream(std::function<Token> factory);

    private:
        const std::function<Token> factory;
        std::optional<Token> shelter;
};

class Lexer {
    public:
        Stream execute();

    protected:
        unsigned long long pos;
        virtual char produce() = 0;
};

#endif //CRAINFUCK_LEXER_H
