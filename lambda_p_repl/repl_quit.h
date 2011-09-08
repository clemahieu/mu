#pragma once

#include <string>
#include <lambda_p/binder/node_instance.h>

namespace lambda_p
{
	namespace core
	{
		class routine;
	}
}
namespace lambda_p_repl
{
	class repl;
	class repl_quit : public ::lambda_p::binder::node_instance
	{
	public:
		repl_quit (::lambda_p_repl::repl & repl_a);
		~repl_quit (void);
		void operator () ();
		::lambda_p_repl::repl & repl;
	};
}

