#ifndef CODE_GENERATOR_H
#define CODE_GENERATOR_H

#include <fstream>
#include <map>
#include "cfg.h"

class CodeGenerator {
    public:
        CodeGenerator();
        void generate(CFG* cfg);

    private:
        void generate_block_bytecode(BBlock* block, std::ofstream& stream, const std::map<BBlock*, std::string>& bblocks);
        void write_block_exits(BBlock* block, std::ofstream& stream, const std::map<BBlock*, std::string>& bblocks);
};

#endif
