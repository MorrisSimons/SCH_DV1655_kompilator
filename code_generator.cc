#include "code_generator.h"
#include "instruction.h"
#include "cfg.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <map>

// Default constructor for CodeGenerator
CodeGenerator::CodeGenerator() = default;

// Generate the bytecode from the Control Flow Graph (CFG)
void CodeGenerator::generate(CFG* cfg) {
    const auto& methods = cfg->get_methods();               // Retrieve methods from the CFG
    const auto& bblocks = cfg->get_bblocks();               // Retrieve basic blocks from the CFG
    std::ofstream stream("output.bc");                      // Open output file for writing bytecode

    // Iterate over each basic block and generate bytecode
    for (const auto& [block, label] : bblocks) {
        // Determine the block's name (method name or label)
        std::string name = !block->method.empty() ? block->method : label;
        if (name != "main") { stream << "\n"; }             // Separate blocks with a newline except for 'main'
        stream << name << ":\n";                            // Write the block's label
        generate_block_bytecode(block, stream, bblocks);    // Generate bytecode for the block

        if (name == "main") {
            stream << "stop\n";                             // Insert 'stop' instruction at the end of 'main'
        }
    }

    stream.close();                                         // Close the output file
}

// Generate bytecode for a single basic block
void CodeGenerator::generate_block_bytecode(BBlock* block, std::ofstream& stream, const std::map<BBlock*, std::string>& bblocks) {
    // Iterate over each Three Address Code (TAC) instruction in the block
    for (const auto& tac : block->instructions) {
        Instruction instruction(tac);                      // Create an Instruction object from TAC
        const auto& bytecode = instruction.get_bytecode(); // Get the bytecode representation
        // Write each line of the bytecode to the output stream
        for (const auto& line : bytecode) {
            stream << line << '\n';
        }
    }

    write_block_exits(block, stream, bblocks);             // Write exit instructions for the block
}

// Write branching instructions to handle control flow between blocks
void CodeGenerator::write_block_exits(BBlock* block, std::ofstream& stream, const std::map<BBlock*, std::string>& bblocks) {
    // If there's a condition, write an 'iffalse' instruction to the false branch
    if (block->true_branch && block->false_branch) {
        stream << "iffalse goto " << bblocks.at(block->false_branch) << '\n';
    }
    // Unconditionally jump to the true branch
    if (block->true_branch) { stream << "goto " << bblocks.at(block->true_branch) << '\n'; }
}