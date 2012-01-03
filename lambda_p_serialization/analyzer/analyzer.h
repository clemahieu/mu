#pragma once

#include <lambda_p_serialization/ast/visitor.h>

#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>

#include <stack>

namespace lambda_p
{
	namespace core
	{
		class routine;
	}
	namespace errors
	{
		class error;
	}
}
namespace lambda_p_serialization
{
	namespace ast
	{
		class node;
		class visitor;
	}
	namespace analyzer
	{
		class analyzer : public lambda_p_serialization::ast::visitor
		{
		public:
			analyzer (boost::function <void (boost::shared_ptr <lambda_p::core::routine>)> target_a, boost::function <void (boost::shared_ptr <lambda_p::errors::error>)> errors_a);
			void operator () (boost::shared_ptr <lambda_p_serialization::ast::node> node);
			void operator () (lambda_p_serialization::ast::expression * expression_a) override;
			void operator () (lambda_p_serialization::ast::identifier * identifier_a) override;
			boost::function <void (boost::shared_ptr <lambda_p::core::routine>)> target;
			boost::function <void (boost::shared_ptr <lambda_p::errors::error> error_a)> errors;
		};
	}
}

