#pragma once

namespace lambda_p
{
	class visitor;
	class node
	{
	public:
		virtual ~node ();
		virtual void operator () (lambda_p::visitor * visitor_a);
	};
}
