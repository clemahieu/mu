#pragma once

#include <mu/io/ast/visitor.h>

#include <cstddef>

namespace mu
{
	namespace core
	{
		class set;
		class expression;
		namespace errors
		{
			class error_target;
		}
	}
	namespace io
	{
		namespace debugging
		{
			class expression;
		}
		namespace analyzer
		{
			class routine;
			class expression : public mu::io::ast::visitor
			{
			public:
				expression (mu::io::analyzer::routine & routine_a, mu::io::ast::expression * expression_a, mu::core::expression * self_a);
				void operator () (mu::io::ast::cluster * cluster_a) override;
				void operator () (mu::io::ast::parameters * parameters_a) override;
				void operator () (mu::io::ast::expression * expression_a) override;
				void operator () (mu::io::ast::identifier * identifier_a) override;
				void operator () (mu::io::ast::value * value_a) override;
				mu::io::analyzer::routine & routine;
				mu::io::ast::expression * expression_m;
				mu::core::expression * self;
				size_t position;
			};
		}
	}
}

