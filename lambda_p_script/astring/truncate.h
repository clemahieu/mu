#pragma once

#include <lambda_p_script/fixed.h>

namespace lambda_p_script
{
	namespace astring
	{
		class truncate : public lambda_p_script::fixed
		{
		public:
			void operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results) override;
			size_t count () override;
		};
	}
}

