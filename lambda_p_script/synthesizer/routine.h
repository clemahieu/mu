#pragma once

#include <boost/shared_ptr.hpp>

#include <map>
#include <list>

namespace lambda_p
{
	class routine;
	class call;
}
namespace lambda_p_script
{
	namespace runtime
	{
		class routine;
	}
	namespace synthesizer
	{
		class synthesizer;
		class expression;
		class routine
		{
		public:
			routine (lambda_p_script::synthesizer::synthesizer & synthesizer_a, boost::shared_ptr <lambda_p::routine> routine_a);
			boost::shared_ptr <lambda_p_script::runtime::routine> result;
			void operator () ( boost::shared_ptr <lambda_p::call> call);
			void operator () (boost::shared_ptr <lambda_p::call> dominator, boost::shared_ptr <lambda_p::call> follower);
			void synthesize (boost::shared_ptr <lambda_p::call> call_a);
			std::map <boost::shared_ptr <lambda_p::call>, std::list <boost::shared_ptr <lambda_p::call>>::iterator> synthesis;
			std::list <boost::shared_ptr <lambda_p::call>> expressions;
			size_t open;
			std::map <boost::shared_ptr <lambda_p::call>, size_t> reservation;
		};
	}
}

