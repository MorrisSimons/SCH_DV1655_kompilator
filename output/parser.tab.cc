// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.





#include "parser.tab.hh"


// Unqualified %code blocks.
#line 13 "parser.yy"

  #define YY_DECL yy::parser::symbol_type yylex()
  YY_DECL;

  Node* root;
  extern int yylineno;

#line 54 "./output/parser.tab.cc"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif



// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace yy {
#line 127 "./output/parser.tab.cc"

  /// Build a parser object.
  parser::parser ()
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr)
#else

#endif
  {}

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/



  // by_state.
  parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  parser::symbol_kind_type
  parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_root: // root
      case symbol_kind::S_Goal: // Goal
      case symbol_kind::S_MainClass: // MainClass
      case symbol_kind::S_MainClassMethod: // MainClassMethod
      case symbol_kind::S_MainClassBody: // MainClassBody
      case symbol_kind::S_ClassDeclaration: // ClassDeclaration
      case symbol_kind::S_ClassDeclarationList: // ClassDeclarationList
      case symbol_kind::S_MethodDeclaration: // MethodDeclaration
      case symbol_kind::S_MethodDeclarationList: // MethodDeclarationList
      case symbol_kind::S_BlockContent: // BlockContent
      case symbol_kind::S_TypeIdentifier: // TypeIdentifier
      case symbol_kind::S_TypeIdentifierList: // TypeIdentifierList
      case symbol_kind::S_VarType: // VarType
      case symbol_kind::S_VarDeclaration: // VarDeclaration
      case symbol_kind::S_VarDeclarationList: // VarDeclarationList
      case symbol_kind::S_VariableAndStatement: // VariableAndStatement
      case symbol_kind::S_VariablesAndStatementList: // VariablesAndStatementList
      case symbol_kind::S_Statement: // Statement
      case symbol_kind::S_StatementList: // StatementList
      case symbol_kind::S_StatementsNonEmpty: // StatementsNonEmpty
      case symbol_kind::S_Expression: // Expression
      case symbol_kind::S_OrExpression: // OrExpression
      case symbol_kind::S_AndExpression: // AndExpression
      case symbol_kind::S_EqualExpression: // EqualExpression
      case symbol_kind::S_CompareExpression: // CompareExpression
      case symbol_kind::S_AddSubExpression: // AddSubExpression
      case symbol_kind::S_MulDivExpression: // MulDivExpression
      case symbol_kind::S_NotExpression: // NotExpression
      case symbol_kind::S_BaseExpression: // BaseExpression
      case symbol_kind::S_ExpressionList: // ExpressionList
      case symbol_kind::S_ExpressionsNonEmpty: // ExpressionsNonEmpty
      case symbol_kind::S_Identifier: // Identifier
      case symbol_kind::S_Return: // Return
      case symbol_kind::S_Int: // Int
        value.YY_MOVE_OR_COPY< Node * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ASSIGN: // ASSIGN
      case symbol_kind::S_AND: // AND
      case symbol_kind::S_OR: // OR
      case symbol_kind::S_EQ: // EQ
      case symbol_kind::S_LT: // LT
      case symbol_kind::S_GT: // GT
      case symbol_kind::S_ADD: // ADD
      case symbol_kind::S_SUB: // SUB
      case symbol_kind::S_MUL: // MUL
      case symbol_kind::S_DIV: // DIV
      case symbol_kind::S_NOT: // NOT
      case symbol_kind::S_LP: // LP
      case symbol_kind::S_RP: // RP
      case symbol_kind::S_LBRACKET: // LBRACKET
      case symbol_kind::S_RBRACKET: // RBRACKET
      case symbol_kind::S_SEMI: // SEMI
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_DOT: // DOT
      case symbol_kind::S_CLASS: // CLASS
      case symbol_kind::S_MAIN: // MAIN
      case symbol_kind::S_PUBLIC: // PUBLIC
      case symbol_kind::S_STATIC: // STATIC
      case symbol_kind::S_VOID: // VOID
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_WHILE: // WHILE
      case symbol_kind::S_PRINTLN: // PRINTLN
      case symbol_kind::S_RETURN: // RETURN
      case symbol_kind::S_INT: // INT
      case symbol_kind::S_BOOLEAN: // BOOLEAN
      case symbol_kind::S_TRUE: // TRUE
      case symbol_kind::S_FALSE: // FALSE
      case symbol_kind::S_THIS: // THIS
      case symbol_kind::S_NEW: // NEW
      case symbol_kind::S_LENGTH: // LENGTH
      case symbol_kind::S_INT_LITERAL: // INT_LITERAL
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRING: // STRING
      case symbol_kind::S_LHB: // LHB
      case symbol_kind::S_RHB: // RHB
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s)
  {
    switch (that.kind ())
    {
      case symbol_kind::S_root: // root
      case symbol_kind::S_Goal: // Goal
      case symbol_kind::S_MainClass: // MainClass
      case symbol_kind::S_MainClassMethod: // MainClassMethod
      case symbol_kind::S_MainClassBody: // MainClassBody
      case symbol_kind::S_ClassDeclaration: // ClassDeclaration
      case symbol_kind::S_ClassDeclarationList: // ClassDeclarationList
      case symbol_kind::S_MethodDeclaration: // MethodDeclaration
      case symbol_kind::S_MethodDeclarationList: // MethodDeclarationList
      case symbol_kind::S_BlockContent: // BlockContent
      case symbol_kind::S_TypeIdentifier: // TypeIdentifier
      case symbol_kind::S_TypeIdentifierList: // TypeIdentifierList
      case symbol_kind::S_VarType: // VarType
      case symbol_kind::S_VarDeclaration: // VarDeclaration
      case symbol_kind::S_VarDeclarationList: // VarDeclarationList
      case symbol_kind::S_VariableAndStatement: // VariableAndStatement
      case symbol_kind::S_VariablesAndStatementList: // VariablesAndStatementList
      case symbol_kind::S_Statement: // Statement
      case symbol_kind::S_StatementList: // StatementList
      case symbol_kind::S_StatementsNonEmpty: // StatementsNonEmpty
      case symbol_kind::S_Expression: // Expression
      case symbol_kind::S_OrExpression: // OrExpression
      case symbol_kind::S_AndExpression: // AndExpression
      case symbol_kind::S_EqualExpression: // EqualExpression
      case symbol_kind::S_CompareExpression: // CompareExpression
      case symbol_kind::S_AddSubExpression: // AddSubExpression
      case symbol_kind::S_MulDivExpression: // MulDivExpression
      case symbol_kind::S_NotExpression: // NotExpression
      case symbol_kind::S_BaseExpression: // BaseExpression
      case symbol_kind::S_ExpressionList: // ExpressionList
      case symbol_kind::S_ExpressionsNonEmpty: // ExpressionsNonEmpty
      case symbol_kind::S_Identifier: // Identifier
      case symbol_kind::S_Return: // Return
      case symbol_kind::S_Int: // Int
        value.move< Node * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ASSIGN: // ASSIGN
      case symbol_kind::S_AND: // AND
      case symbol_kind::S_OR: // OR
      case symbol_kind::S_EQ: // EQ
      case symbol_kind::S_LT: // LT
      case symbol_kind::S_GT: // GT
      case symbol_kind::S_ADD: // ADD
      case symbol_kind::S_SUB: // SUB
      case symbol_kind::S_MUL: // MUL
      case symbol_kind::S_DIV: // DIV
      case symbol_kind::S_NOT: // NOT
      case symbol_kind::S_LP: // LP
      case symbol_kind::S_RP: // RP
      case symbol_kind::S_LBRACKET: // LBRACKET
      case symbol_kind::S_RBRACKET: // RBRACKET
      case symbol_kind::S_SEMI: // SEMI
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_DOT: // DOT
      case symbol_kind::S_CLASS: // CLASS
      case symbol_kind::S_MAIN: // MAIN
      case symbol_kind::S_PUBLIC: // PUBLIC
      case symbol_kind::S_STATIC: // STATIC
      case symbol_kind::S_VOID: // VOID
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_WHILE: // WHILE
      case symbol_kind::S_PRINTLN: // PRINTLN
      case symbol_kind::S_RETURN: // RETURN
      case symbol_kind::S_INT: // INT
      case symbol_kind::S_BOOLEAN: // BOOLEAN
      case symbol_kind::S_TRUE: // TRUE
      case symbol_kind::S_FALSE: // FALSE
      case symbol_kind::S_THIS: // THIS
      case symbol_kind::S_NEW: // NEW
      case symbol_kind::S_LENGTH: // LENGTH
      case symbol_kind::S_INT_LITERAL: // INT_LITERAL
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRING: // STRING
      case symbol_kind::S_LHB: // LHB
      case symbol_kind::S_RHB: // RHB
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_root: // root
      case symbol_kind::S_Goal: // Goal
      case symbol_kind::S_MainClass: // MainClass
      case symbol_kind::S_MainClassMethod: // MainClassMethod
      case symbol_kind::S_MainClassBody: // MainClassBody
      case symbol_kind::S_ClassDeclaration: // ClassDeclaration
      case symbol_kind::S_ClassDeclarationList: // ClassDeclarationList
      case symbol_kind::S_MethodDeclaration: // MethodDeclaration
      case symbol_kind::S_MethodDeclarationList: // MethodDeclarationList
      case symbol_kind::S_BlockContent: // BlockContent
      case symbol_kind::S_TypeIdentifier: // TypeIdentifier
      case symbol_kind::S_TypeIdentifierList: // TypeIdentifierList
      case symbol_kind::S_VarType: // VarType
      case symbol_kind::S_VarDeclaration: // VarDeclaration
      case symbol_kind::S_VarDeclarationList: // VarDeclarationList
      case symbol_kind::S_VariableAndStatement: // VariableAndStatement
      case symbol_kind::S_VariablesAndStatementList: // VariablesAndStatementList
      case symbol_kind::S_Statement: // Statement
      case symbol_kind::S_StatementList: // StatementList
      case symbol_kind::S_StatementsNonEmpty: // StatementsNonEmpty
      case symbol_kind::S_Expression: // Expression
      case symbol_kind::S_OrExpression: // OrExpression
      case symbol_kind::S_AndExpression: // AndExpression
      case symbol_kind::S_EqualExpression: // EqualExpression
      case symbol_kind::S_CompareExpression: // CompareExpression
      case symbol_kind::S_AddSubExpression: // AddSubExpression
      case symbol_kind::S_MulDivExpression: // MulDivExpression
      case symbol_kind::S_NotExpression: // NotExpression
      case symbol_kind::S_BaseExpression: // BaseExpression
      case symbol_kind::S_ExpressionList: // ExpressionList
      case symbol_kind::S_ExpressionsNonEmpty: // ExpressionsNonEmpty
      case symbol_kind::S_Identifier: // Identifier
      case symbol_kind::S_Return: // Return
      case symbol_kind::S_Int: // Int
        value.copy< Node * > (that.value);
        break;

      case symbol_kind::S_ASSIGN: // ASSIGN
      case symbol_kind::S_AND: // AND
      case symbol_kind::S_OR: // OR
      case symbol_kind::S_EQ: // EQ
      case symbol_kind::S_LT: // LT
      case symbol_kind::S_GT: // GT
      case symbol_kind::S_ADD: // ADD
      case symbol_kind::S_SUB: // SUB
      case symbol_kind::S_MUL: // MUL
      case symbol_kind::S_DIV: // DIV
      case symbol_kind::S_NOT: // NOT
      case symbol_kind::S_LP: // LP
      case symbol_kind::S_RP: // RP
      case symbol_kind::S_LBRACKET: // LBRACKET
      case symbol_kind::S_RBRACKET: // RBRACKET
      case symbol_kind::S_SEMI: // SEMI
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_DOT: // DOT
      case symbol_kind::S_CLASS: // CLASS
      case symbol_kind::S_MAIN: // MAIN
      case symbol_kind::S_PUBLIC: // PUBLIC
      case symbol_kind::S_STATIC: // STATIC
      case symbol_kind::S_VOID: // VOID
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_WHILE: // WHILE
      case symbol_kind::S_PRINTLN: // PRINTLN
      case symbol_kind::S_RETURN: // RETURN
      case symbol_kind::S_INT: // INT
      case symbol_kind::S_BOOLEAN: // BOOLEAN
      case symbol_kind::S_TRUE: // TRUE
      case symbol_kind::S_FALSE: // FALSE
      case symbol_kind::S_THIS: // THIS
      case symbol_kind::S_NEW: // NEW
      case symbol_kind::S_LENGTH: // LENGTH
      case symbol_kind::S_INT_LITERAL: // INT_LITERAL
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRING: // STRING
      case symbol_kind::S_LHB: // LHB
      case symbol_kind::S_RHB: // RHB
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_root: // root
      case symbol_kind::S_Goal: // Goal
      case symbol_kind::S_MainClass: // MainClass
      case symbol_kind::S_MainClassMethod: // MainClassMethod
      case symbol_kind::S_MainClassBody: // MainClassBody
      case symbol_kind::S_ClassDeclaration: // ClassDeclaration
      case symbol_kind::S_ClassDeclarationList: // ClassDeclarationList
      case symbol_kind::S_MethodDeclaration: // MethodDeclaration
      case symbol_kind::S_MethodDeclarationList: // MethodDeclarationList
      case symbol_kind::S_BlockContent: // BlockContent
      case symbol_kind::S_TypeIdentifier: // TypeIdentifier
      case symbol_kind::S_TypeIdentifierList: // TypeIdentifierList
      case symbol_kind::S_VarType: // VarType
      case symbol_kind::S_VarDeclaration: // VarDeclaration
      case symbol_kind::S_VarDeclarationList: // VarDeclarationList
      case symbol_kind::S_VariableAndStatement: // VariableAndStatement
      case symbol_kind::S_VariablesAndStatementList: // VariablesAndStatementList
      case symbol_kind::S_Statement: // Statement
      case symbol_kind::S_StatementList: // StatementList
      case symbol_kind::S_StatementsNonEmpty: // StatementsNonEmpty
      case symbol_kind::S_Expression: // Expression
      case symbol_kind::S_OrExpression: // OrExpression
      case symbol_kind::S_AndExpression: // AndExpression
      case symbol_kind::S_EqualExpression: // EqualExpression
      case symbol_kind::S_CompareExpression: // CompareExpression
      case symbol_kind::S_AddSubExpression: // AddSubExpression
      case symbol_kind::S_MulDivExpression: // MulDivExpression
      case symbol_kind::S_NotExpression: // NotExpression
      case symbol_kind::S_BaseExpression: // BaseExpression
      case symbol_kind::S_ExpressionList: // ExpressionList
      case symbol_kind::S_ExpressionsNonEmpty: // ExpressionsNonEmpty
      case symbol_kind::S_Identifier: // Identifier
      case symbol_kind::S_Return: // Return
      case symbol_kind::S_Int: // Int
        value.move< Node * > (that.value);
        break;

      case symbol_kind::S_ASSIGN: // ASSIGN
      case symbol_kind::S_AND: // AND
      case symbol_kind::S_OR: // OR
      case symbol_kind::S_EQ: // EQ
      case symbol_kind::S_LT: // LT
      case symbol_kind::S_GT: // GT
      case symbol_kind::S_ADD: // ADD
      case symbol_kind::S_SUB: // SUB
      case symbol_kind::S_MUL: // MUL
      case symbol_kind::S_DIV: // DIV
      case symbol_kind::S_NOT: // NOT
      case symbol_kind::S_LP: // LP
      case symbol_kind::S_RP: // RP
      case symbol_kind::S_LBRACKET: // LBRACKET
      case symbol_kind::S_RBRACKET: // RBRACKET
      case symbol_kind::S_SEMI: // SEMI
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_DOT: // DOT
      case symbol_kind::S_CLASS: // CLASS
      case symbol_kind::S_MAIN: // MAIN
      case symbol_kind::S_PUBLIC: // PUBLIC
      case symbol_kind::S_STATIC: // STATIC
      case symbol_kind::S_VOID: // VOID
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_WHILE: // WHILE
      case symbol_kind::S_PRINTLN: // PRINTLN
      case symbol_kind::S_RETURN: // RETURN
      case symbol_kind::S_INT: // INT
      case symbol_kind::S_BOOLEAN: // BOOLEAN
      case symbol_kind::S_TRUE: // TRUE
      case symbol_kind::S_FALSE: // FALSE
      case symbol_kind::S_THIS: // THIS
      case symbol_kind::S_NEW: // NEW
      case symbol_kind::S_LENGTH: // LENGTH
      case symbol_kind::S_INT_LITERAL: // INT_LITERAL
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRING: // STRING
      case symbol_kind::S_LHB: // LHB
      case symbol_kind::S_RHB: // RHB
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " (";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::operator() ()
  {
    return parse ();
  }

  int
  parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex ());
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_root: // root
      case symbol_kind::S_Goal: // Goal
      case symbol_kind::S_MainClass: // MainClass
      case symbol_kind::S_MainClassMethod: // MainClassMethod
      case symbol_kind::S_MainClassBody: // MainClassBody
      case symbol_kind::S_ClassDeclaration: // ClassDeclaration
      case symbol_kind::S_ClassDeclarationList: // ClassDeclarationList
      case symbol_kind::S_MethodDeclaration: // MethodDeclaration
      case symbol_kind::S_MethodDeclarationList: // MethodDeclarationList
      case symbol_kind::S_BlockContent: // BlockContent
      case symbol_kind::S_TypeIdentifier: // TypeIdentifier
      case symbol_kind::S_TypeIdentifierList: // TypeIdentifierList
      case symbol_kind::S_VarType: // VarType
      case symbol_kind::S_VarDeclaration: // VarDeclaration
      case symbol_kind::S_VarDeclarationList: // VarDeclarationList
      case symbol_kind::S_VariableAndStatement: // VariableAndStatement
      case symbol_kind::S_VariablesAndStatementList: // VariablesAndStatementList
      case symbol_kind::S_Statement: // Statement
      case symbol_kind::S_StatementList: // StatementList
      case symbol_kind::S_StatementsNonEmpty: // StatementsNonEmpty
      case symbol_kind::S_Expression: // Expression
      case symbol_kind::S_OrExpression: // OrExpression
      case symbol_kind::S_AndExpression: // AndExpression
      case symbol_kind::S_EqualExpression: // EqualExpression
      case symbol_kind::S_CompareExpression: // CompareExpression
      case symbol_kind::S_AddSubExpression: // AddSubExpression
      case symbol_kind::S_MulDivExpression: // MulDivExpression
      case symbol_kind::S_NotExpression: // NotExpression
      case symbol_kind::S_BaseExpression: // BaseExpression
      case symbol_kind::S_ExpressionList: // ExpressionList
      case symbol_kind::S_ExpressionsNonEmpty: // ExpressionsNonEmpty
      case symbol_kind::S_Identifier: // Identifier
      case symbol_kind::S_Return: // Return
      case symbol_kind::S_Int: // Int
        yylhs.value.emplace< Node * > ();
        break;

      case symbol_kind::S_ASSIGN: // ASSIGN
      case symbol_kind::S_AND: // AND
      case symbol_kind::S_OR: // OR
      case symbol_kind::S_EQ: // EQ
      case symbol_kind::S_LT: // LT
      case symbol_kind::S_GT: // GT
      case symbol_kind::S_ADD: // ADD
      case symbol_kind::S_SUB: // SUB
      case symbol_kind::S_MUL: // MUL
      case symbol_kind::S_DIV: // DIV
      case symbol_kind::S_NOT: // NOT
      case symbol_kind::S_LP: // LP
      case symbol_kind::S_RP: // RP
      case symbol_kind::S_LBRACKET: // LBRACKET
      case symbol_kind::S_RBRACKET: // RBRACKET
      case symbol_kind::S_SEMI: // SEMI
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_DOT: // DOT
      case symbol_kind::S_CLASS: // CLASS
      case symbol_kind::S_MAIN: // MAIN
      case symbol_kind::S_PUBLIC: // PUBLIC
      case symbol_kind::S_STATIC: // STATIC
      case symbol_kind::S_VOID: // VOID
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_WHILE: // WHILE
      case symbol_kind::S_PRINTLN: // PRINTLN
      case symbol_kind::S_RETURN: // RETURN
      case symbol_kind::S_INT: // INT
      case symbol_kind::S_BOOLEAN: // BOOLEAN
      case symbol_kind::S_TRUE: // TRUE
      case symbol_kind::S_FALSE: // FALSE
      case symbol_kind::S_THIS: // THIS
      case symbol_kind::S_NEW: // NEW
      case symbol_kind::S_LENGTH: // LENGTH
      case symbol_kind::S_INT_LITERAL: // INT_LITERAL
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRING: // STRING
      case symbol_kind::S_LHB: // LHB
      case symbol_kind::S_RHB: // RHB
        yylhs.value.emplace< std::string > ();
        break;

      default:
        break;
    }



      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // root: Goal
