#pragma once

#define __STDC_LIMIT_MACROS
#define __STDC_CONSTANT_MACROS

#include <llvm/BasicBlock.h>

class alloca_inst_generator
{
public:
	alloca_inst_generator (::llvm::BasicBlock & block_a);
	~alloca_inst_generator (void);
	::llvm::BasicBlock & block;
};

