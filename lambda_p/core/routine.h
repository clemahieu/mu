#pragma once

#include <boost/shared_ptr.hpp>

#include <vector>
#include <string>

#include <lambda_p/core/node.h>
#include <lambda_p/core/statement.h>

namespace lambda_p
{
	namespace core
	{
		class routine
		{
		public:
			routine ();
			~routine (void);
			size_t parameters;
			size_t statements;
		};
	}
}
