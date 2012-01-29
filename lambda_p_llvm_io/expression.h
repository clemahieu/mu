#pragma once

#include <lambda_p/visitor.h>

#include <map>
#include <vector>

#include <boost/shared_ptr.hpp>

namespace llvm
{
	class Value;
	class Function;
	class BasicBlock;
}
namespace lambda_p
{
	class expression;
	namespace errors
	{
		class error_target;
	}
}
namespace lambda_p_llvm
{
	class operation;
	namespace value
	{
		class node;
	}
	namespace function
	{
		class node;
	}
}
namespace lambda_p_llvm_io
{
	class expression : public lambda_p::visitor
	{
	public:
		expression (boost::shared_ptr <lambda_p::errors::error_target> errors_a, llvm::BasicBlock * & block_a, std::map <boost::shared_ptr <lambda_p::expression>, std::vector <boost::shared_ptr <lambda_p::node>>> & values_a, boost::shared_ptr <lambda_p::expression> expression_a);
		std::map <boost::shared_ptr <lambda_p::expression>, std::vector <boost::shared_ptr <lambda_p::node>>> & values;
		void operator () (lambda_p::expression * expression_a) override;
		void operator () (lambda_p::reference * reference_a) override;
		void operator () (lambda_p::link * link_a) override;
		void operator () (lambda_p::node * node_a) override;
		void not_callable ();
		bool process_target (boost::shared_ptr <lambda_p::node> node_a);
		boost::shared_ptr <lambda_p::errors::error_target> errors;
		std::vector <boost::shared_ptr <lambda_p::node>> arguments;
		llvm::BasicBlock * & block;
		boost::shared_ptr <lambda_p::node> current;
		boost::shared_ptr <lambda_p_llvm::operation> target;
	};
}

