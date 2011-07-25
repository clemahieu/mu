#pragma once

#include <boost/shared_ptr.hpp>
#include <boost/iostreams/filtering_stream.hpp>

#include <vector>

#include <lambda_p/core/node.h>

namespace lambda_p
{
	namespace core
	{
		class statement
		{
		public:
			statement (void);
			~statement (void);
			::std::string name;
			::boost::shared_ptr <::lambda_p::core::node*> target;
			::std::vector <::lambda_p::core::node*> input;
			::std::vector <::lambda_p::core::node*> output;
		};
	}
}
