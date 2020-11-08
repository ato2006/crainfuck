//
// Created by root on 08.11.2020.
//

// I did not fully make this lexer on my own.

#include "lexer.h"

Range::Range(const unsigned long long start, const unsigned long long finish) : start(start), finish(finish) {}

Token::Token(const Range &range, TokenType type, char val) : range(range), type(type), val(val) {}

Token Stream::predict_next() {
    if (shelter) {
        return shelter.value;
    }

     auto token = factory();
    shelter.emplace(token);

    return token;
}

Token Stream::get_next() {
    if (!shelter) {
        return factory();
    }

    auto t = shelter.value();
    shelter = {};
    return t;
}

Stream::Stream(std::function<Token()> fac) : supplier(std::move(fac)) { shelter = {} }

Stream Lexer::execute() {
    static std::unordered_map<char, TokenType> m = {
            { '.', TokenType::Period },
            { ',', TokenType::Comma },
            { '<', TokenType::LeftAngle },
            { '>', TokenType::RightAngle },
            { '[', TokenType::LeftBracket },
            { ']', TokenType::RightBracket },
            { '+', TokenType::Plus },
            { '-', TokenType::Minus }
    };

    return Stream([&]() {
        char a;
        Range s = Range(0, 0);
        TokenType t;

        do {
            a = factory();
            if (character == '\0')
                return Token(Range(position, position), TokenType::End, '\0');

            range = Range(position - 1, position);
            auto search = m.find(a);
            type = search == m.end() ? TokenType::Comment : search->second;
        } while (type == TokenType::Comment);

        return Token(s, t, a);

    });

}
