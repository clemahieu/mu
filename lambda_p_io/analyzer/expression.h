#pragma once

#include <lambda_p_io/ast/visitor.h>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	class target;
	class tee;
	class call;
	class gather;
	namespace errors
	{
		class error_target;
	}
}
namespace lambda_p_io
{
	namespace analyzer
	{
		class routine;
		class expression : public lambda_p_io::ast::visitor
		{
		public:
			expression (lambda_p_io::analyzer::routine & routine_a, lambda_p_io::ast::expression * expression_a, boost::shared_ptr <lambda_p::target> target_a, boost::shared_ptr <lambda_p::errors::error_target> errors_a);
			void operator () (lambda_p_io::ast::expression * expression_a) override;
			void operator () (lambda_p_io::ast::identifier * identifier_a) override;
			lambda_p_io::analyzer::routine & routine;
			size_t position;
			lambda_p_io::ast::expression * expression_m;
			boost::shared_ptr <lambda_p::errors::error_target> errors;
			boost::shared_ptr <lambda_p::tee> tee;
			boost::shared_ptr <lambda_p::call> call;
			boost::shared_ptr <lambda_p::gather> gather;
			boost::shared_ptr <lambda_p::target> target;
		};
	}
}

