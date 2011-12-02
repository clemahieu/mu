#pragma once

#include <vector>
#include <map>

#include <lambda_p/core/expression.h>
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
		class routine : public lambda_p::binder::node
		{
			friend class lambda_p::core::statement;
			friend class lambda_p_kernel::nodes::data;
            template <typename> friend class lambda_p::serialization::simple;
			friend class lambda_p::parser::parser;
			friend class lambda_p_kernel::bind_procedure;
			friend class lambda_p::parser::statement;
			friend class lambda_p::parser::routine;
			friend class lambda_p_test::parser_test_1;
		public:
			boost::shared_ptr <lambda_p::core::expression> routine_expression;
		};
	}
}
