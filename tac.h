#ifndef TAC_H
#define TAC_H

#include <string>

class TAC {
  protected:
    std::string target = "";
    std::string lhs = "";
    std::string op = "";
    std::string rhs = "";
    std::string tac = "";
    std::string type = "";
  public:
    TAC(std::string target, std::string lhs, std::string op, std::string rhs);
    std::string get_target();
    std::string get_lhs();
    std::string get_op();
    std::string get_rhs();
    std::string get_tac();
    std::string get_type();
};

class Expression : public TAC {
  public:
    Expression(std::string target, std::string lhs, std::string op, std::string rhs);
};

class UnaryExpression : public TAC {
  public:
    UnaryExpression(std::string target, std::string op, std::string rhs);
};

class Copy : public TAC {
  public:
    Copy(std::string target, std::string lhs);
};

class CopyArray : public TAC {
  public:
    CopyArray(std::string target, std::string lhs, std::string rhs);
};

class MethodCall : public TAC {
  public:
    MethodCall(std::string target, std::string f, std::string N);
};

class Condition : public TAC {
  public:
    Condition(std::string target);
};

class Length : public TAC {
  public:
    Length(std::string target, std::string lhs);
};

class Parameter_cfg : public TAC {
  public:
    Parameter_cfg(std::string target);
};

class Argument : public TAC {
  public:
    Argument(std::string target);
};

class Return : public TAC {
  public:
    Return(std::string target);
};

class Print : public TAC {
  public:
    Print(std::string target);
};

#endif