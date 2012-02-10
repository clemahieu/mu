#include "instruction_insert.h"

#include <lambda_p/errors/error_target.h>
#include <lambda_p_llvm/basic_block/insert.h>
#include <lambda_p_llvm/basic_block/node.h>

#include <boost/make_shared.hpp>

lambda_p_llvm::basic_block::instruction_insert::instruction_insert (boost::shared_ptr <lambda_p_llvm::basic_block::node> block_a, boost::shared_ptr <lambda_p_script::operation> instruction_a)
	: block (block_a),
	instruction (instruction_a)
{
}

void lambda_p_llvm::basic_block::instruction_insert::perform (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results)
{
	std::vector <boost::shared_ptr <lambda_p::node>> r1;
	r1.push_back (block);
	instruction->perform (errors_a, parameters, r1);
	if (!(*errors_a) ())
	{
		assert (r1.size () == 2);
		lambda_p_llvm::basic_block::insert insert;
		insert.perform (errors_a, r1, results);
		results.push_back (r1 [1]);
	}
}