%skeleton "lalr1.cc" 
%defines
%define parse.error verbose
%define api.value.type variant
%define api.token.constructor

%code requires{
  #include <string>
  #include "Node.h"
  #define USE_LEX_ONLY false //change this macro to true if you want to isolate the lexer from the parser.
}

%code{
  #define YY_DECL yy::parser::symbol_type yylex()
  YY_DECL;

  Node* root;
  extern int yylineno;
}

// Definition of set of tokens. All tokens are of type string
%token <std::string> ASSIGN AND OR EQ LT GT ADD SUB MUL DIV NOT LP RP LBRACKET RBRACKET SEMI COMMA DOT CLASS MAIN PUBLIC STATIC VOID IF ELSE WHILE PRINTLN RETURN INT BOOLEAN TRUE FALSE THIS NEW LENGTH INT_LITERAL IDENTIFIER STRING LHB RHB
%token END 0    // End of file

// Operator precedence definitions
%left OR
%left AND
%left EQ LT GT
%left ADD SUB
%left MUL DIV
%right NOT
%left LHB RHB
%left DOT
%left LENGTH
%left NEW
%left THIS
%left INT_LITERAL
%left IDENTIFIER
%left STRING
%left ASSIGN
%left LP RP
%left LBRACKET RBRACKET
%left SEMI COMMA
%left IF ELSE WHILE PRINTLN RETURN INT BOOLEAN TRUE FALSE VOID
%left CLASS MAIN PUBLIC STATIC

// Definition of the production rules. All production rules are of type Node
%type <Node *> Goal MainClass ClassDeclaration VarDeclaration 
%type <Node *> MethodDeclaration VarType Statement Expression Identifier
%type <Node *> ClassDeclarationList VarDeclarationList 
%type <Node *> MethodDeclarationList TypeIdentifierList 
%type <Node *> root MainClassMethod MainClassBody TypeIdentifier BlockContent
%type <Node *> VariableAndStatement VariablesAndStatementList Return 
%type <Node *> StatementList StatementsNonEmpty 
%type <Node *> OrExpression AndExpression EqualExpression CompareExpression 
%type <Node *> AddSubExpression MulDivExpression NotExpression 
%type <Node *> BaseExpression ExpressionList ExpressionsNonEmpty 
%type <Node *> Int

%%

root: Goal { root = $1; }
    ;

Goal:       MainClass ClassDeclarationList END { $$ = new Node("Global", "", yylineno); $$->children.push_back($1); $$->children.push_back($2); /* printf("r1 "); */ }
            ;


MainClass:
    PUBLIC CLASS Identifier LBRACKET MainClassMethod RBRACKET {
        $$ = new Node("MainClass", $3->value, yylineno);
        $$->children.push_back($5);
    }
    ;

MainClassMethod:
    PUBLIC STATIC VOID MAIN LP STRING LHB RHB Identifier RP LBRACKET MainClassBody RBRACKET {
        $$ = new Node("MethodDeclaration", "main", yylineno);
        Node* TypeIdentifierList = new Node("TypeIdentifierList", "", yylineno);
        Node* TypeIdentifier = new Node("TypeIdentifier", "", $9->lineno);
        

        TypeIdentifier->children.push_back(new Node("StringList", "", $9->lineno));
        TypeIdentifier->children.push_back(new Node("Identifier", $9->value, $9->lineno));
        

        TypeIdentifierList->children.push_back(TypeIdentifier);

        $$->children.push_back(new Node("Void", "", yylineno));
        $$->children.push_back(TypeIdentifierList);
        $$->children.push_back($12);
    }
    ;

MainClassBody:
      Statement { 
          $$ = new Node("BlockContent", "", yylineno); 
          $$->children.push_back($1); 
      }
    | MainClassBody Statement { 
          $$ = $1; 
          $$->children.push_back($2); 
      }
    ;

ClassDeclaration:
    CLASS Identifier LBRACKET RBRACKET { 
        $$ = new Node("ClassDeclaration", $2->value, yylineno); 
    }
  | CLASS Identifier LBRACKET VarDeclarationList MethodDeclarationList RBRACKET {
        $$ = new Node("ClassDeclaration", $2->value, $2->lineno); 
        for(auto child : $4->children) {
            $$->children.push_back(child);
        }
        for(auto child : $5->children) {
            $$->children.push_back(child);
        }
    }
    ;

ClassDeclarationList:
    { $$ = new Node("ClassDeclarationList", "", yylineno); }
    | ClassDeclaration { 
          $$ = new Node("ClassDeclarationList", "", yylineno); 
          $$->children.push_back($1); 
      }
    | ClassDeclarationList ClassDeclaration { 
          $$ = $1; 
          $$->children.push_back($2); 
      }
    ;


