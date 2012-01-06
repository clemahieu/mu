#pragma once

#include <boost/function.hpp>

namespace lambda_p
{
	class expression;
}
namespace lambda_p_script
{
	class routine;
	class synthesizer
	{
	public:
		synthesizer (boost::function <void (boost::shared_ptr <lambda_p_script::routine>)> target_a);
		void operator () (boost::shared_ptr <lambda_p::expression> expression_a);
		boost::function <void (boost::shared_ptr <lambda_p_script::routine>)> target;
	};

}
