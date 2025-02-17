#include <iostream>
#include <vector>
#include <unordered_map>
#include <functional>
#include "instruction.h"

// Function to map operators to instructions
std::string get_operator_instruction(const std::string& op) {
    static const std::unordered_map<std::string, std::string> operator_map = {
        {"+", "iadd"},
        {"-", "isub"},
        {"*", "imul"},
        {"/", "idiv"},
        {"<", "ilt"},
        {">", "igt"},
        {"and", "iand"},
        {"||", "ior"},
        {"==", "ieq"},
        {"!", "inot"}
    };

    auto it = operator_map.find(op);
    if (it != operator_map.end()) {
        return it->second;
    } else {
        throw std::invalid_argument("Unknown operator: " + op);
    }
}

// Define static member variables
std::unordered_map<std::string, std::vector<std::string>(Instruction::*)()> Instruction::dispatch_table;
bool Instruction::dispatch_table_initialized = false;

Instruction::Instruction(TAC* tac) : tac(tac), type(tac->get_type()) {
    // Initialize the dispatch table
    initialize_dispatch_table();

    // Generate bytecode using the appropriate handler
    auto handler = dispatch_table.find(type);
    if (handler != dispatch_table.end()) {
        bytecode = (this->*(handler->second))();
    } else {
        std::cerr << "Missing instructions for TAC type: " << type << std::endl;
    }
}

std::string Instruction::get_type() const {
    return type;
}

// Helper function to parse operands
std::string Instruction::parse_operand(const std::string& operand) const {
    if (operand == "True") {
        return "iconst 1";
    } else if (operand == "False") {
        return "iconst 0";
    } else if (!operand.empty() && operand[0] == '-') {
        return "iconst " + operand;
    } else {
        try {
            std::stoi(operand);
            return "iconst " + operand;
        } catch (...) {
            return "iload " + operand;
        }
    }
}

// Initialize the dispatch table
void Instruction::initialize_dispatch_table() {
    if (!dispatch_table_initialized) {
        dispatch_table = {
            {"Expression", &Instruction::handle_expression},
            {"UnaryExpression", &Instruction::handle_unary_expression},
            {"Parameter", &Instruction::handle_parameter},
            {"Argument", &Instruction::handle_argument},
            {"Print", &Instruction::handle_print},
            {"Length", &Instruction::handle_length},
            {"Return", &Instruction::handle_return},
            {"Copy", &Instruction::handle_copy},
            {"MethodCall", &Instruction::handle_method_call},
            {"Condition", &Instruction::handle_condition},
            {"CopyArray", &Instruction::handle_copy_array}
        };
        dispatch_table_initialized = true;
    }
}

// Handler for "Expression" TAC type
std::vector<std::string> Instruction::handle_expression() {
    std::vector<std::string> bytecode(4);
    bytecode[0] = parse_operand(tac->get_lhs());
    bytecode[1] = parse_operand(tac->get_rhs());
    bytecode[2] = get_operator_instruction(tac->get_op());
    bytecode[3] = "istore " + tac->get_target();
    return bytecode;
}

// Handler for "UnaryExpression" TAC type
std::vector<std::string> Instruction::handle_unary_expression() {
    std::vector<std::string> bytecode(3);
    bytecode[0] = parse_operand(tac->get_rhs());
    bytecode[1] = get_operator_instruction(tac->get_op());
    bytecode[2] = "istore " + tac->get_target();
    return bytecode;
}

// Handler for "CopyArray" TAC type
std::vector<std::string> Instruction::handle_copy_array() {
    std::vector<std::string> bytecode(3);
    bytecode[0] = parse_operand(tac->get_lhs());  // Index
    bytecode[1] = parse_operand(tac->get_rhs());  // Value
    bytecode[2] = "iastore " + tac->get_target(); // Array name
    return bytecode;
}

// Handlers for other TAC types
std::vector<std::string> Instruction::handle_parameter() {return { "istore " + tac->get_target()}; }
std::vector<std::string> Instruction::handle_argument() { return { parse_operand(tac->get_target()) }; }
std::vector<std::string> Instruction::handle_print() { return { parse_operand(tac->get_target()), "print" }; }
std::vector<std::string> Instruction::handle_length() { return { "iconst 0", "istore " + tac->get_target() }; }
std::vector<std::string> Instruction::handle_return() { return { parse_operand(tac->get_target()), "ireturn" }; }
std::vector<std::string> Instruction::handle_copy() { return { parse_operand(tac->get_lhs()), "istore " + tac->get_target() }; }
std::vector<std::string> Instruction::handle_method_call() { return { "invokevirtual " + tac->get_lhs(), "istore " + tac->get_target() }; }
std::vector<std::string> Instruction::handle_condition() { return { parse_operand(tac->get_target()) }; }

std::vector<std::string> Instruction::get_bytecode() const { return bytecode;}
