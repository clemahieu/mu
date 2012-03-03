#include <mu/llvm_/basic_block.instruction_insert.h>

#include <mu/core/errors.error_target.h>
#include <mu/llvm_/basic_block.insert.h>
#include <mu/llvm_/basic_block.node.h>

#include <boost/make_shared.hpp>

mu::llvm_::basic_block::instruction_insert::instruction_insert (boost::shared_ptr <mu::llvm_::basic_block::node> block_a, boost::shared_ptr <mu::script::operation> instruction_a)
	: block (block_a),
	instruction (instruction_a)
{
}

void mu::llvm_::basic_block::instruction_insert::perform (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	std::vector <boost::shared_ptr <mu::core::node>> r1;
	r1.push_back (block);
	instruction->perform (errors_a, parameters, r1);
	if (!(*errors_a) ())
	{
		assert (r1.size () == 2);
		mu::llvm_::basic_block::insert insert;
		insert.perform (errors_a, r1, results);
		results.push_back (r1 [1]);
	}
}
