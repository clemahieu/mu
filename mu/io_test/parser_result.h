#pragma once

#include <boost/shared_ptr.hpp>

#include <vector>

namespace mu
{
	namespace io
	{
		namespace ast
		{
			class node;
		}
	}
	namespace io_test
	{
		class parser_result
		{
		public:
			void operator () (boost::shared_ptr <mu::io::ast::node> result_a);
			std::vector <boost::shared_ptr <mu::io::ast::node>> results;
		};
	}
}