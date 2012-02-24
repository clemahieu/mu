#pragma once

#include <mu/core/node.h>

#include <map>
#include <vector>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	class routine;
}
namespace lambda_p_script
{
	namespace cluster
	{
		class node;
	}
}
namespace lambda_p_llvm
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
			void set_names (boost::shared_ptr <lambda_p_script::cluster::node> cluster_a, std::map <boost::shared_ptr <mu::core::node>, boost::shared_ptr <mu::core::node>> & remap_a);
			std::wstring name () override;
			std::map <std::wstring, boost::shared_ptr <lambda_p_llvm::function::node>> names;
			std::vector <boost::shared_ptr <lambda_p_llvm::function::node>> routines;
		};
	}
}

