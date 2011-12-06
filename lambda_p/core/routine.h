#pragma once

#include <vector>
#include <map>

#include <lambda_p/binder/list.h>
#include <lambda_p/binder/node.h>

#include <boost/shared_ptr.hpp>

namespace lambda_p_test
{
	class parser_test_1;
}
namespace lambda_p_kernel
{
	class bind_procedure;
	namespace nodes
	{
		class data;
	}
}
namespace lambda_p
{
	namespace binder
	{
		class bind_procedure;
	}
	namespace serialization
	{
		template <typename> class simple;
	}
	namespace parser
	{
		class parser;
		class statement;
		class routine;
	}
	namespace errors
	{
		class error;
	}
	namespace core
	{
		class expression;
		class expression_leaf;
		class routine : public lambda_p::binder::node
		{
		public:
			routine (std::vector <lambda_p::core::expression_leaf *> & surface, lambda_p::core::expression * routine_expression);
			std::vector <lambda_p::core::expression_leaf *> surface;
			lambda_p::core::expression * routine_expression;
		};
	}
}
