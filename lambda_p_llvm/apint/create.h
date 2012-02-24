#pragma once

#include <lambda_p_script/fixed.h>

namespace lambda_p_llvm
{
	namespace apint
	{
		class create : public lambda_p_script::fixed
		{
		public:
			void operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results) override;
			size_t count () override;
		};
	}
}

