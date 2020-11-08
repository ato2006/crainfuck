//
// Created by root on 07.11.2020.
//

#ifndef CRAINFUCK_AST_H
#define CRAINFUCK_AST_H

#include "expression_type.h"
#include <vector>
#include <utility>
#include <memory>

class Visitor;

class Expression {
    public:
        virtual ExpressionType get_type() = 0;
        virtual void set(Visitor* visitor) = 0;
};


class ExpressionOut : Expression {
    public:
        ExpressionType get_type() override {
            return ExpressionType::Out;
        }

        void set(Visitor* visitor) override;
};

class ExpressionIn : Expression {
    public:
        ExpressionType get_type() override {
           return ExpressionType::In;
        }

        void set(Visitor* visitor) override;
};

class ExpressionLeft : Expression {
    public:
        long long amount;

        explicit ExpressionLeft(long long a = 1) : amount(a) {};

        ExpressionType get_type() override {
            return ExpressionType::Left;
        }

        void set(Visitor* visitor) override;
};

class ExpressionRight : Expression {
    public:
        long long amount;

        explicit ExpressionRight(long long a = 1) : amount(a) {};

        ExpressionType get_type() override {
            return ExpressionType::Right;
        }

        void set(Visitor* visitor) override;
};

class ExpressionLoop : Expression {
    public:
        std::vector<std::unique_ptr<Expression>> expr;

        explicit ExpressionLoop(std::vector<std::unique_ptr<Expression>> expr) : expr(std::move(expr)) {}

        ExpressionType get_type() override {
            return ExpressionType::Loop;
        }

        void set(Visitor* visitor) override;
};

class ExpressionIncrement : Expression {
    public:
        long long amount;

        explicit ExpressionIncrement(long long a = 1) : amount(a) {};

        ExpressionType get_type() override {
           return ExpressionType::Increment;
        }

        void set(Visitor* visitor) override;
};

class ExpressionDecrement : Expression {
    public:
        long long amount;

        explicit ExpressionDecrement(long long a = 1) : amount(a) {};

        ExpressionType get_type() override {
            return ExpressionType::Decrement;
        }

        void set(Visitor* visitor) override;
};

class Visitor {
    public:
        virtual void visit(const ExpressionOut* e);
        virtual void visit(const ExpressionIn* e);
        virtual void visit(const ExpressionIncrement* e);
        virtual void visit(const ExpressionDecrement* e);
        virtual void visit(const ExpressionLoop* e);
        virtual void visit(const ExpressionLeft* e);
        virtual void visit(const ExpressionRight* e);
};

class Handler : Visitor {
    protected:
        virtual void expression_in(const ExpressionIn& e);
        virtual void expression_out(const ExpressionOut& e);
        virtual void expression_increment(const ExpressionIncrement& e);
        virtual void expression_decrement(const ExpressionDecrement& e);
        virtual void expression_loop_enter(const ExpressionLoop& e);
        virtual void expression_loop_exit(const ExpressionLoop& e);
        virtual void expression_left(const ExpressionLeft& e);
        virtual void expression_right(const ExpressionRight& e);

    private:
        void visit(const ExpressionOut* e) override {
            expression_out(*e);
        }

        void visit(const ExpressionIn* e) override {
            expression_in(*e);
        }

        void visit(const ExpressionIncrement* e) override {
            expression_increment(*e);
        }

        void visit(const ExpressionDecrement* e) override {
            expression_decrement(*e);
        }

        void visit(const ExpressionLoop* e) override {
            expression_loop_enter(*e);

            for(auto& expr : e->expr) {
                 expr->set(this);
            }

            expression_loop_exit(*e);
         }

        void visit(const ExpressionLeft* e) override {
            expression_left(*e);
        }

        void visit(const ExpressionRight* e) override {
            expression_right(*e);
        }
};

#endif //CRAINFUCK_AST_H
