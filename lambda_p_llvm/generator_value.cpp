#include "generator_value.h"

#include <lambda_p/binder/binder_implementor.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Instructions.h>
#include <llvm/BasicBlock.h>
#include <llvm/Value.h>

#include <sstream>

lambda_p_llvm::generator_value::generator_value (llvm::Value * value_a, llvm::BasicBlock * block_a)
	: value (value_a),
	block (block_a)
{
}

void lambda_p_llvm::generator_value::bind (lambda_p::core::statement * statement, lambda_p::binder::list & nodes, lambda_p::errors::error_list & problems)
{
	std::vector <llvm::Value *> arguments;
	for (auto i = statement->association->references.begin (); i != statement->association->references.end (); ++i)
	{
		auto value (boost::dynamic_pointer_cast <lambda_p_llvm::generator_value> (nodes [*i]));
		if (value->value->getType ()->isVoidTy ())
		{
			arguments.push_back (llvm::ConstantInt::get (llvm::Type::getInt1Ty (block->getContext ()), 0));
		}
		else
		{
			arguments.push_back (value->value);
		}
	}
	auto call (llvm::CallInst::Create (value, arguments.begin (), arguments.end ()));
	block->getInstList ().push_back (call);
	boost::shared_ptr <lambda_p_llvm::generator_value> result (new lambda_p_llvm::generator_value (call, block));
	nodes [statement->association->declarations [0]] = result;
}

std::wstring lambda_p_llvm::generator_value::binder_name ()
{
	return std::wstring (L"generator_value");
}