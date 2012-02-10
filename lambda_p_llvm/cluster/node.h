#pragma once

#include <lambda_p/node.h>

#include <map>
#include <vector>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	class routine;
}
namespace lambda_p_llvm
{
	namespace value
	{
		class node;
	}
	namespace cluster
	{
		class node : public lambda_p::node
		{
		public:
			void set_names (std::map <std::wstring, boost::shared_ptr <lambda_p::routine>> & names_a, std::map <boost::shared_ptr <lambda_p::node>, boost::shared_ptr <lambda_p::node>> & remap_a);
			std::map <std::wstring, boost::shared_ptr <lambda_p_llvm::value::node>> names;
			std::vector <boost::shared_ptr <lambda_p_llvm::value::node>> routines;
		};
	}
}

