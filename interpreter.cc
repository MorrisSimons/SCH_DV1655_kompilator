#include <string>
#include <stack>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <sstream>

// Enumeration for different instruction types
enum class Instruction {
    ILOAD,          // Load integer from variable
    ICONST,         // Load constant integer
    ISTORE,         // Store integer to variable
    IADD,           // Integer addition
    ISUB,           // Integer subtraction
    IMUL,           // Integer multiplication
    IDIV,           // Integer division
    ILT,            // Integer less than comparison
    IGT,            // Integer greater than comparison
    IEQ,            // Integer equality comparison
    IAND,           // Integer logical AND
    IOR,            // Integer logical OR
    INOT,           // Integer logical NOT
    GOTO,           // Unconditional jump
    IFFALSE,        // Jump if false
    INVOKEVIRTUAL,  // Invoke method
    IRETURN,        // Return from method
    PRINT,          // Print value
    STOP,           // Stop execution
    UNKNOWN         // Unrecognized instruction
};

// Helper function to map instruction strings to Instruction enums
Instruction getInstructionEnum(const std::string& instr) {
    if (instr == "iload") return Instruction::ILOAD;
    if (instr == "iconst") return Instruction::ICONST;
    if (instr == "istore") return Instruction::ISTORE;
    if (instr == "iadd") return Instruction::IADD;
    if (instr == "isub") return Instruction::ISUB;
    if (instr == "imul") return Instruction::IMUL;
    if (instr == "idiv") return Instruction::IDIV;
    if (instr == "ilt") return Instruction::ILT;
    if (instr == "igt") return Instruction::IGT;
    if (instr == "ieq") return Instruction::IEQ;
    if (instr == "iand") return Instruction::IAND;
    if (instr == "ior") return Instruction::IOR;
    if (instr == "inot") return Instruction::INOT;
    if (instr == "goto") return Instruction::GOTO;
    if (instr == "iffalse") return Instruction::IFFALSE;
    if (instr == "invokevirtual") return Instruction::INVOKEVIRTUAL;
    if (instr == "ireturn") return Instruction::IRETURN;
    if (instr == "print") return Instruction::PRINT;
    if (instr == "stop") return Instruction::STOP;
    else {
        std::cout << "This is the Unknown instruction: " << instr << std::endl;
        return Instruction::UNKNOWN;
    }
}

// Exception class to signal a stop instruction
class StopException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Stop instruction reached";
    }
};

// Interpreter class to execute bytecode instructions
class Interpreter {
private:
    std::stack<std::string> operand_stack;                 // Stack for operands
    std::stack<int> arg_stack;                             // Stack for method arguments
    std::stack<std::map<std::string, int>> variables_stack;// Stack of variable scopes
    std::vector<std::string> bytecode;                     // Vector to hold bytecode lines
    std::map<std::string, int> labels;                     // Map of labels to line numbers
    int program_counter;                                   // Current instruction index
    int end_of_file;                                       // Index representing end of bytecode

    // Helper function to retrieve the value of a variable or literal
    int get_value(const std::string& value) {
        // Check if the string represents a numeric value
        if (!value.empty() && (std::isdigit(value[0]) || (value[0] == '-' && value.size() > 1 && std::isdigit(value[1])))) {
            bool is_numeric = true;
            for (size_t i = 1; i < value.size(); ++i) {
                if (!std::isdigit(value[i])) {
                    is_numeric = false;
                    break;
                }
            }
            if (is_numeric) {
                return std::stoi(value);                        // Convert string to integer
            }
        }
        // Treat the value as a variable name
        auto& vars = variables_stack.top();
        if (vars.find(value) == vars.end()) {vars[value] = 0;}  // Initialize variable to 0 if not found
        return vars[value];                                     // Return variable value
    }

public:
    // Constructor to initialize the interpreter and load bytecode
    Interpreter() {
        std::ifstream file("output.bc");                        // Open the bytecode file
        std::string line;                                       // Line buffer
        int line_number = 0;                                    // Line counter

        while (std::getline(file, line)) {
            line_number++;

            // Set program counter to 'main' label
            if (line == "main:") {
                program_counter = line_number;
            }

            // Store labels with their corresponding line numbers
            if (line.find(":") != std::string::npos) {
                std::string label = line.substr(0, line.find(":"));
                labels[label] = line_number;
            }

            bytecode.push_back(line);                          // Add line to bytecode vector
        }
    
        end_of_file = line_number + 1;                         // Set end of file marker
        variables_stack.push(std::map<std::string, int>());    // Initialize global variable scope
    }

