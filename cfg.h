// CFG.h

#ifndef CFG_H
#define CFG_H

#include <string>
#include <vector>
#include <map>
#include <unordered_map> // Include unordered_map for the handlers map
#include <fstream>
#include <set>
#include "tac.h"
#include "Node.h"

// Class representing a Basic Block in the Control Flow Graph
class BBlock {
public:
    BBlock(); // Constructor declaration

    int temp_counter;              // Counter for temporary variables
    std::string block_id;          // Identifier for the basic block
    std::string method;            // Name of the method to which the block belongs
    std::vector<TAC*> instructions;// List of Three Address Code instructions
    TAC* condition;                // Condition for branching (if any)

    BBlock* true_branch;           // Pointer to the true branch block
    BBlock* false_branch;          // Pointer to the false branch block
    bool displayTrueBranch;        // Flag to display the true branch in the graph
    bool displayFalseBranch;       // Flag to display the false branch in the graph
};

// Class representing the Control Flow Graph
class CFG {
public:
    CFG(); // Constructor
    std::string CFGTraversal(Node* root); // Parses the AST and builds the CFG
    void graph();                         // Generates the graph representation
    void add_bblock(BBlock* block);       // Adds a basic block to the CFG
    void create_BBlock(BBlock* block, std::ofstream* stream); // Helper for graph generation

    // Getter methods
    std::map<BBlock*, std::string> get_bblocks(); // Returns the map of basic blocks
    std::vector<BBlock*> get_methods();           // Returns the list of method blocks

private:
    int block_count;                           // Counter for naming blocks
    BBlock* active_block;                      // Pointer to the current active block
    std::map<BBlock*, std::string> bblocks;    // Map of blocks to their names
    std::set<BBlock*> rendered_bblocks;        // Set of blocks already rendered in the graph
    std::vector<BBlock*> methods;              // List of method blocks

    // Type definition for handler functions
    typedef std::string (CFG::*HandlerFunc)(Node* root);

    // Map of handlers for different node types
    std::unordered_map<std::string, HandlerFunc> handlers;

    // Function to initialize handlers
    void initHandlers();

    // Handler function declarations
    std::string handleMethodDeclaration(Node* root);
    std::string handleReturn(Node* root);
    std::string handlePrintlnStatement(Node* root);
    std::string handleIfElseStatement(Node* root);
    std::string handleWhileStatement(Node* root);
    std::string handleMethodCallExpression(Node* root);
    std::string handleNotExpression(Node* root);
    std::string handleBinaryExpression(Node* root);
    std::string handleExpression(Node* root);
    std::string handleArrayLength(Node* root);
    std::string handleAssignStatement(Node* root);
    std::string handleArrayAssignStatement(Node* root);
    // Add other handler function declarations as needed
};

#endif // CFG_H