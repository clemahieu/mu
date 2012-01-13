#pragma once

#include <boost/shared_ptr.hpp>

#include <map>
#include <vector>

namespace lambda_p
{
	class call;
	class expression;
	class set;
}
namespace lambda_p_script
{
	class routine;
}
namespace lambda_p_script_io
{
	class routine;
	class generator
	{
	public:
		generator (std::vector <boost::shared_ptr <lambda_p::expression>> & expressions_a, boost::shared_ptr <lambda_p::set> parameters_a);
		boost::shared_ptr <lambda_p_script::routine> result;
		std::map <boost::shared_ptr <lambda_p::expression>, size_t> reservations;
	};
}

