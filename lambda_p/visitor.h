#pragma once

namespace lambda_p
{
	class reference;
	class node;
	class routine;
	class expression;
	class visitor
	{
	public:
		virtual void operator () (lambda_p::expression * expression_a) = 0;
		virtual void operator () (lambda_p::reference * reference_a) = 0;
		virtual void operator () (lambda_p::routine * routine_a) = 0;
		virtual void operator () (lambda_p::node * node_a) = 0;
	};
}

