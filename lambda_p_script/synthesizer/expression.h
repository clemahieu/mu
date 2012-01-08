#pragma once

#include <lambda_p/visitor.h>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	class call;
}
namespace lambda_p_script
{
	namespace synthesizer
	{
		class routine;
		class order;
		class expression : public lambda_p::visitor
		{
		public:
			expression (lambda_p_script::synthesizer::routine & routine_a, boost::shared_ptr <lambda_p::call> call_a);
			lambda_p_script::synthesizer::routine & routine;
			boost::shared_ptr <lambda_p::node> current;
			boost::shared_ptr <lambda_p::call> call;
			void operator () (lambda_p::call * call_a) override;
			void operator () (lambda_p::parameters * parameters_a) override;
			void operator () (lambda_p::reference * reference_a) override;
			void operator () (lambda_p::node * node_a) override;
		};
	}
}

