#pragma once

#include <boost/shared_ptr.hpp>

#include <map>
#include <list>

namespace lambda_p
{
	class expression;
}
namespace lambda_p_script
{
	namespace synthesizer
	{
		class expression;
		class synthesizer;
		class routine
		{
		public:
			routine (lambda_p_script::synthesizer::synthesizer & synthesizer_a, boost::shared_ptr <lambda_p::expression> expression_a);
			boost::shared_ptr <lambda_p_script::routine> result;
			void operator () (boost::shared_ptr <lambda_p::expression> dominator, boost::shared_ptr <lambda_p::expression> new_expression_a);
			std::map <boost::shared_ptr <lambda_p::expression>, std::list <boost::shared_ptr <lambda_p_script::synthesizer::call>>::value_type> synthesis;
			std::list <boost::shared_ptr <lambda_p_script::synthesizer::call>> calls;
		};
	}
}

