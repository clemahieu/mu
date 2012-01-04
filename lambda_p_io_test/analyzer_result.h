#pragma once

#include <vector>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	namespace core
	{
		class routine;
	}
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
		void operator () (boost::shared_ptr <lambda_p::core::routine> routine_a);
		std::vector <boost::shared_ptr <lambda_p::core::routine>> routines;
		boost::shared_ptr <lambda_p::errors::error_list> errors;
	};
}

