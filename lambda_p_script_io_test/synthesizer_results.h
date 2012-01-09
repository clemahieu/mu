#pragma once

#include <boost/shared_ptr.hpp>

#include <vector>

namespace lambda_p_script
{
	class routine;
}
namespace lambda_p_script_test
{
	class synthesizer_results
	{
	public:
		void operator () (boost::shared_ptr <lambda_p_script::routine> routine_a);
		std::vector <boost::shared_ptr <lambda_p_script::routine>> routines;
	};
}

