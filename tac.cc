#include <iostream>
#include "tac.h"

// ---------- CONSTRUCTORS ----------

TAC::TAC(std::string t, std::string l, std::string o, std::string r)
    : target(t), lhs(l), op(o), rhs(r), tac(""), type("") {
}

// ---------- METHODS ----------

std::string TAC::get_target() {
    return target;
}

std::string TAC::get_lhs() {
    return lhs;
}

std::string TAC::get_op() {
    return op;
}

std::string TAC::get_rhs() {
    return rhs;
}

std::string TAC::get_tac() {
    return tac;
}

std::string TAC::get_type() {
    return type;
}

// ---------- EXPRESSION ----------

Expression::Expression(std::string t, std::string l, std::string o, std::string r)
    : TAC(t, l, o, r) {
    type = "Expression";
    tac = target + " := " + lhs + " " + op + " " + rhs;
}

// ---------- UNARY EXPRESSION ----------

UnaryExpression::UnaryExpression(std::string t, std::string o, std::string r)
    : TAC(t, "", o, r) {
    type = "UnaryExpression";
    tac = target + " := " + op + " " + rhs;
}

// ---------- COPY ----------

Copy::Copy(std::string t, std::string l)
    : TAC(t, l, "", "") {
    type = "Copy";
    tac = target + " := " + lhs;
}

// ---------- COPY ARRAY ----------

CopyArray::CopyArray(std::string t, std::string l, std::string r)
    : TAC(t, l, "CopyArray", r) {
    type = "CopyArray";
    tac = target + "[" + lhs + "] := " + rhs;
}

// ---------- METHOD CALL ----------

MethodCall::MethodCall(std::string t, std::string f, std::string N)
    : TAC(t, f, "call", N) {
    type = "MethodCall";
    tac = target + " := " + op + " " + lhs;
}

// ---------- CONDITION ----------

Condition::Condition(std::string label)
    : TAC(label, "", "", "") {
    type = "Condition";
    tac = "cmp " + target + ", 1";
}

// ---------- LENGTH ----------

Length::Length(std::string t, std::string l)
    : TAC(t, l, "length", "") {
    type = "Length";
    tac = target + " := " + op + " " + lhs;
}

// ---------- PARAMETER ----------

Parameter_cfg::Parameter_cfg(std::string t)
    : TAC(t, "", "param", "") {
    type = "Parameter";
    tac = op + " " + target;
}

// ---------- ARGUMENT ----------

Argument::Argument(std::string t)
    : TAC(t, "", "arg", "") {
    type = "Argument";
    tac = op + " " + target;
}

// ---------- RETURN ----------

Return::Return(std::string t)
    : TAC(t, "", "return", "") {
    type = "Return";
    tac = op + " " + target;
}

// ---------- PRINT ----------

Print::Print(std::string t)
    : TAC(t, "", "print", "") {
    type = "Print";
    tac = op + " " + target;
}