#line 62 "parser.yy"
           { root = yystack_[0].value.as < Node * > (); }
#line 908 "./output/parser.tab.cc"
    break;

  case 3: // Goal: MainClass ClassDeclarationList END
#line 65 "parser.yy"
                                               { yylhs.value.as < Node * > () = new Node("Global", "", yylineno); yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ()); yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ()); /* printf("r1 "); */ }
#line 914 "./output/parser.tab.cc"
    break;

  case 4: // MainClass: PUBLIC CLASS Identifier LBRACKET MainClassMethod RBRACKET
#line 70 "parser.yy"
                                                              {
        yylhs.value.as < Node * > () = new Node("MainClass", yystack_[3].value.as < Node * > ()->value, yylineno);
        yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ());
    }
#line 923 "./output/parser.tab.cc"
    break;

  case 5: // MainClassMethod: PUBLIC STATIC VOID MAIN LP STRING LHB RHB Identifier RP LBRACKET MainClassBody RBRACKET
#line 77 "parser.yy"
                                                                                            {
        yylhs.value.as < Node * > () = new Node("MethodDeclaration", "main", yylineno);
        Node* TypeIdentifierList = new Node("TypeIdentifierList", "", yylineno);
        Node* TypeIdentifier = new Node("TypeIdentifier", "", yystack_[4].value.as < Node * > ()->lineno);
        

        TypeIdentifier->children.push_back(new Node("StringList", "", yystack_[4].value.as < Node * > ()->lineno));
        TypeIdentifier->children.push_back(new Node("Identifier", yystack_[4].value.as < Node * > ()->value, yystack_[4].value.as < Node * > ()->lineno));
        

        TypeIdentifierList->children.push_back(TypeIdentifier);

        yylhs.value.as < Node * > ()->children.push_back(new Node("Void", "", yylineno));
        yylhs.value.as < Node * > ()->children.push_back(TypeIdentifierList);
        yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ());
    }
