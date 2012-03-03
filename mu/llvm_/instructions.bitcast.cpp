#include <mu/llvm_/instructions.bitcast.h>

#include <mu/core/errors.error_target.h>
#include <mu/llvm_/instruction.node.h>
#include <mu/llvm_/type.node.h>

#include <llvm/Value.h>
#include <llvm/DerivedTypes.h>
#include <llvm/BasicBlock.h>
#include <llvm/Instructions.h>

#include <sstream>

#include <boost/make_shared.hpp>

void mu::llvm_::instructions::bitcast::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters_a, std::vector <boost::shared_ptr <mu::core::node>> & results_a)
{
	auto one (boost::dynamic_pointer_cast <mu::llvm_::value::node> (parameters_a [0]));
	auto two (boost::dynamic_pointer_cast <mu::llvm_::type::node> (parameters_a [1]));
	if (one.get () != nullptr)
	{
		if (two.get () != nullptr)
		{
			auto instruction (new llvm::BitCastInst (one->value (), two->type ()));
			results_a.push_back (boost::make_shared <mu::llvm_::instruction::node> (instruction, two));
		}
		else
		{
			invalid_type (errors_a, parameters_a [1], 1);
		}
	}
	else
	{
		invalid_type (errors_a, parameters_a [0], 0);
	}
}

size_t mu::llvm_::instructions::bitcast::count ()
{
	return 2;
}
