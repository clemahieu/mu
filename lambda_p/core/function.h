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
		class function
		{
		public:
			function (void);
			~function (void);
			::std::string name;
			::std::vector <::lambda_p::core::node> input;
			::std::vector <::lambda_p::core::node> output;
			::std::vector <::lambda_p::core::node> internal_m;
			::lambda_p::core::body body;
		};
	}
}