#line 944 "./output/parser.tab.cc"
    break;

  case 6: // MainClassBody: Statement
#line 96 "parser.yy"
                { 
          yylhs.value.as < Node * > () = new Node("BlockContent", "", yylineno); 
          yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); 
      }
#line 953 "./output/parser.tab.cc"
    break;

  case 7: // MainClassBody: MainClassBody Statement
#line 100 "parser.yy"
                              { 
          yylhs.value.as < Node * > () = yystack_[1].value.as < Node * > (); 
          yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); 
      }
#line 962 "./output/parser.tab.cc"
    break;

  case 8: // ClassDeclaration: CLASS Identifier LBRACKET RBRACKET
#line 107 "parser.yy"
                                       { 
        yylhs.value.as < Node * > () = new Node("ClassDeclaration", yystack_[2].value.as < Node * > ()->value, yylineno); 
    }
#line 970 "./output/parser.tab.cc"
    break;

  case 9: // ClassDeclaration: CLASS Identifier LBRACKET VarDeclarationList MethodDeclarationList RBRACKET
#line 110 "parser.yy"
                                                                                {
        yylhs.value.as < Node * > () = new Node("ClassDeclaration", yystack_[4].value.as < Node * > ()->value, yystack_[4].value.as < Node * > ()->lineno); 
        for(auto child : yystack_[2].value.as < Node * > ()->children) {
            yylhs.value.as < Node * > ()->children.push_back(child);
        }
        for(auto child : yystack_[1].value.as < Node * > ()->children) {
            yylhs.value.as < Node * > ()->children.push_back(child);
        }
    }
