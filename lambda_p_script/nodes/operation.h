#pragma once

#include <boost/shared_ptr.hpp>

#include <vector>

namespace lambda_p
{
	class node;
}
namespace lambda_p_script
{
	namespace nodes
	{
		class operation
		{
		public:
			virtual void operator () (std::vector <boost::shared_ptr <lambda_p::node>> & parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results) = 0;
		};
	}
}

