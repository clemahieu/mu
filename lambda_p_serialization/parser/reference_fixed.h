#pragma once

#include <lambda_p_serialization/parser/reference.h>

#include <vector>

namespace lambda_p
{
	namespace core
	{
		class expression;
		class entry;
	}
}
namespace lambda_p_serialization
{
	namespace parser
	{
		class reference_fixed : public lambda_p_serialization::parser::reference
		{
		public:
			reference_fixed (boost::shared_ptr <lambda_p::core::entry> entry_a, std::vector <boost::shared_ptr <lambda_p::core::expression>> expressions_a);
			void operator () (boost::shared_ptr <lambda_p::core::target> target_a) override;
			std::vector <boost::shared_ptr <lambda_p::core::expression>> expressions;
			boost::shared_ptr <lambda_p::core::entry> entry;
		};
	}
}