#line 984 "./output/parser.tab.cc"
    break;

  case 10: // ClassDeclarationList: %empty
#line 122 "parser.yy"
    { yylhs.value.as < Node * > () = new Node("ClassDeclarationList", "", yylineno); }
#line 990 "./output/parser.tab.cc"
    break;

  case 11: // ClassDeclarationList: ClassDeclaration
#line 123 "parser.yy"
                       { 
          yylhs.value.as < Node * > () = new Node("ClassDeclarationList", "", yylineno); 
          yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); 
      }
#line 999 "./output/parser.tab.cc"
    break;

  case 12: // ClassDeclarationList: ClassDeclarationList ClassDeclaration
#line 127 "parser.yy"
                                            { 
          yylhs.value.as < Node * > () = yystack_[1].value.as < Node * > (); 
          yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); 
      }
#line 1008 "./output/parser.tab.cc"
    break;

  case 13: // MethodDeclaration: PUBLIC VarType Identifier LP TypeIdentifierList RP BlockContent
#line 135 "parser.yy"
                                                                    { 
        yylhs.value.as < Node * > () = new Node("MethodDeclaration", yystack_[4].value.as < Node * > ()->value, yystack_[4].value.as < Node * > ()->lineno); 
        yylhs.value.as < Node * > ()->children.push_back(yystack_[5].value.as < Node * > ());
        yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
        yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
    }
#line 1019 "./output/parser.tab.cc"
    break;

  case 14: // MethodDeclarationList: %empty
#line 144 "parser.yy"
    { yylhs.value.as < Node * > () = new Node("MethodDeclarationList", "", yylineno); }
#line 1025 "./output/parser.tab.cc"
    break;

  case 15: // MethodDeclarationList: MethodDeclaration
#line 145 "parser.yy"
                        { 
          yylhs.value.as < Node * > () = new Node("MethodDeclarationList", "", yylineno); 
          yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); 
      }
#line 1034 "./output/parser.tab.cc"
    break;

  case 16: // MethodDeclarationList: MethodDeclarationList MethodDeclaration
#line 149 "parser.yy"
                                              { 
          yylhs.value.as < Node * > () = yystack_[1].value.as < Node * > (); 
          yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); 
      }
#line 1043 "./output/parser.tab.cc"
    break;

  case 17: // BlockContent: LBRACKET Return RBRACKET
#line 156 "parser.yy"
                             { 
        yylhs.value.as < Node * > () = new Node("BlockContent", "", yylineno); 
        yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ()); 
    }
#line 1052 "./output/parser.tab.cc"
    break;

  case 18: // BlockContent: LBRACKET VariablesAndStatementList Return RBRACKET
#line 160 "parser.yy"
                                                       { 
        yylhs.value.as < Node * > () = new Node("BlockContent", "", yylineno); 
        
        for(auto child : yystack_[2].value.as < Node * > ()->children) {
            yylhs.value.as < Node * > ()->children.push_back(child);
        }
        
        yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ()); 
    }
#line 1066 "./output/parser.tab.cc"
    break;

  case 19: // TypeIdentifier: VarType Identifier
#line 173 "parser.yy"
                       { 
        yylhs.value.as < Node * > () = new Node("TypeIdentifier", "", yylineno);
        yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ()); 
        yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); 
    }
#line 1076 "./output/parser.tab.cc"
    break;

  case 20: // TypeIdentifierList: %empty
#line 181 "parser.yy"
    { yylhs.value.as < Node * > () = new Node("TypeIdentifierList", "", yylineno); }
#line 1082 "./output/parser.tab.cc"
    break;

  case 21: // TypeIdentifierList: TypeIdentifier
#line 182 "parser.yy"
                     { 
          yylhs.value.as < Node * > () = new Node("TypeIdentifierList", "", yylineno); 
          yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); 
      }
#line 1091 "./output/parser.tab.cc"
    break;

  case 22: // TypeIdentifierList: TypeIdentifierList COMMA TypeIdentifier
