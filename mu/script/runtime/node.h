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
		namespace runtime
		{
			class frame;
			class node
			{
			public:
                virtual ~node();
				virtual void operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::script::runtime::frame & frame, std::vector <boost::shared_ptr <mu::core::node>> & target) = 0;
			};
		}
	}
}

