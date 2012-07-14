#pragma once

#include <mu/core/node.h>

#include <map>
#include <vector>

#include <boost/shared_ptr.hpp>

namespace mu
{
	namespace script
	{
		namespace cluster
		{
			class node;
		}
	}
	namespace llvm_
	{
		namespace function
		{
			class node;
		}
		namespace cluster
		{
			class node : public mu::core::node
			{
			public:
				std::wstring name () override;
				std::map <std::wstring, mu::llvm_::function::node *> names;
				std::vector <mu::llvm_::function::node *> routines;
			};
		}
	}
}

