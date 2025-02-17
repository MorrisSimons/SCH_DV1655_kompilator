#include "cfg.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <set>
#include <iterator>

// Constructor for Basic Block (BBlock)
BBlock::BBlock() {
    // Initialize temporary variable counter
    temp_counter = 0;
    // Set default block identifier
    block_id = "block_";
    // Initialize method name
    method = "";
    // Initialize the list of instructions (Three Address Code)
    instructions = std::vector<TAC*>();
    // Initialize condition and branch pointers
    condition = nullptr;
    true_branch = nullptr;
    false_branch = nullptr;
    // Set flags to display branch conditions
    displayTrueBranch = true;
    displayFalseBranch = true;
}

// Constructor for Control Flow Graph (CFG)
CFG::CFG() {
    // Initialize block counter
    block_count = 0;
    // Set the active block to null
    active_block = nullptr;
    // Clear the basic blocks map
    bblocks.clear();
    // Clear the set of rendered basic blocks
    rendered_bblocks.clear();
    // Clear the list of methods
    methods.clear();
    // Initialize handlers for different node types
    initHandlers();
}

// Initialize the map of handlers for different node types
void CFG::initHandlers() {
    // Map each node type to its corresponding handler function
    handlers["MethodCallExpression"] = &CFG::handleMethodCallExpression;
    handlers["MethodDeclaration"] = &CFG::handleMethodDeclaration;
    handlers["Return"] = &CFG::handleReturn;
    // Handle Expressions
    handlers["NotExpression"] = &CFG::handleNotExpression;
    handlers["Expression"] = &CFG::handleExpression;
    handlers["GreaterThanExpression"] = &CFG::handleBinaryExpression;
    handlers["LessThanExpression"] = &CFG::handleBinaryExpression;
    handlers["EqualExpression"] = &CFG::handleBinaryExpression;
    handlers["AddExpression"] = &CFG::handleBinaryExpression;
    handlers["SubExpression"] = &CFG::handleBinaryExpression;
    handlers["DivExpression"] = &CFG::handleBinaryExpression;
    handlers["MulExpression"] = &CFG::handleBinaryExpression;
    handlers["AndExpression"] = &CFG::handleBinaryExpression;
    handlers["OrExpression"] = &CFG::handleBinaryExpression;
    // Map statements to their handlers
    handlers["WhileStatement"] = &CFG::handleWhileStatement;
    handlers["IfElseStatement"] = &CFG::handleIfElseStatement;
    handlers["ArrayLength"] = &CFG::handleArrayLength;
    handlers["AssignStatement"] = &CFG::handleAssignStatement;
    handlers["ArrayAssignStatement"] = &CFG::handleArrayAssignStatement;
    handlers["PrintlnStatement"] = &CFG::handlePrintlnStatement;
}

// Main traversal function for the CFG
std::string CFG::CFGTraversal(Node* root) {
    // Check if a handler exists for this node type
    auto it = handlers.find(root->type);
    if (it != handlers.end()) {
        // Call the handler function
        return (this->*(it->second))(root);
    } else {
        // Handle specific node types directly
        if (root->type == "IntLiteral" || root->type == "Identifier") { return root->value; }
        else if (root->type == "SubIntLiteral") { return "-" + root->value; } 
        else if (root->type == "TrueExpression") { return "True"; }
        else if (root->type == "FalseExpression") { return "False"; }
        else if (root->type == "ThisExpression") { return "This"; }
        else {
            // For other node types, traverse their children
            for (auto child : root->children) {
            CFGTraversal(child);
            }
            return root->value;
        }
        }
    }

