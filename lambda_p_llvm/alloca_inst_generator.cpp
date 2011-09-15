#include "alloca_inst_generator.h"

alloca_inst_generator::alloca_inst_generator (::llvm::BasicBlock & block_a)
	: block (block_a)
{
}

alloca_inst_generator::~alloca_inst_generator(void)
{
}
