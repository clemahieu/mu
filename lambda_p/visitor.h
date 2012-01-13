#pragma once

namespace lambda_p
{
	class set;
	class call;
	class reference;
	class node;
	class visitor
	{
	public:
		virtual void operator () (lambda_p::set * set_a) = 0;
		virtual void operator () (lambda_p::call * call_a) = 0;
		virtual void operator () (lambda_p::reference * reference_a) = 0;
		virtual void operator () (lambda_p::node * node_a) = 0;
	};
}

