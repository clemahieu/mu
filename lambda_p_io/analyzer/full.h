#pragma once

#include <lambda_p_io/analyzer/declaration.h>

namespace lambda_p
{
	class tee;
}
namespace lambda_p_io
{
	namespace analyzer
	{
		class full : public lambda_p_io::analyzer::declaration
		{
		public:
			full (boost::shared_ptr <lambda_p::tee> tee_a);
			void operator () (boost::shared_ptr <lambda_p::target> target_a) override;
			boost::shared_ptr <lambda_p::tee> tee;
		};
	}
}

