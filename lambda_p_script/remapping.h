#pragma once

#include <map>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	class routine;
	class node;
}
namespace lambda_p_script
{
	class routine;
	class remapping
	{
	public:
		void remap (std::map <boost::shared_ptr <lambda_p::node>, boost::shared_ptr <lambda_p::node>> & remap_a);
		std::map <boost::shared_ptr <lambda_p::routine>, boost::shared_ptr <lambda_p::node>> generated;
	};
}

