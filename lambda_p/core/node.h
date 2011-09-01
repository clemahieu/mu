#pragma once

#include <iostream>

namespace lambda_p
{
	namespace core
	{
		class node
		{
		public:
			node ();
			~node (void);
            virtual void validate (::std::iostream & problems) = 0;
		};
	}
}