MethodDeclaration:
    PUBLIC VarType Identifier LP TypeIdentifierList RP BlockContent { 
        $$ = new Node("MethodDeclaration", $3->value, $3->lineno); 
        $$->children.push_back($2);
        $$->children.push_back($5);
        $$->children.push_back($7);
    }
    ;

MethodDeclarationList:
    { $$ = new Node("MethodDeclarationList", "", yylineno); }
    | MethodDeclaration { 
          $$ = new Node("MethodDeclarationList", "", yylineno); 
          $$->children.push_back($1); 
      }
    | MethodDeclarationList MethodDeclaration { 
          $$ = $1; 
          $$->children.push_back($2); 
      }
    ;

BlockContent:
    LBRACKET Return RBRACKET { 
        $$ = new Node("BlockContent", "", yylineno); 
        $$->children.push_back($2); 
    }
  | LBRACKET VariablesAndStatementList Return RBRACKET { 
        $$ = new Node("BlockContent", "", yylineno); 
        
        for(auto child : $2->children) {
            $$->children.push_back(child);
        }
        
        $$->children.push_back($3); 
    }
    ;


TypeIdentifier:
    VarType Identifier { 
        $$ = new Node("TypeIdentifier", "", yylineno);
        $$->children.push_back($1); 
        $$->children.push_back($2); 
    }
    ;

TypeIdentifierList:
    { $$ = new Node("TypeIdentifierList", "", yylineno); }
    | TypeIdentifier { 
          $$ = new Node("TypeIdentifierList", "", yylineno); 
          $$->children.push_back($1); 
      }
    | TypeIdentifierList COMMA TypeIdentifier { 
          $$ = $1; 
          $$->children.push_back($3); 
      }
    ;

VarType:
    INT LHB RHB { 
        $$ = new Node("IntArray", "", yylineno); 
    }
  | BOOLEAN { 
        $$ = new Node("Boolean", "", yylineno); 
    }
  | INT { 
        $$ = new Node("Int", "", yylineno); 
    }
  | Identifier { 
        $$ = new Node("Identifier", $1->value, yylineno); 
    }
    ;

VarDeclaration:
    VarType Identifier SEMI { 
        $$ = new Node("VarDeclaration", "", yylineno); 
        $$->children.push_back($1); 
        $$->children.push_back($2); 
    }
    ;

VarDeclarationList:
    { $$ = new Node("VarDeclarationList", "", yylineno); }
    | VarDeclaration { 
          $$ = new Node("VarDeclarationList", "", yylineno); 
          $$->children.push_back($1); 
      }
    | VarDeclarationList VarDeclaration { 
          $$ = $1; 
          $$->children.push_back($2); 
      }
    ;

VariableAndStatement:
    VarDeclaration { $$ = $1; }
  | Statement { $$ = $1; }
    ;

VariablesAndStatementList:
    VariableAndStatement { 
        $$ = new Node("VariablesAndStatementList", "", yylineno); 
        $$->children.push_back($1); 
    }
  | VariablesAndStatementList VariableAndStatement { 
        $$ = $1; 
        $$->children.push_back($2); 
    }
    ;

Statement:
      LBRACKET RBRACKET { 
          $$ = new Node("BlockContent", "", yylineno); 
      }
    | LBRACKET StatementList RBRACKET { 
          $$ = new Node("BlockContent", "", yylineno); 
          $$->children.push_back($2); 
      }
    | IF LP Expression RP Statement { 
          $$ = new Node("IfStatement", "", yylineno); 
          $$->children.push_back($3); 
          $$->children.push_back($5); 
      }
    | IF LP Expression RP Statement ELSE Statement { 
          $$ = new Node("IfElseStatement", "", yylineno); 
          $$->children.push_back($3); 
          $$->children.push_back($5); 
          $$->children.push_back($7); 
      }
    | WHILE LP Expression RP Statement { 
          $$ = new Node("WhileStatement", "", yylineno); 
          $$->children.push_back($3); 
          $$->children.push_back($5); 
      }
    | PRINTLN LP Expression RP SEMI { 
          $$ = new Node("PrintlnStatement", "", yylineno); 
          $$->children.push_back($3); 
      }
    | Identifier ASSIGN Expression SEMI { 
          $$ = new Node("AssignStatement", "", yylineno); 
          $$->children.push_back($1); 
          $$->children.push_back($3); 
      }
    | Identifier LHB Expression RHB ASSIGN Expression SEMI { 
          $$ = new Node("ArrayAssignStatement", "", yylineno); 
          $$->children.push_back($1); 
          $$->children.push_back($3); 
          $$->children.push_back($6); 
      }
    ;


StatementList:
    { $$ = new Node("StatementList", "", yylineno); }
    | StatementsNonEmpty { $$ = $1; }
    ;

StatementsNonEmpty:
      Statement { 
          $$ = new Node("StatementList", "", yylineno); 
          $$->children.push_back($1); 
      }
    | StatementsNonEmpty Statement { 
          $$ = $1; 
          $$->children.push_back($2); 
      }
    ;

