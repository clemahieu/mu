#pragma once

namespace mu
{
	namespace io
	{
		namespace ast
		{
			class expression;
			class parameters;
			class identifier;
			class end;
			class cluster;
			class visitor
			{
			public:
				virtual void operator () (mu::io::ast::cluster * cluster_a) = 0;
				virtual void operator () (mu::io::ast::parameters * parameters_a) = 0;
				virtual void operator () (mu::io::ast::expression * expression_a) = 0;
				virtual void operator () (mu::io::ast::identifier * identifier_a) = 0;
				virtual void operator () (mu::io::ast::end * end_a) = 0;
			};
		}
	}
}
