#pragma once

#include <vector>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	class expression;
	namespace errors
	{
		class error_list;
	}
}
namespace lambda_p_io_test
{
	class analyzer_result
	{
	public:
		analyzer_result ();
		void operator () (boost::shared_ptr <lambda_p::expression> routine_a);
		std::vector <boost::shared_ptr <lambda_p::expression>> routines;
		boost::shared_ptr <lambda_p::errors::error_list> errors;
	};
}

