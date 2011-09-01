#pragma once

#include <boost/shared_ptr.hpp>
#include <boost/iostreams/filtering_stream.hpp>

#include <vector>

#include <lambda_p/core/node.h>
#include <lambda_p/core/routine.h>

namespace lambda_p
{
	namespace core
	{
		class statement
		{
		public:
			statement (::lambda_p::core::routine & routine_a);
			~statement (void);
            ::lambda_p::core::routine & routine;
            size_t index;
            ::std::vector < ::lambda_p::core::node *> arguments;
            size_t results;
		};
	}
}
