#pragma once

#include <string>

namespace lambda_p
{
	class visitor;
	class node
	{
	public:
		virtual ~node ();
		virtual void operator () (lambda_p::visitor * visitor_a);
		virtual std::wstring name ();
		virtual std::wstring debug ();
	};
}
