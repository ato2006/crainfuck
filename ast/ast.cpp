//
// Created by root on 07.11.2020.
//

#include "ast.h"

void ExpressionOut::set(Visitor* visitor) {
    visitor->visit(this);
}

void ExpressionIn::set(Visitor* visitor) {
    visitor->visit(this);
}

void ExpressionLeft::set(Visitor* visitor) {
    visitor->visit(this);
}

void ExpressionRight::set(Visitor* visitor) {
    visitor->visit(this);
}

void ExpressionIncrement::set(Visitor* visitor) {
    visitor->visit(this);
}

void ExpressionDecrement::set(Visitor* visitor) {
    visitor->visit(this);
}

void ExpressionLoop::set(Visitor* visitor) {
    visitor->visit(this);
}
