#pragma once

#include <lambda_p_serialization/parser/reference.h>

namespace lambda_p
{
	namespace core
	{
		class tee;
	}
}
namespace lambda_p_serialization
{
	namespace parser
	{
		class reference_tee : public lambda_p_serialization::parser::reference
		{
		public:
			reference_tee (boost::shared_ptr <lambda_p::core::tee> tee_a);
			void operator () (boost::shared_ptr <lambda_p::core::target> target_a) override;
			boost::shared_ptr <lambda_p::core::tee> tee;
			size_t position;
		};
	}
}

