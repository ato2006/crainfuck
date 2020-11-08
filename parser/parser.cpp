//
// Created by root on 08.11.2020.
//

#include "parser.h"

std::vector<std::unique_ptr<Expression>> Parser::get_all() {
    auto expr = std::vector<std::unique_ptr<Expression>>();

     for (; ;) {
         auto t = stream->predict_next().type;

         if (t != TokenType::End) {

             if (t == TokenType::LeftBracket) {
                 expr.push_back(get_expression_loop());
             } else {
                 expr.push_back(get_expression_single());
             }
             
         } else {break;}
     }

    }