#line 186 "parser.yy"
                                              { 
          yylhs.value.as < Node * > () = yystack_[2].value.as < Node * > (); 
          yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); 
      }
#line 1100 "./output/parser.tab.cc"
    break;

  case 23: // VarType: INT LHB RHB
#line 193 "parser.yy"
                { 
        yylhs.value.as < Node * > () = new Node("IntArray", "", yylineno); 
    }
#line 1108 "./output/parser.tab.cc"
    break;

  case 24: // VarType: BOOLEAN
#line 196 "parser.yy"
            { 
        yylhs.value.as < Node * > () = new Node("Boolean", "", yylineno); 
    }
#line 1116 "./output/parser.tab.cc"
    break;

  case 25: // VarType: INT
#line 199 "parser.yy"
        { 
        yylhs.value.as < Node * > () = new Node("Int", "", yylineno); 
    }
#line 1124 "./output/parser.tab.cc"
    break;

  case 26: // VarType: Identifier
#line 202 "parser.yy"
               { 
        yylhs.value.as < Node * > () = new Node("Identifier", yystack_[0].value.as < Node * > ()->value, yylineno); 
    }
#line 1132 "./output/parser.tab.cc"
    break;

  case 27: // VarDeclaration: VarType Identifier SEMI
#line 208 "parser.yy"
                            { 
        yylhs.value.as < Node * > () = new Node("VarDeclaration", "", yylineno); 
        yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ()); 
        yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ()); 
    }
#line 1142 "./output/parser.tab.cc"
    break;

  case 28: // VarDeclarationList: %empty
#line 216 "parser.yy"
    { yylhs.value.as < Node * > () = new Node("VarDeclarationList", "", yylineno); }
#line 1148 "./output/parser.tab.cc"
    break;

  case 29: // VarDeclarationList: VarDeclaration
#line 217 "parser.yy"
                     { 
          yylhs.value.as < Node * > () = new Node("VarDeclarationList", "", yylineno); 
          yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); 
      }
#line 1157 "./output/parser.tab.cc"
    break;

  case 30: // VarDeclarationList: VarDeclarationList VarDeclaration
#line 221 "parser.yy"
                                        { 
          yylhs.value.as < Node * > () = yystack_[1].value.as < Node * > (); 
          yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); 
      }
#line 1166 "./output/parser.tab.cc"
    break;

  case 31: // VariableAndStatement: VarDeclaration
#line 228 "parser.yy"
                   { yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > (); }
#line 1172 "./output/parser.tab.cc"
    break;

  case 32: // VariableAndStatement: Statement
#line 229 "parser.yy"
              { yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > (); }
#line 1178 "./output/parser.tab.cc"
    break;

  case 33: // VariablesAndStatementList: VariableAndStatement
#line 233 "parser.yy"
                         { 
        yylhs.value.as < Node * > () = new Node("VariablesAndStatementList", "", yylineno); 
        yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); 
    }
#line 1187 "./output/parser.tab.cc"
    break;

  case 34: // VariablesAndStatementList: VariablesAndStatementList VariableAndStatement
#line 237 "parser.yy"
                                                   { 
        yylhs.value.as < Node * > () = yystack_[1].value.as < Node * > (); 
        yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); 
    }
#line 1196 "./output/parser.tab.cc"
    break;

  case 35: // Statement: LBRACKET RBRACKET
#line 244 "parser.yy"
                        { 
          yylhs.value.as < Node * > () = new Node("BlockContent", "", yylineno); 
      }
#line 1204 "./output/parser.tab.cc"
    break;

  case 36: // Statement: LBRACKET StatementList RBRACKET
#line 247 "parser.yy"
                                      { 
          yylhs.value.as < Node * > () = new Node("BlockContent", "", yylineno); 
          yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ()); 
      }
#line 1213 "./output/parser.tab.cc"
    break;

  case 37: // Statement: IF LP Expression RP Statement
#line 251 "parser.yy"
                                    { 
          yylhs.value.as < Node * > () = new Node("IfStatement", "", yylineno); 
          yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ()); 
          yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); 
      }
#line 1223 "./output/parser.tab.cc"
    break;

  case 38: // Statement: IF LP Expression RP Statement ELSE Statement
#line 256 "parser.yy"
                                                   { 
          yylhs.value.as < Node * > () = new Node("IfElseStatement", "", yylineno); 
          yylhs.value.as < Node * > ()->children.push_back(yystack_[4].value.as < Node * > ()); 
          yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ()); 
          yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); 
      }
#line 1234 "./output/parser.tab.cc"
    break;

  case 39: // Statement: WHILE LP Expression RP Statement
#line 262 "parser.yy"
                                       { 
          yylhs.value.as < Node * > () = new Node("WhileStatement", "", yylineno); 
          yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ()); 
          yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); 
      }
#line 1244 "./output/parser.tab.cc"
    break;

  case 40: // Statement: PRINTLN LP Expression RP SEMI
#line 267 "parser.yy"
                                    { 
          yylhs.value.as < Node * > () = new Node("PrintlnStatement", "", yylineno); 
          yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ()); 
      }
#line 1253 "./output/parser.tab.cc"
    break;

  case 41: // Statement: Identifier ASSIGN Expression SEMI
#line 271 "parser.yy"
                                        { 
          yylhs.value.as < Node * > () = new Node("AssignStatement", "", yylineno); 
          yylhs.value.as < Node * > ()->children.push_back(yystack_[3].value.as < Node * > ()); 
          yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ()); 
      }
#line 1263 "./output/parser.tab.cc"
    break;

  case 42: // Statement: Identifier LHB Expression RHB ASSIGN Expression SEMI
#line 276 "parser.yy"
                                                           { 
          yylhs.value.as < Node * > () = new Node("ArrayAssignStatement", "", yylineno); 
          yylhs.value.as < Node * > ()->children.push_back(yystack_[6].value.as < Node * > ()); 
          yylhs.value.as < Node * > ()->children.push_back(yystack_[4].value.as < Node * > ()); 
          yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ()); 
      }
#line 1274 "./output/parser.tab.cc"
    break;

  case 43: // StatementList: %empty
#line 286 "parser.yy"
    { yylhs.value.as < Node * > () = new Node("StatementList", "", yylineno); }
#line 1280 "./output/parser.tab.cc"
    break;

  case 44: // StatementList: StatementsNonEmpty
#line 287 "parser.yy"
                         { yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > (); }
#line 1286 "./output/parser.tab.cc"
    break;

  case 45: // StatementsNonEmpty: Statement
#line 291 "parser.yy"
                { 
          yylhs.value.as < Node * > () = new Node("StatementList", "", yylineno); 
          yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); 
      }
#line 1295 "./output/parser.tab.cc"
    break;

  case 46: // StatementsNonEmpty: StatementsNonEmpty Statement
#line 295 "parser.yy"
                                   { 
          yylhs.value.as < Node * > () = yystack_[1].value.as < Node * > (); 
          yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); 
      }
#line 1304 "./output/parser.tab.cc"
    break;

  case 47: // Expression: OrExpression
#line 302 "parser.yy"
                 { yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > (); }
