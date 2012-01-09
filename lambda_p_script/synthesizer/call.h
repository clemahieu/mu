#pragma once

#include <lambda_p/visitor.h>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	class node;
}
namespace lambda_p_script
{
	namespace runtime
	{
		class call;
	}
	namespace synthesizer
	{
		class generator;
		class call : public lambda_p::visitor
		{
		public:
			call (lambda_p_script::synthesizer::generator & generator_a, boost::shared_ptr <lambda_p_script::runtime::call> call_a, boost::shared_ptr <lambda_p::node> node_a);
			void operator () (lambda_p::call * call_a) override;
			void operator () (lambda_p::parameters * parameters_a) override;
			void operator () (lambda_p::reference * reference_a) override;
			void operator () (lambda_p::node * node_a) override;
			boost::shared_ptr <lambda_p::node> node;
			boost::shared_ptr <lambda_p_script::runtime::call> call_m;
			lambda_p_script::synthesizer::generator & generator;
		};
	}
}

