#pragma once

#include <lambda_p/errors/error_target.h>

#include <boost/shared_ptr.hpp>

#include <vector>

namespace lambda_p
{
	namespace errors
	{
		class error;
		class error_list : public lambda_p::errors::error_target
		{
		public:
			std::vector <boost::shared_ptr <lambda_p::errors::error>> errors;
			void operator () (boost::shared_ptr <lambda_p::errors::error> error) override;
			bool operator () () override;
		};
	}
}

