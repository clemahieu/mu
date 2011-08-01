#pragma once

#include <boost/shared_ptr.hpp>

#include <vector>
#include <string>

#include <lambda_p/core/node.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/body.h>

namespace lambda_p
{
	namespace core
	{
		class routine
		{
		public:
			routine (::std::string name_a);
			~routine (void);
			::std::string name;
			::std::vector < ::boost::shared_ptr < ::lambda_p::core::node> > surface;
			::boost::shared_ptr < ::lambda_p::core::body> body;
		};
	}
}