// Handle method call expressions
std::string CFG::handleMethodCallExpression(Node* root) {
    // Generate a temporary variable for the method call result
    std::string block_id = "_t" + std::to_string(active_block->temp_counter++);
    auto it = root->children.begin();

    // If there are more than one child, skip the first (object on which the method is called)
    if (std::distance(root->children.begin(), root->children.end()) > 1) {
        it = std::next(it, 1);
    }
    std::string f = "";
    if (it != root->children.end()) {
        // Get the method name
        Node* method_name = *it;
        f = method_name->value;
        it = std::next(it);
    }

    int N = 0;

    if (it != root->children.end()) {
        // Get method arguments
        Node* arguments = *it;
        for (auto arg_it = arguments->children.begin(); arg_it != arguments->children.end(); ++arg_it) {
            // Process each argument
            std::string argument_name = CFGTraversal(*arg_it);
            Argument* argument = new Argument(argument_name);
            // Add argument to instructions
            active_block->instructions.push_back(argument);
            N++;
        }
    }

    // Create method call instruction
    MethodCall* method_call = new MethodCall(block_id, f, std::to_string(N));
    // Add method call to instructions
    active_block->instructions.push_back(method_call);
    return block_id;
}

// Handle method declarations
std::string CFG::handleMethodDeclaration(Node* root) {
    // Create a new basic block for the method
    BBlock* method_block = new BBlock();
    // Set the method name
    method_block->method = root->value;
    // Set the active block to the method block
    active_block = method_block;

    Node* parameters = nullptr;
    if (root->children.size() >= 2) {
        // Get method parameters
        parameters = *std::next(root->children.begin(), 1);
        for (auto it = parameters->children.rbegin(); it != parameters->children.rend(); ++it) {
            // Get parameter name
            Node* parameter_child = *std::prev((*it)->children.end(), 1);
            std::string parameter_name = parameter_child->value;
            // Create parameter instruction
            Parameter_cfg* parameter = new Parameter_cfg(parameter_name);
            active_block->instructions.push_back(parameter);
        }
    }

    Node* body = nullptr;
    if (!root->children.empty()) {
        // Get method body
        body = root->children.back();
        // Traverse method body statements
        for (auto& stmt : body->children) {
            CFGTraversal(stmt);
        }
    }

    if (active_block) {
        // Add the method block to basic blocks
        add_bblock(active_block);
        active_block = nullptr;
    }

    // Do not display true condition for method block
    method_block->displayTrueBranch = false;
    add_bblock(method_block);
    return "";
}

// Handle return statements
std::string CFG::handleReturn(Node* root) {
    if (!root->children.empty()) {
        // Get return expression
        Node* expr = root->children.front();
        std::string return_value = CFGTraversal(expr);
        // Create return instruction
        Return* ret_statement = new Return(return_value);
        active_block->instructions.push_back(ret_statement);
    }
    // Add the current block to basic blocks
    add_bblock(active_block);
    active_block = nullptr;
    return "";
}

// Handle logical NOT expressions
std::string CFG::handleNotExpression(Node* root) {
    // Generate a temporary variable for the result
    std::string block_id = "_t" + std::to_string(active_block->temp_counter++);
    if (!root->children.empty()) {
        // Get the operand
        Node* operand = root->children.front();
        std::string rhs = CFGTraversal(operand);
        // Create unary expression instruction
        UnaryExpression* expression = new UnaryExpression(block_id, "!", rhs);
        active_block->instructions.push_back(expression);
        return block_id;
    }
    return "";
}

// Handle generic expressions
std::string CFG::handleExpression(Node* root) {
    if (!root->children.empty()) {
        // Traverse the expression
        Node* expr = root->children.front();
        return CFGTraversal(expr);
    }
    return "";
}

// Handle binary expressions (e.g., arithmetic, logical)
std::string CFG::handleBinaryExpression(Node* root) {
    // Determine the operator based on node type
    std::string op;
    if (root->type == "GreaterThanExpression") { op = ">"; } 
    else if (root->type == "LessThanExpression") { op = "<"; } 
    else if (root->type == "EqualExpression") { op = "=="; } 
    else if (root->type == "OrExpression") { op = "||"; } 
    else if (root->type == "AndExpression") { op = "and"; } 
    else if (root->type == "AddExpression") { op = "+"; } 
    else if (root->type == "SubExpression") { op = "-"; } 
    else if (root->type == "DivExpression") { op = "/"; } 
    else if (root->type == "MulExpression") { op = "*"; }

    // Generate a temporary variable for the result
    std::string block_id = "_t" + std::to_string(active_block->temp_counter++);
    if (root->children.size() >= 2) {
        // Get left and right operands
        Node* left = *std::next(root->children.begin(), 0);
        Node* right = *std::next(root->children.begin(), 1);
        std::string left_op = CFGTraversal(left);
        std::string right_op = CFGTraversal(right);
        // Create binary expression instruction
        Expression* expression = new Expression(block_id, left_op, op, right_op);
        active_block->instructions.push_back(expression);
        return block_id;
    }
    return "";
}

