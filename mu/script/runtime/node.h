#pragma once

#include <vector>

#include <boost/shared_ptr.hpp>

namespace mu
{
	namespace core
	{
		class node;
		namespace errors
		{
			class error_target;
		}
	}
	namespace script
	{
		class context;
		class node
		{
		public:
			virtual void operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::script::context & context, std::vector <boost::shared_ptr <mu::core::node>> & target) = 0;
		};
	}
}