Expression:
    OrExpression { $$ = $1; }
    ;

OrExpression:
    OrExpression OR AndExpression { 
        $$ = new Node("OrExpression", "", yylineno); 
        $$->children.push_back($1); 
        $$->children.push_back($3); 
    }
  | AndExpression { $$ = $1; }
    ;

AndExpression:
    AndExpression AND EqualExpression { 
        $$ = new Node("AndExpression", "", yylineno); 
        $$->children.push_back($1); 
        $$->children.push_back($3); 
    }
  | EqualExpression { $$ = $1; }
    ;

EqualExpression:
    EqualExpression EQ CompareExpression { 
        $$ = new Node("EqualExpression", "", yylineno); 
        $$->children.push_back($1); 
        $$->children.push_back($3); 
    }
  | CompareExpression { $$ = $1; }
    ;

CompareExpression:
    CompareExpression LT AddSubExpression { 
        $$ = new Node("LessThanExpression", "", yylineno); 
        $$->children.push_back($1); 
        $$->children.push_back($3); 
    }
  | CompareExpression GT AddSubExpression { 
        $$ = new Node("GreaterThanExpression", "", yylineno); 
        $$->children.push_back($1); 
        $$->children.push_back($3); 
    }
  | AddSubExpression { $$ = $1; }
    ;

AddSubExpression:
    AddSubExpression ADD MulDivExpression { 
        $$ = new Node("AddExpression", "", yylineno); 
        $$->children.push_back($1); 
        $$->children.push_back($3); 
    }
  | AddSubExpression SUB MulDivExpression { 
        $$ = new Node("SubExpression", "", yylineno); 
        $$->children.push_back($1); 
        $$->children.push_back($3); 
    }
  | MulDivExpression { $$ = $1; }
    ;

MulDivExpression:
    MulDivExpression MUL NotExpression { 
        $$ = new Node("MulExpression", "", yylineno); 
        $$->children.push_back($1); 
        $$->children.push_back($3); 
    }
  | MulDivExpression DIV NotExpression { 
        $$ = new Node("DivExpression", "", yylineno); 
        $$->children.push_back($1); 
        $$->children.push_back($3); 
    }
  | NotExpression { $$ = $1; }
    ;

NotExpression:
    NOT BaseExpression { 
        $$ = new Node("NotExpression", "", yylineno); 
        $$->children.push_back($2); 
    }
  | BaseExpression { $$ = $1; }
    ;

BaseExpression:
    NEW Identifier LP RP { $$ = new Node("NewObjectExpression", $2->value, yylineno); }
  | BaseExpression LHB Expression RHB { 
        $$ = new Node("ArrayAccess", "", yylineno); 
        $$->children.push_back($1); 
        $$->children.push_back($3); 
    }
  | BaseExpression DOT LENGTH { 
        $$ = new Node("ArrayLength", "", yylineno); 
        $$->children.push_back($1); 
    }
  | BaseExpression DOT Identifier LP ExpressionList RP { 
        $$ = new Node("MethodCallExpression", "", yylineno); 
        $$->children.push_back($1); 
        $$->children.push_back($3); 
        if($5 != nullptr) $$->children.push_back($5); 
    }
  | TRUE { 
        $$ = new Node("TrueExpression", "", yylineno); 
    }
  | FALSE { 
        $$ = new Node("FalseExpression", "", yylineno); 
    }
  | THIS { 
        $$ = new Node("ThisExpression", "", yylineno); 
    }
  | NEW INT LHB Expression RHB { 
        $$ = new Node("NewArray", "", yylineno); 
        $$->children.push_back($4); 
    }
  | LP Expression RP { 
        $$ = new Node("Expression", "", yylineno); 
        $$->children.push_back($2); 
    }
  | Int { $$ = $1; }
  | Identifier { $$ = $1; }
    ;

ExpressionList:
    { $$ = new Node("ExpressionList", "", yylineno); }
    | ExpressionsNonEmpty { $$ = $1; }
    ;

ExpressionsNonEmpty:
      Expression { 
          $$ = new Node("ExpressionList", "", yylineno); 
          $$->children.push_back($1); 
      }
    | ExpressionsNonEmpty COMMA Expression { 
          $$ = $1; 
          $$->children.push_back($3); 
      }
    ;


Identifier:
    IDENTIFIER { 
        $$ = new Node("Identifier", $1, yylineno); 
    }
    ;

Return:
    RETURN Expression SEMI { 
        $$ = new Node("Return", "", yylineno); 
        $$->children.push_back($2); 
    }
    ;

Int:
    INT_LITERAL { 
        $$ = new Node("Int", $1, yylineno); 
    }
  | SUB INT_LITERAL { 
        $$ = new Node("SubInt", "-" + $2, yylineno); 
    }
    ;

%%