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
		class node
		{
		public:
			node ();
			~node (void);
			virtual node_id node_type () const = 0;
			virtual ::std::wstring node_type_name () const = 0;
		};
	}
}
