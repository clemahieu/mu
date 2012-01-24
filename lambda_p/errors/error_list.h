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
			std::vector <std::pair <boost::shared_ptr <lambda_p::errors::error>, lambda_p::context>> errors;
			void operator () (boost::shared_ptr <lambda_p::errors::error> error, lambda_p::context context_a) override;
			bool operator () () override;
		};
	}
}