#line 1310 "./output/parser.tab.cc"
    break;

  case 48: // OrExpression: OrExpression OR AndExpression
#line 306 "parser.yy"
                                  { 
        yylhs.value.as < Node * > () = new Node("OrExpression", "", yylineno); 
        yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ()); 
        yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); 
    }
#line 1320 "./output/parser.tab.cc"
    break;

  case 49: // OrExpression: AndExpression
#line 311 "parser.yy"
                  { yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > (); }
#line 1326 "./output/parser.tab.cc"
    break;

  case 50: // AndExpression: AndExpression AND EqualExpression
#line 315 "parser.yy"
                                      { 
        yylhs.value.as < Node * > () = new Node("AndExpression", "", yylineno); 
        yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ()); 
        yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); 
    }
#line 1336 "./output/parser.tab.cc"
    break;

  case 51: // AndExpression: EqualExpression
#line 320 "parser.yy"
                    { yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > (); }
#line 1342 "./output/parser.tab.cc"
    break;

  case 52: // EqualExpression: EqualExpression EQ CompareExpression
#line 324 "parser.yy"
                                         { 
        yylhs.value.as < Node * > () = new Node("EqualExpression", "", yylineno); 
        yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ()); 
        yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); 
    }
#line 1352 "./output/parser.tab.cc"
    break;

  case 53: // EqualExpression: CompareExpression
#line 329 "parser.yy"
                      { yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > (); }
#line 1358 "./output/parser.tab.cc"
    break;

  case 54: // CompareExpression: CompareExpression LT AddSubExpression
#line 333 "parser.yy"
                                          { 
        yylhs.value.as < Node * > () = new Node("LessThanExpression", "", yylineno); 
        yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ()); 
        yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); 
    }
#line 1368 "./output/parser.tab.cc"
    break;

  case 55: // CompareExpression: CompareExpression GT AddSubExpression
#line 338 "parser.yy"
                                          { 
        yylhs.value.as < Node * > () = new Node("GreaterThanExpression", "", yylineno); 
        yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ()); 
        yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); 
    }
#line 1378 "./output/parser.tab.cc"
    break;

  case 56: // CompareExpression: AddSubExpression
#line 343 "parser.yy"
                     { yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > (); }
#line 1384 "./output/parser.tab.cc"
    break;

  case 57: // AddSubExpression: AddSubExpression ADD MulDivExpression
#line 347 "parser.yy"
                                          { 
        yylhs.value.as < Node * > () = new Node("AddExpression", "", yylineno); 
        yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ()); 
        yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); 
    }
#line 1394 "./output/parser.tab.cc"
    break;

  case 58: // AddSubExpression: AddSubExpression SUB MulDivExpression
#line 352 "parser.yy"
                                          { 
        yylhs.value.as < Node * > () = new Node("SubExpression", "", yylineno); 
        yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ()); 
        yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); 
    }
#line 1404 "./output/parser.tab.cc"
    break;

  case 59: // AddSubExpression: MulDivExpression
#line 357 "parser.yy"
                     { yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > (); }
#line 1410 "./output/parser.tab.cc"
    break;

  case 60: // MulDivExpression: MulDivExpression MUL NotExpression
#line 361 "parser.yy"
                                       { 
        yylhs.value.as < Node * > () = new Node("MulExpression", "", yylineno); 
        yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ()); 
        yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); 
    }
#line 1420 "./output/parser.tab.cc"
    break;

  case 61: // MulDivExpression: MulDivExpression DIV NotExpression
#line 366 "parser.yy"
                                       { 
        yylhs.value.as < Node * > () = new Node("DivExpression", "", yylineno); 
        yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ()); 
        yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); 
    }
#line 1430 "./output/parser.tab.cc"
    break;

  case 62: // MulDivExpression: NotExpression
#line 371 "parser.yy"
                  { yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > (); }
#line 1436 "./output/parser.tab.cc"
    break;

  case 63: // NotExpression: NOT BaseExpression
#line 375 "parser.yy"
                       { 
        yylhs.value.as < Node * > () = new Node("NotExpression", "", yylineno); 
        yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); 
    }
#line 1445 "./output/parser.tab.cc"
    break;

  case 64: // NotExpression: BaseExpression
#line 379 "parser.yy"
                   { yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > (); }
#line 1451 "./output/parser.tab.cc"
    break;

  case 65: // BaseExpression: NEW Identifier LP RP
#line 383 "parser.yy"
                         { yylhs.value.as < Node * > () = new Node("NewObjectExpression", yystack_[2].value.as < Node * > ()->value, yylineno); }
#line 1457 "./output/parser.tab.cc"
    break;

  case 66: // BaseExpression: BaseExpression LHB Expression RHB
#line 384 "parser.yy"
                                      { 
        yylhs.value.as < Node * > () = new Node("ArrayAccess", "", yylineno); 
        yylhs.value.as < Node * > ()->children.push_back(yystack_[3].value.as < Node * > ()); 
        yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ()); 
    }
#line 1467 "./output/parser.tab.cc"
    break;

  case 67: // BaseExpression: BaseExpression DOT LENGTH
#line 389 "parser.yy"
                              { 
        yylhs.value.as < Node * > () = new Node("ArrayLength", "", yylineno); 
        yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ()); 
    }
#line 1476 "./output/parser.tab.cc"
    break;

  case 68: // BaseExpression: BaseExpression DOT Identifier LP ExpressionList RP
#line 393 "parser.yy"
                                                       { 
        yylhs.value.as < Node * > () = new Node("MethodCallExpression", "", yylineno); 
        yylhs.value.as < Node * > ()->children.push_back(yystack_[5].value.as < Node * > ()); 
        yylhs.value.as < Node * > ()->children.push_back(yystack_[3].value.as < Node * > ()); 
        if(yystack_[1].value.as < Node * > () != nullptr) yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ()); 
    }
#line 1487 "./output/parser.tab.cc"
    break;

  case 69: // BaseExpression: TRUE
#line 399 "parser.yy"
         { 
        yylhs.value.as < Node * > () = new Node("TrueExpression", "", yylineno); 
    }
#line 1495 "./output/parser.tab.cc"
    break;

  case 70: // BaseExpression: FALSE
#line 402 "parser.yy"
          { 
        yylhs.value.as < Node * > () = new Node("FalseExpression", "", yylineno); 
    }
#line 1503 "./output/parser.tab.cc"
    break;

  case 71: // BaseExpression: THIS
#line 405 "parser.yy"
         { 
        yylhs.value.as < Node * > () = new Node("ThisExpression", "", yylineno); 
    }
#line 1511 "./output/parser.tab.cc"
    break;

  case 72: // BaseExpression: NEW INT LHB Expression RHB
#line 408 "parser.yy"
                               { 
        yylhs.value.as < Node * > () = new Node("NewArray", "", yylineno); 
        yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ()); 
    }
#line 1520 "./output/parser.tab.cc"
    break;

  case 73: // BaseExpression: LP Expression RP
#line 412 "parser.yy"
                     { 
        yylhs.value.as < Node * > () = new Node("Expression", "", yylineno); 
        yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ()); 
    }
#line 1529 "./output/parser.tab.cc"
    break;

  case 74: // BaseExpression: Int
