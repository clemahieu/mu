#pragma once

#include <lambda_p_script/fixed.h>

namespace lambda_p_llvm_wrapper
{
	namespace module
	{
		class get_package : public lambda_p_script::fixed
		{
		public:
			void operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p_script::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results) override;
			size_t count () override;
			std::wstring name () override;
		};
	}
}

