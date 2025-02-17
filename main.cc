#include <iostream>
#include "parser.tab.hh"
#include "symbol_table.h"
#include "semantic.h"
#include "tac.h"
#include "cfg.h"
#include "code_generator.h"
//BasicBlock* currentBlock;  // Define the external variable
//std::vector<BasicBlock*> methods;  // Define the external variable

extern Node* root;
extern FILE* yyin;
extern int yylineno;
extern int lexical_errors;
extern yy::parser::symbol_type yylex();

enum errCodes {
    SUCCESS = 0,
    LEXICAL_ERROR = 1,
    SYNTAX_ERROR = 2,
    AST_ERROR = 3,
    SEMANTIC_ERROR = 4,
    SEGMENTATION_FAULT = 139
};


int errCode = errCodes::SUCCESS;

// Handling Syntax Errors
void yy::parser::error(std::string const& err) {
    if (!lexical_errors) {
        std::cerr << "Syntax errors found! See the logs below:" << std::endl;
        std::cerr << "\t@error at line " << yylineno << ". Cannot generate a syntax for this input:" << err.c_str() << std::endl;
        std::cerr << "End of syntax errors!" << std::endl;
        errCode = errCodes::SYNTAX_ERROR;
    }
}

int main(int argc, char** argv) {
    // Reads from file if a file name is passed as an argument. Otherwise, reads from stdin.
    if (argc > 1) {
        if (!(yyin = fopen(argv[1], "r"))) {
            perror(argv[1]);
            return 1;
        }
    }

    yy::parser parser;

    if (!parser.parse()) {
        printf("================================================================\n");
        printf("======================== Parser Started ========================\n");
        printf("================================================================\n");
        root->generate_tree();
        printf("================================================================\n");
        printf("========================= Symbol Table =========================\n");
        printf("================================================================\n");
        SymbolTable* symbol_table = new SymbolTable();
        treeTraversal(root, symbol_table);
        symbol_table->generate_tree();
        printf("================================================================\n");
        printf("================== Semantic Analysis started ===================\n");
        printf("================================================================\n");
        semanticTraversal(root, symbol_table);
        printf("================================================================\n");
        printf("================== Control Flow Graph started ===================\n");
        printf("================================================================\n");
        // Generate TAC and CFG
        CFG cfg = CFG();
        cfg.CFGTraversal(root);
        cfg.graph();
        CodeGenerator code_generator = CodeGenerator();
        code_generator.generate(&cfg);
        printf("================================================================\n");
        printf("========================= End of Program =======================\n");
        printf("================================================================\n");

       
    }

    return errCode;
}
