#pragma once

#include <lambda_p_io/ast/visitor.h>

#include <boost/shared_ptr.hpp>

#include <map>
#include <utility>

namespace lambda_p
{
	class node;
	class expression;
	class routine;
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
		class resolver;
		class routine
		{
		public:
			routine (lambda_p_io::analyzer::analyzer & analyzer_a, lambda_p_io::ast::expression * expression_a);
			lambda_p_io::analyzer::analyzer & analyzer;
			void operator () (std::wstring, boost::shared_ptr <lambda_p::node>);
			boost::shared_ptr <lambda_p::routine> routine_m;
			size_t parameter_count;
			std::map <std::wstring, boost::shared_ptr <lambda_p::node>> declarations;
			std::multimap <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::resolver>> unresolved;
		};
	}
}

