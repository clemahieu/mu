#pragma once

#include <lambda_p/target.h>

namespace lambda_p
{
	class gather;
	class connection : public lambda_p::target
	{
	public:
		connection (boost::shared_ptr <lambda_p::gather> gather_a, size_t number_a);
		void operator () (std::vector <boost::shared_ptr <lambda_p::node>> & arguments) override;
		boost::shared_ptr <lambda_p::gather> gather;
		size_t number;
	};
}

