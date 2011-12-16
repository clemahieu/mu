#pragma once

#include <lambda_p_serialization/parser/reference.h>

namespace lambda_p
{
	namespace core
	{
		class scatter;
	}
}
namespace lambda_p_serialization
{
	namespace parser
	{
		class reference_scatter : public lambda_p_serialization::parser::reference
		{
		public:
			reference_scatter (boost::shared_ptr <lambda_p::core::scatter> scatter_a, size_t position_a);
			void operator () (boost::shared_ptr <lambda_p::core::target> target_a) override;			
			boost::shared_ptr <lambda_p::core::scatter> scatter;
			size_t position;
		};
	}
}

