#include "bitcast.h"

#include <mu/core/errors/error_target.h>
#include <mu/llvm_/instruction/node.h>
#include <mu/llvm_/type/node.h>
#include <mu/script/check.h>

#include <llvm/Value.h>
#include <llvm/DerivedTypes.h>
#include <llvm/BasicBlock.h>
#include <llvm/Instructions.h>

#include <sstream>

#include <boost/make_shared.hpp>

void mu::llvm_::instructions::bitcast::operator () (mu::script::context & context_a)
{
	if (mu::script::check <mu::llvm_::value::node, mu::llvm_::type::node> () (context_a))
	{
		auto one (boost::static_pointer_cast <mu::llvm_::value::node> (context_a.parameters [0]));
		auto two (boost::static_pointer_cast <mu::llvm_::type::node> (context_a.parameters [1]));
		auto instruction (new llvm::BitCastInst (one->value (), two->type ()));
		context_a.results.push_back (boost::make_shared <mu::llvm_::instruction::node> (instruction, two));
	}
}

size_t mu::llvm_::instructions::bitcast::count ()
{
	return 2;
}