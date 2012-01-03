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
		class error;
	}
}
namespace lambda_p_serialization_test
{
	class analyzer_result
	{
	public:
		void operator () (boost::shared_ptr <lambda_p::core::routine> routine_a);
		void operator () (boost::shared_ptr <lambda_p::errors::error> error_a);
		std::vector <boost::shared_ptr <lambda_p::core::routine>> routines;
		std::vector <boost::shared_ptr <lambda_p::errors::error>> errors;
	};
}

