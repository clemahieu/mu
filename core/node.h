#pragma once

#include <string>

namespace mu
{
	namespace core
	{
		class visitor;
		class node
		{
		public:
			virtual ~node ();
			virtual void operator () (mu::core::visitor * visitor_a);
			virtual std::wstring name ();
			virtual std::wstring debug ();
		};
	}
}