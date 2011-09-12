#pragma once

#include <lambda_p/binder/node_instance.h>

namespace lambda_p_repl
{
	class hello_world : public ::lambda_p::binder::node_instance
	{
	public:
		hello_world(void);
		~hello_world(void);
		void operator () ();
	};
}

