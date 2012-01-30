#pragma once

#include <lambda_p/node.h>

#include <map>
#include <vector>

#include <boost/shared_ptr.hpp>

namespace lambda_p_llvm
{
	namespace function_pointer
	{
		class node;
	}
	class cluster : public lambda_p::node
	{
	public:
		std::map <std::wstring, size_t> names;
		std::vector <boost::shared_ptr <lambda_p_llvm::function_pointer::node>> routines;
	};
}

