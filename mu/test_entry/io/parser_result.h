#pragma once

#include <boost/shared_ptr.hpp>

#include <vector>

namespace mu
{
	namespace io
	{
		namespace ast
		{
			class cluster;
		}
	}
	namespace io_test
	{
		class parser_result
		{
		public:
			void operator () (mu::io::ast::cluster * result_a);
			std::vector <mu::io::ast::cluster *> results;
		};
	}
}