#line 416 "parser.yy"
        { yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > (); }
#line 1535 "./output/parser.tab.cc"
    break;

  case 75: // BaseExpression: Identifier
#line 417 "parser.yy"
               { yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > (); }
#line 1541 "./output/parser.tab.cc"
    break;

  case 76: // ExpressionList: %empty
#line 421 "parser.yy"
    { yylhs.value.as < Node * > () = new Node("ExpressionList", "", yylineno); }
#line 1547 "./output/parser.tab.cc"
    break;

  case 77: // ExpressionList: ExpressionsNonEmpty
#line 422 "parser.yy"
                          { yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > (); }
#line 1553 "./output/parser.tab.cc"
    break;

  case 78: // ExpressionsNonEmpty: Expression
#line 426 "parser.yy"
                 { 
          yylhs.value.as < Node * > () = new Node("ExpressionList", "", yylineno); 
          yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); 
      }
#line 1562 "./output/parser.tab.cc"
    break;

  case 79: // ExpressionsNonEmpty: ExpressionsNonEmpty COMMA Expression
#line 430 "parser.yy"
                                           { 
          yylhs.value.as < Node * > () = yystack_[2].value.as < Node * > (); 
          yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); 
      }
#line 1571 "./output/parser.tab.cc"
    break;

  case 80: // Identifier: IDENTIFIER
#line 438 "parser.yy"
               { 
        yylhs.value.as < Node * > () = new Node("Identifier", yystack_[0].value.as < std::string > (), yylineno); 
    }
#line 1579 "./output/parser.tab.cc"
    break;

  case 81: // Return: RETURN Expression SEMI
#line 444 "parser.yy"
                           { 
        yylhs.value.as < Node * > () = new Node("Return", "", yylineno); 
        yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ()); 
    }
#line 1588 "./output/parser.tab.cc"
    break;

  case 82: // Int: INT_LITERAL
#line 451 "parser.yy"
                { 
        yylhs.value.as < Node * > () = new Node("Int", yystack_[0].value.as < std::string > (), yylineno); 
    }
#line 1596 "./output/parser.tab.cc"
    break;

  case 83: // Int: SUB INT_LITERAL
#line 454 "parser.yy"
                    { 
        yylhs.value.as < Node * > () = new Node("SubInt", "-" + yystack_[0].value.as < std::string > (), yylineno); 
    }
#line 1604 "./output/parser.tab.cc"
    break;


