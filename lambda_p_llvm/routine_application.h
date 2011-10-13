#pragma once

#include <vector>

namespace llvm
{
	class Function;
	class Type;
}
namespace lambda_p
{
	namespace binder
	{
		class node_instance;
	}
	namespace errors
	{
		class error;
	}
	namespace core
	{
		class routine;
	}
}
namespace lambda_p_llvm
{
	class value;
	class generation_context;
	class routine_application
	{
	public:
		routine_application (::lambda_p::core::routine * routine_a);
		void apply (::std::vector < ::lambda_p_llvm::value *> arguments);
		::llvm::Function * generate (::lambda_p_llvm::generation_context & context, ::std::vector < ::llvm::Type const *> open_arguments, ::std::vector < ::llvm::Type const *> results, ::std::vector < ::lambda_p::errors::error *> & problems);
		::lambda_p::core::routine * routine;
		::std::vector < size_t> indirection;
		::std::vector < ::lambda_p::binder::node_instance *> arguments;
		void erase (size_t i);
	};
}
