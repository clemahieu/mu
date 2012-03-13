#pragma once

#include <mu/core/context.h>
#include <mu/io/ast/visitor.h>

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
		namespace debugging
		{
			class routine;
			class node;
		}
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
				void resolve_local (std::wstring, boost::shared_ptr <mu::core::node> node_a, mu::io::debugging::node * node_info_a);
				boost::shared_ptr <mu::core::routine> routine_m;
				mu::io::debugging::routine * routine_info;
				std::map <std::wstring, std::pair <boost::shared_ptr <mu::core::node>, mu::io::debugging::node *>> declarations;
			};
		}
	}
}

