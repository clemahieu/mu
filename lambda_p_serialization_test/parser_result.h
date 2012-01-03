#pragma once

#include <boost/shared_ptr.hpp>

#include <vector>

namespace lambda_p_serialization
{
	namespace ast
	{
		class expression;
	}
}
namespace lambda_p_serialization_test
{
	class parser_result
	{
	public:
		void operator () (boost::shared_ptr <lambda_p_serialization::ast::expression> result_a);
		std::vector <boost::shared_ptr <lambda_p_serialization::ast::expression>> results;
	};
}

