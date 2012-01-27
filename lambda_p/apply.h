#pragma once

#include <boost/shared_ptr.hpp>

#include <vector>

namespace lambda_p
{
	class node;
	namespace apply
	{
		void merge (std::vector <boost::shared_ptr <lambda_p::node>> & target, std::vector <boost::shared_ptr <lambda_p::node>> & source);
	}
}
