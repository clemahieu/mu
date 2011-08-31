#pragma once

#include <boost/shared_ptr.hpp>
#include <boost/iostreams/filtering_stream.hpp>

#include <vector>

#include <lambda_p/core/node.h>
#include <lambda_p/core/identifier.h>

namespace lambda_p
{
	namespace core
	{
		class statement
		{
		public:
			statement (::lambda_p::core::identifier * declaration_a, ::lambda_p::core::identifier * target_a);
			~statement (void);
			::lambda_p::core::identifier * declaration;
			::lambda_p::core::identifier * target;
			::std::vector < ::lambda_p::core::node *> arguments;
		};
	}
}
