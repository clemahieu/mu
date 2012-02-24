#pragma once

#include <lambda_p_script/fixed.h>

namespace lambda_p_script
{
	namespace values
	{
		class operation : public lambda_p_script::fixed
		{
		public:
			operation ();
			operation (std::vector <boost::shared_ptr <mu::core::node>> values_a);
			void operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results) override;
			size_t count () override;
			std::vector <boost::shared_ptr <mu::core::node>> values;
		};
	}
}

