#pragma once

#include <mu/core/context.h>
#include <mu/io/ast.visitor.h>

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
	namespace io
	{
		namespace analyzer
		{
			class analyzer;
			class declaration;
			class resolver;
			class routine
			{
			public:
				routine (mu::io::analyzer::analyzer & analyzer_a, mu::io::ast::expression * expression_a);
				mu::io::analyzer::analyzer & analyzer;
				void resolve_local (std::wstring, boost::shared_ptr <mu::core::node>, mu::core::context context_a);
				boost::shared_ptr <mu::core::routine> routine_m;
				std::map <std::wstring, boost::shared_ptr <mu::core::node>> declarations;
			};
		}
	}
}

