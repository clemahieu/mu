#pragma once

#include <mu/core/node.h>
#include <mu/script/context.h>

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
		class operation : public mu::core::node
		{
		public:
			virtual void operator () (mu::script::context & context_a) = 0;
		};
	}
}
