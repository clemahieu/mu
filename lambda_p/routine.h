#pragma once

#include <lambda_p/node.h>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	class expression;
	class routine : public lambda_p::node
	{
	public:
		routine ();
		void operator () (lambda_p::visitor * visitor_a) override;
		boost::shared_ptr <lambda_p::expression> parameters;
		boost::shared_ptr <lambda_p::expression> body;
	};
}

