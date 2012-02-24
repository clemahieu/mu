#pragma once

#include <core/context.h>
#include <lambda_p_io/ast/visitor.h>

#include <boost/shared_ptr.hpp>

#include <map>
#include <utility>

namespace mu
{
	namespace core
	{
		class node;
		class expression;
		class routine;
		namespace errors
		{
			class error_target;
		}
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
			void resolve_local (std::wstring, boost::shared_ptr <mu::core::node>, mu::core::context context_a);
			boost::shared_ptr <mu::core::routine> routine_m;
			std::map <std::wstring, boost::shared_ptr <mu::core::node>> declarations;
		};
	}
}

