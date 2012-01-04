#pragma once

#include <lambda_p_io/ast/visitor.h>

#include <boost/shared_ptr.hpp>

#include <map>
#include <vector>

namespace lambda_p
{
	class entry;
	class pipe;
	class target;
	class fixed;
	namespace errors
	{
		class error_target;
	}
}
namespace lambda_p_io
{
	namespace analyzer
	{
		class analyzer;
		class declaration;
		class routine
		{
		public:
			routine (lambda_p_io::analyzer::analyzer & analyzer_a, lambda_p_io::ast::expression * expression_a, std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::declaration>> declarations_a, boost::shared_ptr <lambda_p::errors::error_target> errors_a);
			lambda_p_io::analyzer::analyzer & analyzer;
			boost::shared_ptr <lambda_p::entry> entry;
			boost::shared_ptr <lambda_p::pipe> pipe;
			void operator () (std::wstring, boost::shared_ptr <lambda_p_io::analyzer::declaration>);
			std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::declaration>> declarations;
			std::multimap <std::wstring, boost::shared_ptr <lambda_p::target>> unresolved;
		};
	}
}

