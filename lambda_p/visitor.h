#pragma once

namespace lambda_p
{
	class reference;
	class node;
	class link;
	class expression;
	class parameters;
	class visitor
	{
	public:
		virtual void operator () (lambda_p::expression * expression_a) = 0;
		virtual void operator () (lambda_p::parameters * parameters_a) = 0;
		virtual void operator () (lambda_p::reference * reference_a) = 0;
		virtual void operator () (lambda_p::link * link_a) = 0;
		virtual void operator () (lambda_p::node * node_a) = 0;
	};
}

