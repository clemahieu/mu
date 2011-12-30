#pragma once

#include <lambda_p_serialization/ast/node.h>

#include <vector>

#include <boost/shared_ptr.hpp>

namespace lambda_p_serialization
{
	namespace ast
	{
		class expression : public lambda_p_serialization::ast::node
		{
		public:
			std::wstring name () override;
			void operator () (lambda_p_serialization::ast::visitor * visitor_a) override;
			std::vector <boost::shared_ptr <lambda_p_serialization::ast::node>> values;
			std::vector <std::wstring> individual_names;
			std::wstring full_name;
		};
	}
}

