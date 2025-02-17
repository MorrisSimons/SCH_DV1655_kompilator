#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <vector>
#include <string>
#include <unordered_map>
#include "tac.h"

class Instruction {
    private:
        TAC* tac;
        std::string type;
        std::vector<std::string> bytecode;

        // Static dispatch table for TAC type handlers
        static std::unordered_map<std::string, std::vector<std::string>(Instruction::*)()> dispatch_table;
        static bool dispatch_table_initialized;

        // Initialization of the dispatch table
        void initialize_dispatch_table();

        // Helper functions
        std::string parse_operand(const std::string& operand) const;

        // Handler functions for each TAC type
        std::vector<std::string> handle_expression();
        std::vector<std::string> handle_unary_expression();
        std::vector<std::string> handle_parameter();
        std::vector<std::string> handle_argument();
        std::vector<std::string> handle_print();
        std::vector<std::string> handle_length();
        std::vector<std::string> handle_return();
        std::vector<std::string> handle_copy();
        std::vector<std::string> handle_method_call();
        std::vector<std::string> handle_condition();
        std::vector<std::string> handle_copy_array();

    public:
        Instruction(TAC* tac);
        std::vector<std::string> get_bytecode() const;
        std::string get_type() const;
};

#endif
