#pragma once

#include <lambda_p/binder/node.h>

namespace lambda_p_repl
{
	class character_stream : public lambda_p::binder::node
	{
	public:
		virtual wchar_t operator () () = 0;
	};
}

