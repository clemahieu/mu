#pragma once

#include <lambda_p_serialization/ast/visitor.h>

#include <boost/shared_ptr.hpp>

#include <map>

namespace lambda_p
{
	namespace core
	{
		class entry;
		class pipe;
		class target;
	}
	namespace errors
	{
		class error_list;
	}
}
namespace lambda_p_serialization
{
	namespace analyzer
	{
		class analyzer;
		class declaration;
		class routine
		{
		public:
			routine (lambda_p_serialization::analyzer::analyzer & analyzer_a, lambda_p_serialization::ast::expression * expression_a, std::map <std::wstring, boost::shared_ptr <lambda_p_serialization::analyzer::declaration>> declarations_a);
			boost::shared_ptr <lambda_p::core::entry> entry;
			boost::shared_ptr <lambda_p::core::pipe> pipe;
			boost::shared_ptr <lambda_p::errors::error_list> errors;
			std::map <std::wstring, boost::shared_ptr <lambda_p_serialization::analyzer::declaration>> declarations;
			std::multimap <std::wstring, boost::shared_ptr <lambda_p::core::target>> unresolved;
		};
	}
}

