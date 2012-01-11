#pragma once

#include <lambda_p_script/nodes/fixed.h>

namespace lambda_p_script
{
	namespace operations
	{
		namespace closure
		{
			class closure : public lambda_p_script::nodes::fixed
			{
			public:
				closure (size_t count_a, boost::shared_ptr <lambda_p_script::nodes::operation> operation_a);
				closure (std::vector <size_t> & open_a, std::vector <boost::shared_ptr <lambda_p::node>> & closed_a);
				void operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, std::vector <boost::shared_ptr <lambda_p::node>> & parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results) override;
				size_t count () override;
				std::wstring name () override;
				std::vector <size_t> open;
				std::vector <boost::shared_ptr <lambda_p::node>> closed;
			};
		}
	}
}

