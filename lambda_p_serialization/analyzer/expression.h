#pragma once

#include <lambda_p_serialization/ast/visitor.h>

#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>

namespace lambda_p
{
	namespace core
	{
		class target;
		class tee;
		class call;
		class gather;
	}
	namespace errors
	{
		class error;
	}
}
namespace lambda_p_serialization
{
	namespace analyzer
	{
		class routine;
		class expression : public lambda_p_serialization::ast::visitor
		{
		public:
			expression (lambda_p_serialization::analyzer::routine & routine_a, lambda_p_serialization::ast::expression * expression_a, boost::shared_ptr <lambda_p::core::target> target_a, boost::function <void (boost::shared_ptr <lambda_p::errors::error>)> errors_a);
			void operator () (lambda_p_serialization::ast::expression * expression_a) override;
			void operator () (lambda_p_serialization::ast::identifier * identifier_a) override;
			lambda_p_serialization::analyzer::routine & routine;
			size_t position;
			boost::function <void (boost::shared_ptr <lambda_p::errors::error>)> errors;
			boost::shared_ptr <lambda_p::core::tee> tee;
			boost::shared_ptr <lambda_p::core::call> call;
			boost::shared_ptr <lambda_p::core::gather> gather;
			boost::shared_ptr <lambda_p::core::target> target;
		};
	}
}

