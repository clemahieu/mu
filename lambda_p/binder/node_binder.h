#pragma once

#include <iostream>

namespace lambda_p
{
	namespace core
	{
		class statement;
	}
	namespace binder
	{
		class node_binder
		{
		public:
			node_binder(void);
			~node_binder(void);
			virtual void bind (::lambda_p::core::statement *) = 0;
			virtual void validate (::std::ostream & problems) = 0;
		};
	}
}

