#pragma once

#include <lambda_p/target.h>

namespace lambda_p
{
	class container : public lambda_p::target
	{
	public:
		void operator () (std::vector <boost::shared_ptr <lambda_p::node>> & arguments) override;
		std::vector <boost::shared_ptr <lambda_p::node>> results;
	};
}

