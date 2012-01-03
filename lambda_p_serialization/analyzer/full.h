#pragma once

#include <lambda_p_serialization/analyzer/declaration.h>

namespace lambda_p
{
	namespace core
	{
		class tee;
	}
}
namespace lambda_p_serialization
{
	namespace analyzer
	{
		class full : public lambda_p_serialization::analyzer::declaration
		{
		public:
			full (boost::shared_ptr <lambda_p::core::tee> tee_a);
			void operator () (boost::shared_ptr <lambda_p::core::target> target_a) override;
			boost::shared_ptr <lambda_p::core::tee> tee;
		};
	}
}

