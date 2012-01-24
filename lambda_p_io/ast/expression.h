#pragma once

#include <lambda_p_io/ast/node.h>

#include <vector>

#include <boost/shared_ptr.hpp>

namespace lambda_p_io
{
	namespace ast
	{
		class identifier;
		class expression : public lambda_p_io::ast::node
		{
		public:
			expression (lambda_p::context context_a, std::vector <boost::shared_ptr <lambda_p_io::ast::node>> values);
			expression (lambda_p::context context_a, std::vector <boost::shared_ptr <lambda_p_io::ast::node>> values, std::vector <boost::shared_ptr <lambda_p_io::ast::identifier>> individual_names);
			expression (lambda_p::context context_a, std::vector <boost::shared_ptr <lambda_p_io::ast::node>> values, std::vector <boost::shared_ptr <lambda_p_io::ast::identifier>> individual_names, boost::shared_ptr <lambda_p_io::ast::identifier> full_name);
			std::wstring name () override;
			void operator () (lambda_p_io::ast::visitor * visitor_a) override;
			std::vector <boost::shared_ptr <lambda_p_io::ast::node>> values;
			std::vector <boost::shared_ptr <lambda_p_io::ast::identifier>> individual_names;
			boost::shared_ptr <lambda_p_io::ast::identifier> full_name;
		};
	}
}

