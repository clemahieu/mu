#pragma once

#include <lambda_p_script/nodes/operation.h>

namespace lambda_p_script
{
	namespace nodes
	{
		class fixed : public lambda_p_script::nodes::operation
		{
		public:
			void operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, std::vector <boost::shared_ptr <lambda_p::node>> & parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results) override;
			virtual void perform (boost::shared_ptr <lambda_p::errors::error_target> errors_a, std::vector <boost::shared_ptr <lambda_p::node>> & parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results) = 0;
			virtual size_t count () = 0;
		};
	}
}

