#pragma once

#include <mu/core/visitor.h>

#include <vector>

namespace lambda_p_test
{
	class test_visitor : public mu::core::visitor
	{
	public:
		void operator () (mu::core::expression * expression_a) override;
		void operator () (mu::core::parameters * parameters_a) override;
		void operator () (mu::core::reference * reference_a) override;
		void operator () (mu::core::node * node_a) override;
		void operator () (mu::core::routine * routine_a) override;
		std::vector <mu::core::expression *> expressions;
		std::vector <mu::core::parameters *> parameters;
		std::vector <mu::core::reference *> references;
		std::vector <mu::core::node *> nodes;
		std::vector <mu::core::routine *> routines;
	};
}

