#pragma once

#include <mu/core/context.h>

#include <boost/shared_ptr.hpp>

#include <vector>

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
		class operation;
		namespace runtime
		{
			class frame;
			class node;
			class call
			{
			public:
				call (size_t results_a);
				size_t results;
				std::vector <boost::shared_ptr <mu::script::runtime::node>> arguments;
				void operator () (mu::script::context & context_a, mu::script::runtime::frame & frame_a);
			};
		}
	}
}
