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
	class routine;
	namespace synthesizer
	{
		class order;
		class synthesizer;
		class expression;
		class routine
		{
		public:
			routine (lambda_p_script::synthesizer::synthesizer & synthesizer_a, boost::shared_ptr <lambda_p::routine> routine_a);
			boost::shared_ptr <lambda_p_script::routine> result;
			void operator () (boost::shared_ptr <lambda_p_script::synthesizer::order> expression, boost::shared_ptr <lambda_p::call> call);
			void operator () (boost::shared_ptr <lambda_p::call> dominator, boost::shared_ptr <lambda_p::call> follower);
			std::map <boost::shared_ptr <lambda_p::call>, std::list <boost::shared_ptr <lambda_p_script::synthesizer::order>>::iterator> synthesis;
			std::list <boost::shared_ptr <lambda_p_script::synthesizer::order>> expressions;
			size_t open;
			std::map <boost::shared_ptr <lambda_p::call>, size_t> reservation;
		};
	}
}

