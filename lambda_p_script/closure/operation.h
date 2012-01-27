#pragma once

#include <lambda_p_script/fixed.h>

namespace lambda_p_script
{
	namespace closure
	{
		class operation : public lambda_p_script::fixed
		{
		public:
			operation (size_t count_a, boost::shared_ptr <lambda_p_script::operation> operation_a);
			operation (boost::shared_ptr <lambda_p_script::operation> operation_a, std::vector <size_t> & open_a, std::vector <boost::shared_ptr <lambda_p::node>> & closed_a);
			void operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results) override;
			size_t count () override;
			std::wstring name () override;
			boost::shared_ptr <lambda_p_script::operation> operation_m;
			std::vector <size_t> open;
			std::vector <boost::shared_ptr <lambda_p::node>> closed;
		};
	}
}