// Handle while statements
std::string CFG::handleWhileStatement(Node* root) {
    // Create blocks for condition, true branch, and join point
    BBlock* condition = new BBlock();
    BBlock* true_B = new BBlock();
    BBlock* join = new BBlock();

    // Set up branching from the current block to the condition block
    if (active_block->instructions.empty()) {
        active_block->true_branch = condition;
    } else {
        active_block->true_branch = condition;
        add_bblock(active_block);
        active_block = condition;
    }

    // Set up true and false branches from the condition block
    active_block->true_branch = true_B;
    active_block->false_branch = join;
    if (root->children.size() >= 1) {
        // Process the condition expression
        Node* condition_expr = root->children.front();
        std::string value = CFGTraversal(condition_expr);
        active_block->instructions.push_back(new Condition(value));
    }
    add_bblock(active_block);

    // Process the body of the while loop
    active_block = true_B;
    active_block->true_branch = condition;
    if (root->children.size() >= 2) {
        Node* body = *std::next(root->children.begin(), 1);
        CFGTraversal(body);
    }
    active_block->true_branch = condition;
    active_block->displayTrueBranch = false;
    add_bblock(active_block);

    // Continue with the join block after the loop
    active_block = join;
    add_bblock(join);
    return "";
}

// Handle if-else statements
std::string CFG::handleIfElseStatement(Node* root) {
    // Create blocks for condition, true branch, false branch, and join point
    BBlock* condition = new BBlock();
    BBlock* true_block = new BBlock();
    BBlock* false_block = new BBlock();
    BBlock* join = new BBlock();

    // Do not display branch conditions for true and false blocks
    true_block->displayTrueBranch = false;
    false_block->displayTrueBranch = false;

    // Set up branching from the current block to the condition block
    if (active_block->instructions.empty()) {
        active_block->true_branch = condition;
    } else {
        active_block->true_branch = condition;
        add_bblock(active_block);
        active_block = condition;
    }

    // Set up true and false branches from the condition block
    active_block->true_branch = true_block;
    active_block->false_branch = false_block;
    if (root->children.size() >= 1) {
        // Process the condition expression
        Node* condition_expr = root->children.front();
        std::string value = CFGTraversal(condition_expr);
        active_block->instructions.push_back(new Condition(value));
    }
    add_bblock(active_block);

    // Process the true branch
    active_block = true_block;
    active_block->true_branch = join;
    if (root->children.size() >= 2) {
        Node* true_stmt = *std::next(root->children.begin(), 1);
        CFGTraversal(true_stmt);
    }
    add_bblock(active_block);

    // Process the false branch
    active_block = false_block;
    active_block->true_branch = join;
    if (root->children.size() >= 3) {
        Node* false_stmt = *std::next(root->children.begin(), 2);
        CFGTraversal(false_stmt);
    }
    add_bblock(active_block);

    // Continue with the join block after the if-else statement
    active_block = join;
    add_bblock(join);
    return "";
}

// Handle array length expressions
std::string CFG::handleArrayLength(Node* root) {
    // Generate a temporary variable for the result
    std::string block_id = "_t" + std::to_string(active_block->temp_counter++);
    if (!root->children.empty()) {
        // Get the array variable
        Node* array = root->children.front();
        std::string array_std = CFGTraversal(array);
        // Create length instruction
        Length* length = new Length(block_id, array_std);
        active_block->instructions.push_back(length);
        return block_id;
    }
    return "";
}

