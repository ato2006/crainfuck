//
// Created by root on 08.11.2020.
//

#ifndef CRAINFUCK_PARSER_H
#define CRAINFUCK_PARSER_H

#include "../ast/ast.h"
#include "../lexer/lexer.h"

class Parser {
    public:
        explicit Parser(Stream* str);

        std::vector<std::unique_ptr<Expression>> get_all();
        std::unique_ptr<Expression> get_expression_single();
        std::unique_ptr<ExpressionLoop> get_expression_loop();

    private:
        Stream* stream;
};

#endif //CRAINFUCK_PARSER_H
