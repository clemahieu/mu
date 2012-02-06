#pragma once

#include <boost/shared_ptr.hpp>

#include <lambda_p/segment.h>

#include <vector>
#include <map>

namespace llvm
{
	class BasicBlock;
	class FunctionType;
	class Function;
	class Argument;
	class Instruction;
	class Type;
}
namespace lambda_p
{
	class node;
	class routine;
	class expression;
	namespace errors
	{
		class error_target;
	}
}
namespace lambda_p_llvm
{
	namespace module
	{
		class node;
	}
	namespace function_pointer
	{
		class node;
	}
	namespace value
	{
		class node;
	}
}
namespace lambda_p_llvm_io
{
	class routine
	{
	public:
		routine (boost::shared_ptr <lambda_p::errors::error_target> errors_a, boost::shared_ptr <lambda_p::routine> routine_a, boost::shared_ptr <lambda_p_llvm::module::node> module_a);
		void add_function (boost::shared_ptr <lambda_p_llvm::module::node> module_a, std::vector <llvm::BasicBlock *> & blocks, llvm::FunctionType * type, bool multy, std::vector <llvm::Argument *> & arguments);
		void try_resolve ();
		boost::shared_ptr <lambda_p_llvm::function_pointer::node> result;
		std::map <boost::shared_ptr <lambda_p::expression>, std::vector <boost::shared_ptr <lambda_p::node>>> values;
		std::vector <llvm::Instruction *> instructions;
		std::vector <llvm::Type *> parameters;
		llvm::Type * return_m;
		size_t unresolved;
		boost::shared_ptr <lambda_p::errors::error_target> errors;
		boost::shared_ptr <lambda_p::routine> routine_m;
		boost::shared_ptr <lambda_p_llvm::module::node> module;
	};
}

