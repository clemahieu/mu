#pragma once

#include <lambda_p/target.h>

#include <boost/shared_ptr.hpp>

#include <vector>

namespace lambda_p
{
	class target;
	class expression;
	class connection;
	class gather
	{
	public:
		gather (boost::shared_ptr <lambda_p::target> target_a);
		void operator () (std::vector <boost::shared_ptr <lambda_p::node>> & arguments, size_t sequence);
		boost::shared_ptr <lambda_p::connection> operator () (boost::shared_ptr <lambda_p::gather> self_a);
	private:
		std::vector <std::vector <boost::shared_ptr <lambda_p::node>>> arguments;
		boost::shared_ptr <lambda_p::target> target;
		size_t remaining;
	};
}

