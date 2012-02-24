#pragma once

#include <lambda_p_script/operation.h>

namespace lambda_p_script
{
	namespace closure
	{
		class single : public lambda_p_script::operation
		{
		public:
			single (boost::shared_ptr <lambda_p_script::operation> operation_a);
			single (std::vector <boost::shared_ptr <mu::core::node>> & closed_a, boost::shared_ptr <lambda_p_script::operation> operation_a);
			void perform (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results) override;
			std::wstring name () override;
			boost::shared_ptr <lambda_p_script::operation> operation_m;
			std::vector <boost::shared_ptr <mu::core::node>> closed;
		};
	}
}

