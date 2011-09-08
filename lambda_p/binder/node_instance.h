#pragma once

namespace lambda_p
{
	namespace binder
	{
		class node_instance
		{
		public:
			node_instance(void);
			~node_instance(void);
			virtual void operator () () = 0;
		};
	}
}

