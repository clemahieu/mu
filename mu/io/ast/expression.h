#pragma once

#include <mu/io/ast/node.h>

#include <vector>

#include <boost/shared_ptr.hpp>

#include <gc_allocator.h>

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
				expression (mu::io::debugging::context context_a, std::vector <mu::io::ast::node *, gc_allocator <mu::io::ast::node *>> values);
				expression (mu::io::debugging::context context_a, std::vector <mu::io::ast::node *, gc_allocator <mu::io::ast::node *>> values, std::vector <mu::io::ast::identifier *, gc_allocator <mu::io::ast::identifier *>> individual_names);
				expression (mu::io::debugging::context context_a, std::vector <mu::io::ast::node *, gc_allocator <mu::io::ast::node *>> values, std::vector <mu::io::ast::identifier *, gc_allocator <mu::io::ast::identifier *>> individual_names, mu::io::ast::identifier * full_name);
				std::wstring name () override;
				void operator () (mu::io::ast::visitor * visitor_a) override;
				std::vector <mu::io::ast::node *, gc_allocator <mu::io::ast::node *>> values;
				std::vector <mu::io::ast::identifier *, gc_allocator <mu::io::ast::identifier *>> individual_names;
				mu::io::ast::identifier * full_name;
			};
		}
	}
}
