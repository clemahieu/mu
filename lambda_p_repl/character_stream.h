#pragma once

#include <lambda_p/binder/instance.h>

namespace lambda_p_repl
{
	class character_stream : public ::lambda_p::binder::instance
	{
	public:
		virtual wchar_t operator () () = 0;
	};
}

