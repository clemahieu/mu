#include <mu/llvm_/basic_block/instruction_insert.h>

#include <mu/core/errors/error_target.h>
#include <mu/llvm_/basic_block/insert.h>
#include <mu/llvm_/basic_block/node.h>
#include <mu/script/context.h>

#include <boost/make_shared.hpp>

#include <vector>

mu::llvm_::basic_block::instruction_insert::instruction_insert (boost::shared_ptr <mu::llvm_::basic_block::node> block_a, boost::shared_ptr <mu::script::operation> instruction_a)
	: block (block_a),
	instruction (instruction_a)
{
}

bool mu::llvm_::basic_block::instruction_insert::operator () (mu::script::context & context_a)
{
	bool result (true);
	context_a.push (block);
	context_a.slide ();
	context_a.push (instruction);
	context_a.push (context_a.parameters_begin (), context_a.parameters_end ());
	result = context_a ();
	if (result)
	{
		assert (context_a.working_size () == 1);
		context_a.slide ();
		context_a.push (boost::make_shared <mu::llvm_::basic_block::insert> ());
		context_a.push (context_a.locals (0));
		context_a.push (context_a.locals (1));
		result = context_a ();
		assert (context_a.working_size () == 0);
		context_a.push (context_a.locals (1));
	}
	return result;
}