#pragma once

#include <lambda_p/node.h>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	class set;
	class reference : public lambda_p::node
	{
	public:
		void operator () (lambda_p::visitor * visitor_a) override;
		boost::shared_ptr <lambda_p::set> set;
		size_t index;
	};
}

