#pragma once

#include <boost/iostreams/stream.hpp>
#include <boost/shared_ptr.hpp>

#include <lambda_p/core/function.h>
#include <lambda_p/core/body.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/node.h>

namespace lambda_p
{
	namespace serialization
	{
		class simple
		{
		public:
			simple (void);
			~simple (void);
			void function (::lambda_p::core::function *function_a);
			void body (::lambda_p::core::body *body_a);
			void statement (::lambda_p::core::statement *statement_a);
			void node (::lambda_p::core::node *node_a);
			::boost::shared_ptr <::boost::iostreams::filtering_ostream> target;
		};
	}
}