// Handle assignment statements
std::string CFG::handleAssignStatement(Node* root) {
    if (root->children.size() >= 2) {
        // Get the identifier and the value to assign
        Node* id = *std::next(root->children.begin(), 0);
        std::string block_id = CFGTraversal(id);
        Node* right = *std::next(root->children.begin(), 1);
        std::string right_value = CFGTraversal(right);
        // Create copy instruction
        Copy* copy = new Copy(block_id, right_value);
        active_block->instructions.push_back(copy);
    }
    return "";
}

// Handle array assignment statements
std::string CFG::handleArrayAssignStatement(Node* root) {
    if (root->children.size() >= 3) {
        // Get the array identifier, index, and value
        Node* id = *std::next(root->children.begin(), 0);
        std::string block_id = id->value;
        Node* index = *std::next(root->children.begin(), 1);
        std::string index_string = CFGTraversal(index);
        Node* right = *std::next(root->children.begin(), 2);
        std::string right_value = CFGTraversal(right);
        // Create array copy instruction
        CopyArray* copy_array = new CopyArray(block_id, index_string, right_value);
        active_block->instructions.push_back(copy_array);
    }
    return "";
}

// Handle println statements
std::string CFG::handlePrintlnStatement(Node* root) {
    if (!root->children.empty()) {
        // Get the expression to print
        Node* expr = root->children.front();
        std::string value_to_print = CFGTraversal(expr);
        // Create print instruction
        Print* print = new Print(value_to_print);
        active_block->instructions.push_back(print);
    }
    return "";
}

// Add a basic block to the CFG
void CFG::add_bblock(BBlock* block) {
    // Avoid adding the same block multiple times
    if (bblocks.count(block)) return;
    // Generate a unique block identifier
    std::string block_id = "block_" + std::to_string(block_count++);
    block->block_id = block_id;
    // Add the block to the map of basic blocks
    bblocks[block] = block_id;
    // If the block represents a method, add it to the methods list
    if (!block->method.empty()) methods.push_back(block);
}

// Generate the graph representation of the CFG
void CFG::graph() {
    std::ofstream stream("cfg.dot");
    stream << "digraph {\n\tnode [shape=box];\n";

    // Create graph nodes and edges for each basic block
    for (const auto& pair : bblocks) {
        create_BBlock(pair.first, &stream);
    }

    stream << "}\n";
    stream.close();
}

// Recursively create graph nodes and edges for basic blocks
void CFG::create_BBlock(BBlock* block, std::ofstream* stream) {
    // Avoid rendering the same block multiple times
    if (rendered_bblocks.count(block)) return;
    rendered_bblocks.insert(block);

    std::string block_id = bblocks[block];
    if (!block->method.empty()) block_id += "_" + block->method;

    // Begin node definition
    *stream << "\t" << block_id << " [label=\"" << block_id << "\\n";

    // Add instructions to the node label
    for (auto& tac : block->instructions) {
        *stream << tac->get_tac() << "\\n";
    }
    *stream << "\"];\n";

    // Create edges to true branch
    if (block->true_branch) {
        std::string to = bblocks[block->true_branch];
        std::string from = block_id;
        std::string label = block->displayTrueBranch ? " [label=\"true\"]" : "";
        *stream << "\t" << from << " -> " << to << label << ";\n";
        create_BBlock(block->true_branch, stream);
    }

    // Create edges to false branch
    if (block->false_branch) {
        std::string to = bblocks[block->false_branch];
        std::string from = block_id;
        std::string label = block->displayFalseBranch ? " [label=\"false\"]" : "";
        *stream << "\t" << from << " -> " << to << label << ";\n";
        create_BBlock(block->false_branch, stream);
    }
}

// Get the list of method basic blocks
std::vector<BBlock*> CFG::get_methods() {
    return methods;
}

// Get the map of basic blocks
std::map<BBlock*, std::string> CFG::get_bblocks() {
    return bblocks;
}
