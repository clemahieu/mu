#pragma once

#include <mu/io/ast/node.h>

namespace mu
{
	namespace io
	{
		namespace ast
		{
			class identifier;
			class expression : public mu::io::ast::node
			{
			public:
				expression (mu::io::context context_a, mu::vector <mu::io::ast::node *> values);
				expression (mu::io::context context_a, mu::vector <mu::io::ast::node *> values, mu::vector <mu::io::ast::identifier *> individual_names);
				expression (mu::io::context context_a, mu::vector <mu::io::ast::node *> values, mu::vector <mu::io::ast::identifier *> individual_names, mu::io::ast::identifier * full_name);
                mu::string name () override;
				void operator () (mu::io::ast::visitor * visitor_a) override;
				mu::vector <mu::io::ast::node *> values;
				mu::vector <mu::io::ast::identifier *> individual_names;
				mu::io::ast::identifier * full_name;
			};
		}
	}
}
