#pragma once

#include <lambda_p_script/operation.h>

namespace lambda_p_script
{
	namespace package
	{
		class get_recursive : public lambda_p_script::operation
		{
		public:
			void perform (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results) override;
			std::wstring name ();
		};
	}
}

