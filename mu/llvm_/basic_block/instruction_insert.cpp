#include "instruction_insert.h"

#include <mu/core/errors/error_target.h>
#include <mu/llvm_/basic_block/insert.h>
#include <mu/llvm_/basic_block/node.h>

#include <boost/make_shared.hpp>

mu::llvm_::basic_block::instruction_insert::instruction_insert (boost::shared_ptr <mu::llvm_::basic_block::node> block_a, boost::shared_ptr <mu::script::operation> instruction_a)
	: block (block_a),
	instruction (instruction_a)
{
}

void mu::llvm_::basic_block::instruction_insert::operator () (mu::script::context & context_a)
{
	std::vector <boost::shared_ptr <mu::core::node>> r1;
	r1.push_back (block);
    auto ctx (mu::script::context (context_a.errors, context_a.parameters, r1));
	(*instruction) (ctx);
	if (!(*context_a.errors) ())
	{
		assert (r1.size () == 2);
		mu::llvm_::basic_block::insert insert;
        auto ctx (mu::script::context (context_a.errors, r1, context_a.results));
		insert (ctx);
		context_a.results.push_back (r1 [1]);
	}
}