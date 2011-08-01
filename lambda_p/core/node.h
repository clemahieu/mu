#pragma once

#include <string>

namespace lambda_p
{
	namespace core
	{
		class node
		{
		public:
			node (::std::string name_a);
			~node (void);
			::std::string name;
		};
	}
}
