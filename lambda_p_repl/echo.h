#pragma once

#include <lambda_p/binder/node_instance.h>

#include <string>

namespace lambda_p_repl
{
	class echo : public ::lambda_p::binder::node_instance
	{
	public:
		echo(::std::wstring string_a);
		~echo(void);
		void operator () ();
		::std::wstring string;
	};
}

