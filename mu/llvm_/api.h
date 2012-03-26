#pragma once

#include <boost/shared_ptr.hpp>

#include <map>

namespace mu
{
	namespace script
	{
		namespace extensions
		{
			class node;
		}
		namespace values
		{
			class operation;
		}
	}
	namespace llvm_
	{
		namespace api
		{
			void binding (mu::script::extensions::node *& result_a, mu::script::values::operation *& context_a);
		};
	}
}

