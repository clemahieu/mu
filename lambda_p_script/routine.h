#pragma once

#include <lambda_p_script/operation.h>

#include <boost/shared_ptr.hpp>

#include <vector>

namespace lambda_p_script
{
	class routine : public lambda_p_script::operation
	{
	public:
		routine (size_t count_a);
		size_t count;
		std::vector <boost::shared_ptr <lambda_p_script::operation>> body;
		void operator () (std::vector <boost::shared_ptr <lambda_p::node>> & context, size_t base) override;
	};
}

