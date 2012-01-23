#pragma once

#include <boost/shared_ptr.hpp>

#include <lambda_p_script/segment.h>

#include <vector>

namespace llvm
{
	class BasicBlock;
	class FunctionType;
	class Function;
	class Argument;
}
namespace lambda_p
{
	class node;
	class routine;
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
		routine (boost::shared_ptr <lambda_p::errors::error_target> errors_a, boost::shared_ptr <lambda_p::routine> routine_a, boost::shared_ptr <lambda_p_llvm::module::node> module_a, lambda_p_script::segment <boost::shared_ptr <lambda_p::node>> parameters);
		void add_function (boost::shared_ptr <lambda_p_llvm::module::node> module_a, std::vector <llvm::BasicBlock *> & blocks, llvm::FunctionType * type, bool multy, std::vector <llvm::Argument *> & arguments);
		boost::shared_ptr <lambda_p_llvm::function_pointer::node> result;
	};
}