  // Function to execute the bytecode instructions
  void execute_instructions() {
    //std::cout << "Running the program..." << std::endl;
    while(true) {
        // Switch based on the Instruction enum
        std::string line = bytecode[program_counter - 1];
        //std::cout << "Line: " << line << std::endl;
        if(line.empty() || line.find(":") != std::string::npos){
            program_counter++;
            continue;
        }
        // Extract the instruction and its argument
        size_t space_pos = line.find(" ");
        std::string instruction_str = (space_pos != std::string::npos) ? line.substr(0, space_pos) : line;
        // Get the Instruction enum
        Instruction instruction = getInstructionEnum(instruction_str);
        std::string args = (space_pos != std::string::npos) ? line.substr(space_pos + 1) : "";
        switch (instruction) {
            case Instruction::ILOAD: { // iload
                if(args.empty()) {throw std::runtime_error("iload requires a variable name");}
                std::string var_name = args;
                // Set default value if variable not found
                if (variables_stack.top().find(var_name) == variables_stack.top().end()) {
                    variables_stack.top()[var_name] = 0;
                }
                operand_stack.push(std::to_string(variables_stack.top()[var_name]));
                program_counter++;
                break;
            }
            case Instruction::ICONST: { // iconst
                if (args.empty()) {throw std::runtime_error("iconst requires an integer argument");}
                int value = std::stoi(args);
                operand_stack.push(std::to_string(value));
                program_counter++;
                break;
            }
            case Instruction::ISTORE: { // istore
                if(!operand_stack.empty()){
                    std::string n = line.substr(line.find(" ") + 1);
                    int value = get_value(operand_stack.top());
                    //std::cout << "istore running: "<< value << std::endl;
                    variables_stack.top()[n] = value;
                    operand_stack.pop();
                }
                program_counter++;
                break;
            }
            case Instruction::IADD: { // iadd
                //std::cout << "iadd running" << std::endl;
                int value1 = get_value(operand_stack.top());
                operand_stack.pop();
                int value2 = get_value(operand_stack.top());
                operand_stack.pop();
                int result = value2 + value1;
                operand_stack.push(std::to_string(result));
                program_counter++;
                break;
            }
            case Instruction::ISUB: { // isub
                if (operand_stack.size() < 2) {throw std::runtime_error("isub requires at least two values on the operand_stack");}
                int value1 = get_value(operand_stack.top());
                operand_stack.pop();
                int value2 = get_value(operand_stack.top());
                operand_stack.pop();
                int result = value2 - value1;
                operand_stack.push(std::to_string(result));
                program_counter++;
                break;
            }
            case Instruction::IMUL: { // imul
                if (operand_stack.size() < 2) {throw std::runtime_error("imul requires at least two values on the operand_stack");}
                int value1 = get_value(operand_stack.top());
                operand_stack.pop();
                int value2 = get_value(operand_stack.top());
                operand_stack.pop();
                int result = value2 * value1;
                operand_stack.push(std::to_string(result));
                program_counter++;
                break;
            }
            case Instruction::IDIV: { // idiv
                if (operand_stack.size() < 2) {throw std::runtime_error("idiv requires at least two values on the operand_stack");}
                int value1 = get_value(operand_stack.top());
                if (value1 == 0) {throw std::runtime_error("Division by zero");}
                operand_stack.pop();
                int value2 = get_value(operand_stack.top());
                operand_stack.pop();
                int result = value2 / value1;
                operand_stack.push(std::to_string(result));
                program_counter++;
                break;
            }
            case Instruction::IGT: { // igt
                if (operand_stack.size() < 2) {throw std::runtime_error("igt requires at least two values on the operand_stack");}
                int value1 = get_value(operand_stack.top());
                operand_stack.pop();
                int value2 = get_value(operand_stack.top());
                operand_stack.pop();
                int result;
                if (value2 > value1) { result = 1; } 
                else { result = 0; }
                operand_stack.push(std::to_string(result));
                program_counter++;
                break;
            }
            case Instruction::ILT: { // ilt
                if (operand_stack.size() < 2) {throw std::runtime_error("ilt requires at least two values on the operand_stack");}
                int value1 = get_value(operand_stack.top());
                operand_stack.pop();
                int value2 = get_value(operand_stack.top());
                operand_stack.pop();
                int result;
                if (value2 < value1) { result = 1; } 
                else { result = 0; }
                operand_stack.push(std::to_string(result));
                program_counter++;
                break;
            }
            case Instruction::IEQ: { // ieq
                if (operand_stack.size() < 2) {throw std::runtime_error("ieq requires at least two values on the operand_stack");}
                int value1 = get_value(operand_stack.top());
                operand_stack.pop();
                int value2 = get_value(operand_stack.top());
                operand_stack.pop();
                int result;
                if (value2 == value1) { result = 1; } 
                else { result = 0; }
                operand_stack.push(std::to_string(result));
                program_counter++;
                break;
            }
            case Instruction::IOR: { // ior
                if (operand_stack.size() < 2) {throw std::runtime_error("ior requires at least two values on the operand_stack");}
                int value1 = get_value(operand_stack.top());
                operand_stack.pop();
                int value2 = get_value(operand_stack.top());
                operand_stack.pop();
                int result;
                if (value1 + value2 > 0) { result = 1; } 
                else { result = 0; } 
                operand_stack.push(std::to_string(result));
                program_counter++;
                break;
            }
            case Instruction::IAND: { // iand
                if (operand_stack.size() < 2) {throw std::runtime_error("iand requires at least two values on the operand_stack");}
                int value1 = get_value(operand_stack.top());
                operand_stack.pop();
                int value2 = get_value(operand_stack.top());
                operand_stack.pop();
                int result;
                if (value1 * value2 == 1) { result = 1; } 
                else { result = 0; }
                operand_stack.push(std::to_string(result));
                program_counter++;
                break;
            }
            case Instruction::INOT: { // inot
                if (operand_stack.empty()) {throw std::runtime_error("inot requires at least one value on the operand_stack");}
                int value1 = get_value(operand_stack.top());
                operand_stack.pop();
                int result;
                if (value1 == 0) { result = 1; } 
                else { result = 0; }
                operand_stack.push(std::to_string(result));
                program_counter++;
                break;
            }
            case Instruction::GOTO: { // goto
                if (args.empty()) {throw std::runtime_error("goto requires a label argument");}
                std::string label = args;
                if (labels.find(label) == labels.end()) {throw std::runtime_error("Unknown label: " + label);}
                program_counter = labels[label];
                break;
            }
            case Instruction::IFFALSE: { // iffalse
                if (args.empty()) {throw std::runtime_error("iffalse requires a label argument");}
                if (operand_stack.empty()) {throw std::runtime_error("iffalse requires at least one value on the operand_stack");}

                int value1 = get_value(operand_stack.top());
                operand_stack.pop();
                std::string label = line.substr(line.rfind(" ") + 1);
                if(value1 == 0){
                    //std::cout << "iffalse: " << label << std::endl;
                    program_counter = labels[label];
                } else { program_counter++; }
                break;
            }
            case Instruction::INVOKEVIRTUAL: { // invokevirtual
                //std::cout << "running test for invokevirtual" << std::endl;
                if (args.empty()) {throw std::runtime_error("invokevirtual requires a method name argument");}
                std::string method = args;
                if (labels.find(method) == labels.end()) {throw std::runtime_error("Unknown method: " + method);}
                arg_stack.push(program_counter + 1);
                variables_stack.push(std::map<std::string, int>());
                program_counter = labels[method];
                break;
            }
            case Instruction::IRETURN: { // ireturn
                if (arg_stack.empty()) {throw std::runtime_error("ireturn called without a matching invokevirtual");}
                program_counter = arg_stack.top();
                arg_stack.pop();
                if (variables_stack.empty()) {throw std::runtime_error("Variable operand_stack underflow on ireturn");}
                variables_stack.pop();
                break;
            }
            case Instruction::PRINT: { // print
                //std::cout << "running test for print" << std::endl;
                if (operand_stack.empty()) {throw std::runtime_error("print attempted on an empty operand_stack");}
                std::cout << get_value(operand_stack.top()) << std::endl;
                operand_stack.pop();
                program_counter++;
                break;
            }
            case Instruction::STOP: { // stop
                throw StopException();
                return;
            }
            case Instruction::UNKNOWN: { // Unknown instruction
                std::cout << "testing Unknown instruction: " << instruction_str << std::endl;
                throw std::runtime_error("Unknown instruction: " + instruction_str);
                break;
            }
            default: { // Fallback for safety
                throw std::runtime_error("Unhandled instruction: " + instruction_str);
                break;
            }
        }
    }
}
};

int main(){
    Interpreter interpreter;
    try {
        interpreter.execute_instructions();
    }
    catch (const StopException& e) {
        //std::cout << "SUCCESS PROGRAM STOPPED AT STOP INSTRUCTION" << std::endl;
    }
    catch (const std::exception& e){
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}