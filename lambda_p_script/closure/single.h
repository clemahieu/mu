#pragma once

#include <lambda_p_script/operation.h>

namespace lambda_p_script
{
	namespace closure
	{
		class single : public lambda_p_script::operation
		{
		public:
			single (std::vector <boost::shared_ptr <lambda_p::node>> & closed_a, boost::shared_ptr <lambda_p_script::operation> operation_a);
			void perform (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p_script::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results) override;
			std::wstring name () override;
			boost::shared_ptr <lambda_p_script::operation> operation_m;
			std::vector <boost::shared_ptr <lambda_p::node>> closed;
		};
	}
}

