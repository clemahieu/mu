#pragma once

#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>

namespace lambda_p
{
	class routine;
	namespace errors
	{
		class error_target;
	}
}
namespace lambda_p_io
{
	namespace ast
	{
		class expression;
		class visitor;
	}
	namespace analyzer
	{
		namespace extensions
		{
			class extensions;
			class extension;
		}
		class analyzer
		{
		public:
			analyzer (boost::function <void (boost::shared_ptr <lambda_p::routine>)> target_a, boost::shared_ptr <lambda_p::errors::error_target> errors_a);
			analyzer (boost::function <void (boost::shared_ptr <lambda_p::routine>)> target_a, boost::shared_ptr <lambda_p::errors::error_target> errors_a, boost::shared_ptr <lambda_p_io::analyzer::extensions::extensions> extensions_a);
			void operator () (boost::shared_ptr <lambda_p_io::ast::expression> expression_a);
			boost::shared_ptr <lambda_p_io::analyzer::extensions::extensions> extensions;
			boost::function <void (boost::shared_ptr <lambda_p::routine>)> target;
			boost::shared_ptr <lambda_p::errors::error_target> errors;
		};
	}
}

