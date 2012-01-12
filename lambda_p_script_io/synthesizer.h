#pragma once

#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	class node;
	class routine;
	namespace errors
	{
		class error_target;
	}
}
namespace lambda_p_script
{
	class routine;
}
namespace lambda_p_script_io
{
	class synthesizer
	{
	public:
		synthesizer (boost::function <void (boost::shared_ptr <lambda_p_script::routine>)> target_a);
		void operator () (boost::shared_ptr <lambda_p::routine> expression_a);
		boost::function <void (boost::shared_ptr <lambda_p_script::routine>)> target;
	};
}
