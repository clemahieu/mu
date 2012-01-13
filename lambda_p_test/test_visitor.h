#pragma once

#include <lambda_p/visitor.h>

#include <vector>

namespace lambda_p_test
{
	class test_visitor : public lambda_p::visitor
	{
	public:
		void operator () (lambda_p::set * set_a) override;
		void operator () (lambda_p::call * call_a) override;
		void operator () (lambda_p::reference * reference_a) override;
		void operator () (lambda_p::node * node_a) override;
		std::vector <lambda_p::set *> sets;
		std::vector <lambda_p::call *> calls;
		std::vector <lambda_p::reference *> references;
		std::vector <lambda_p::node *> nodes;
	};
}

