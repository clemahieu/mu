#pragma once

#include <lambda_p_io/ast/visitor.h>

#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>

#include <stack>
#include <map>

namespace lambda_p
{
	class expression;
	namespace errors
	{
		class error_target;
	}
}
namespace lambda_p_io
{
	namespace ast
	{
		class node;
		class visitor;
	}
	namespace analyzer
	{
		class extension;
		class analyzer : public lambda_p_io::ast::visitor
		{
		public:
			analyzer (boost::function <void (boost::shared_ptr <lambda_p::expression>)> target_a, boost::shared_ptr <lambda_p::errors::error_target> errors_a);
			analyzer (boost::function <void (boost::shared_ptr <lambda_p::expression>)> target_a, boost::shared_ptr <lambda_p::errors::error_target> errors_a, std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extension>> extensions_a);
			void operator () (boost::shared_ptr <lambda_p_io::ast::node> node);
			void operator () (lambda_p_io::ast::expression * expression_a) override;
			void operator () (lambda_p_io::ast::identifier * identifier_a) override;
			std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extension>> extensions;
			boost::function <void (boost::shared_ptr <lambda_p::expression>)> target;
			boost::shared_ptr <lambda_p::errors::error_target> errors;
		};
	}
}

