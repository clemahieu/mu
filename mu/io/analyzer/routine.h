#pragma once

#include <mu/core/types.h>
#include <mu/io/debugging/context.h>
#include <mu/io/ast/visitor.h>

#include <boost/shared_ptr.hpp>

#include <map>
#include <utility>

#include <gc_allocator.h>

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
				mu::core::routine * routine_m;
			};
		}
	}
}

