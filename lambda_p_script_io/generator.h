#pragma once

#include <boost/shared_ptr.hpp>

#include <map>

namespace lambda_p
{
	class call;
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
		generator (lambda_p_script_io::routine & routine_a);
		boost::shared_ptr <lambda_p_script::routine> result;
		std::map <boost::shared_ptr <lambda_p::call>, size_t> reservations;
	};
}

