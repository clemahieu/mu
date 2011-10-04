#pragma once

#include <iostream>

namespace lambda_p
{
	namespace core
	{
		enum node_id
		{
			node_data,
			node_declaration,
			node_reference
		};
		class routine;
		::std::wstring node_name (node_id);
		class node
		{
		public:
			node ();
			~node (void);
			virtual node_id node_type () const = 0;
		};
	}
}
