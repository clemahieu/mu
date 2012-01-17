#pragma once

#include <lambda_p/visitor.h>

#include <vector>

namespace lambda_p_test
{
	class test_visitor : public lambda_p::visitor
	{
	public:
		void operator () (lambda_p::expression * expression_a) override;
		void operator () (lambda_p::reference * reference_a) override;
		void operator () (lambda_p::routine * routine_a) override;
		void operator () (lambda_p::node * node_a) override;
		std::vector <lambda_p::expression *> expressions;
		std::vector <lambda_p::reference *> references;
		std::vector <lambda_p::routine *> routines;
		std::vector <lambda_p::node *> nodes;
	};
}

