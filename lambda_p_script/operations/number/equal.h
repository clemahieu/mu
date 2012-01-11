#pragma once

#include <lambda_p_script/nodes/fixed.h>

namespace lambda_p_script
{
	namespace operations
	{
		namespace number
		{
			class equal : public lambda_p_script::nodes::fixed
			{
			public:
				void operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, std::vector <boost::shared_ptr <lambda_p::node>> & parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results) override;
				std::wstring name () override;
				size_t count () override;
			};
		}
	}
}
