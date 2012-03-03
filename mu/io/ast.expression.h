#pragma once

#include <mu/io/ast.node.h>

#include <vector>

#include <boost/shared_ptr.hpp>

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
				expression (mu::core::context context_a, std::vector <boost::shared_ptr <mu::io::ast::node>> values);
				expression (mu::core::context context_a, std::vector <boost::shared_ptr <mu::io::ast::node>> values, std::vector <boost::shared_ptr <mu::io::ast::identifier>> individual_names);
				expression (mu::core::context context_a, std::vector <boost::shared_ptr <mu::io::ast::node>> values, std::vector <boost::shared_ptr <mu::io::ast::identifier>> individual_names, boost::shared_ptr <mu::io::ast::identifier> full_name);
				std::wstring name () override;
				void operator () (mu::io::ast::visitor * visitor_a) override;
				std::vector <boost::shared_ptr <mu::io::ast::node>> values;
				std::vector <boost::shared_ptr <mu::io::ast::identifier>> individual_names;
				boost::shared_ptr <mu::io::ast::identifier> full_name;
			};
		}
	}
}
