#pragma once

#include <lambda_p/target.h>

namespace lambda_p
{
	class expression;
	class adapter : public lambda_p::target
	{
	public:
		void operator () (std::vector <boost::shared_ptr <lambda_p::node>> & arguments) override;
		boost::shared_ptr <lambda_p::expression> node;
		boost::shared_ptr <lambda_p::target> target;
	};
}