#line 1608 "./output/parser.tab.cc"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (YY_MOVE (msg));
      }


    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;


      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

  std::string
  parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // parser::context.
  parser::context::context (const parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

    const int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        const int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        const int yychecklim = yylast_ - yyn + 1;
        const int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
        for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
          if (yycheck_[yyx + yyn] == yyx && yyx != symbol_kind::S_YYerror
              && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
            {
              if (!yyarg)
                ++yycount;
              else if (yycount == yyargn)
                return 0;
              else
                yyarg[yycount++] = YY_CAST (symbol_kind_type, yyx);
            }
      }

    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }






  int
  parser::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char parser::yypact_ninf_ = -71;

  const signed char parser::yytable_ninf_ = -1;

  const short
  parser::yypact_[] =
  {
     -11,    -3,    24,   -71,     6,     4,   -71,     4,   -71,    20,
     -71,    42,    45,   -71,   -71,    61,    23,    69,    73,   -71,
      60,   -71,     4,   -71,    34,   -71,    89,   -71,    81,   111,
      67,   -71,    -9,   -71,   112,   -71,   -71,     4,   -71,   -71,
     123,   124,    99,    67,   101,   -71,    70,     4,   103,   127,
      67,   -71,     4,     5,   -71,   -71,   125,    66,   130,   132,
     133,    36,   -71,   -71,     5,   -71,    -2,   131,   134,   -71,
     -71,   135,   -13,    -2,    36,    36,    36,   113,    77,    36,
     -71,   -71,   -71,    25,   -71,   137,   144,   149,   150,    96,
      98,   109,   -71,    40,   -71,   -71,   -71,   140,    36,    36,
     -71,   -13,   -71,   -71,   143,   145,   146,   -71,    40,   147,
     118,   151,   -71,    36,    36,    36,    36,    36,    36,    36,
      36,    36,    63,    36,   -71,   148,   121,   102,   -71,   -13,
     -13,   152,   -71,    36,   153,   149,   150,    96,    98,    98,
     109,   109,   -71,   -71,   -71,   155,   122,   -71,   164,   -71,
     -71,   154,   -71,   -71,   129,   -71,    36,   -71,    36,   -13,
     -71,   -71,   157,   156,   158,   -71,   -71,    36,   -71,   -71
  };

  const signed char
  parser::yydefact_[] =
  {
       0,     0,     0,     2,    10,     0,     1,     0,    11,     0,
      80,     0,     0,     3,    12,     0,    28,     0,     0,     8,
      25,    24,     0,    29,    14,    26,     0,     4,     0,     0,
       0,    15,     0,    30,     0,    23,    27,     0,     9,    16,
       0,     0,     0,    20,     0,    21,     0,     0,     0,     0,
       0,    19,     0,     0,    13,    22,     0,     0,     0,     0,
       0,     0,    31,    33,     0,    32,    26,     0,     0,    35,
      45,     0,    44,     0,     0,     0,     0,     0,     0,     0,
      69,    70,    71,     0,    82,     0,    47,    49,    51,    53,
      56,    59,    62,    64,    75,    74,    34,     0,     0,     0,
      17,     0,    36,    46,     0,     0,     0,    83,    63,     0,
       0,     0,    81,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    18,     0,     0,     0,     6,     0,
       0,     0,    73,     0,     0,    48,    50,    52,    54,    55,
      57,    58,    60,    61,    67,     0,     0,    41,     0,     5,
       7,    37,    39,    40,     0,    65,    76,    66,     0,     0,
      72,    78,     0,    77,     0,    38,    68,     0,    42,    79
  };

  const short
  parser::yypgoto_[] =
  {
     -71,   -71,   -71,   -71,   -71,   -71,   165,   -71,   141,   -71,
     -71,   128,   -71,   -20,    52,   -71,   115,   -71,   -50,   -71,
     -71,   -70,   -71,    64,    68,    65,    10,    14,    15,   105,
     -71,   -71,    -5,   120,   -71
  };

  const unsigned char
  parser::yydefgoto_[] =
  {
       0,     2,     3,     4,    18,   127,     8,     9,    31,    32,
      54,    45,    46,    22,    62,    24,    63,    64,    65,    71,
      72,    85,    86,    87,    88,    89,    90,    91,    92,    93,
     162,   163,    94,    67,    95
  };

  const unsigned char
  parser::yytable_[] =
  {
      11,    98,    12,    57,   104,   105,   106,    70,    38,   109,
      37,    25,     1,    58,    30,    59,    60,    29,     5,    25,
      13,    57,   103,    47,     6,    25,    10,     7,   125,   126,
      47,    58,    41,    59,    60,    61,    20,    21,    25,    99,
      19,     7,    51,    10,    10,    25,    77,    56,    66,    78,
      79,   128,    73,   146,    20,    21,   110,    30,    15,    66,
     122,    16,    10,   154,    10,    20,    21,    73,    23,    80,
      81,    82,    83,    10,    84,    10,    33,   150,   111,   151,
     152,   123,    57,    69,    17,    49,   161,    77,   164,    50,
      27,    79,    58,    26,    59,    60,    73,   169,    20,    21,
     144,    28,    10,   116,   117,    10,    10,   118,   119,   165,
      80,    81,    82,    83,    34,    84,    10,   145,    57,   149,
     120,   121,    73,    35,    73,    73,   138,   139,    58,    36,
      59,    60,   140,   141,    40,   142,   143,    42,    43,    44,
      68,    10,    48,    53,    74,    52,    75,    76,   100,   113,
     101,   107,   102,   114,    73,   112,   115,   124,   129,   133,
     130,   131,   132,   148,   157,   134,   147,   158,   155,   156,
     153,   160,   166,    39,    14,   167,   168,   135,    55,    96,
     137,   159,   136,   108,    97
  };

  const unsigned char
  parser::yycheck_[] =
  {
       5,     3,     7,    16,    74,    75,    76,    57,    17,    79,
      30,    16,    23,    26,    23,    28,    29,    22,    21,    24,
       0,    16,    72,    43,     0,    30,    39,    21,    98,    99,
      50,    26,    37,    28,    29,    30,    31,    32,    43,    41,
      17,    21,    47,    39,    39,    50,    10,    52,    53,    13,
      14,   101,    57,   123,    31,    32,    31,    23,    16,    64,
      20,    16,    39,   133,    39,    31,    32,    72,    16,    33,
      34,    35,    36,    39,    38,    39,    24,   127,    83,   129,
     130,    41,    16,    17,    23,    15,   156,    10,   158,    19,
      17,    14,    26,    24,    28,    29,   101,   167,    31,    32,
      37,    41,    39,     7,     8,    39,    39,     9,    10,   159,
      33,    34,    35,    36,    25,    38,    39,   122,    16,    17,
      11,    12,   127,    42,   129,   130,   116,   117,    26,    18,
      28,    29,   118,   119,    22,   120,   121,    14,    14,    40,
      15,    39,    41,    16,    14,    42,    14,    14,    17,     5,
      16,    38,    17,     4,   159,    18,     6,    17,    15,    41,
      15,    15,    15,    42,    42,    14,    18,     3,    15,    14,
      18,    42,    15,    32,     9,    19,    18,   113,    50,    64,
     115,    27,   114,    78,    64
  };

  const signed char
  parser::yystos_[] =
  {
       0,    23,    44,    45,    46,    21,     0,    21,    49,    50,
      39,    75,    75,     0,    49,    16,    16,    23,    47,    17,
      31,    32,    56,    57,    58,    75,    24,    17,    41,    75,
      23,    51,    52,    57,    25,    42,    18,    56,    17,    51,
      22,    75,    14,    14,    40,    54,    55,    56,    41,    15,
      19,    75,    42,    16,    53,    54,    75,    16,    26,    28,
      29,    30,    57,    59,    60,    61,    75,    76,    15,    17,
      61,    62,    63,    75,    14,    14,    14,    10,    13,    14,
      33,    34,    35,    36,    38,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    75,    77,    59,    76,     3,    41,
      17,    16,    17,    61,    64,    64,    64,    38,    72,    64,
      31,    75,    18,     5,     4,     6,     7,     8,     9,    10,
      11,    12,    20,    41,    17,    64,    64,    48,    61,    15,
      15,    15,    15,    41,    14,    66,    67,    68,    69,    69,
      70,    70,    71,    71,    37,    75,    64,    18,    42,    17,
      61,    61,    61,    18,    64,    15,    14,    42,     3,    27,
      42,    64,    73,    74,    64,    61,    15,    19,    18,    64
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    43,    44,    45,    46,    47,    48,    48,    49,    49,
      50,    50,    50,    51,    52,    52,    52,    53,    53,    54,
      55,    55,    55,    56,    56,    56,    56,    57,    58,    58,
      58,    59,    59,    60,    60,    61,    61,    61,    61,    61,
      61,    61,    61,    62,    62,    63,    63,    64,    65,    65,
      66,    66,    67,    67,    68,    68,    68,    69,    69,    69,
      70,    70,    70,    71,    71,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    73,    73,    74,    74,
      75,    76,    77,    77
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     3,     6,    13,     1,     2,     4,     6,
       0,     1,     2,     7,     0,     1,     2,     3,     4,     2,
       0,     1,     3,     3,     1,     1,     1,     3,     0,     1,
       2,     1,     1,     1,     2,     2,     3,     5,     7,     5,
       5,     4,     7,     0,     1,     1,     2,     1,     3,     1,
       3,     1,     3,     1,     3,     3,     1,     3,     3,     1,
       3,     3,     1,     2,     1,     4,     4,     3,     6,     1,
       1,     1,     5,     3,     1,     1,     0,     1,     1,     3,
       1,     3,     1,     2
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "END", "error", "\"invalid token\"", "ASSIGN", "AND", "OR", "EQ", "LT",
  "GT", "ADD", "SUB", "MUL", "DIV", "NOT", "LP", "RP", "LBRACKET",
  "RBRACKET", "SEMI", "COMMA", "DOT", "CLASS", "MAIN", "PUBLIC", "STATIC",
  "VOID", "IF", "ELSE", "WHILE", "PRINTLN", "RETURN", "INT", "BOOLEAN",
  "TRUE", "FALSE", "THIS", "NEW", "LENGTH", "INT_LITERAL", "IDENTIFIER",
  "STRING", "LHB", "RHB", "$accept", "root", "Goal", "MainClass",
  "MainClassMethod", "MainClassBody", "ClassDeclaration",
  "ClassDeclarationList", "MethodDeclaration", "MethodDeclarationList",
  "BlockContent", "TypeIdentifier", "TypeIdentifierList", "VarType",
  "VarDeclaration", "VarDeclarationList", "VariableAndStatement",
  "VariablesAndStatementList", "Statement", "StatementList",
  "StatementsNonEmpty", "Expression", "OrExpression", "AndExpression",
  "EqualExpression", "CompareExpression", "AddSubExpression",
  "MulDivExpression", "NotExpression", "BaseExpression", "ExpressionList",
  "ExpressionsNonEmpty", "Identifier", "Return", "Int", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,    62,    62,    65,    70,    77,    96,   100,   107,   110,
     122,   123,   127,   135,   144,   145,   149,   156,   160,   173,
     181,   182,   186,   193,   196,   199,   202,   208,   216,   217,
     221,   228,   229,   233,   237,   244,   247,   251,   256,   262,
     267,   271,   276,   286,   287,   291,   295,   302,   306,   311,
     315,   320,   324,   329,   333,   338,   343,   347,   352,   357,
     361,   366,   371,   375,   379,   383,   384,   389,   393,   399,
     402,   405,   408,   412,   416,   417,   421,   422,   426,   430,
     438,   444,   451,   454
  };

  void
  parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


} // yy
#line 2190 "./output/parser.tab.cc"

#line 459 "parser.yy"
