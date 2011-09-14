#pragma once

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	namespace tokens
	{
		class token;
	}
	namespace core
	{
		class node;
		class routine;
	}
}
namespace lambda_p_repl
{
	class repl
	{
	public:
		repl(void);
		~repl(void);
		void run ();
		void stop ();
		void reset ();
	private:
		::lambda_p::core::node * quit_node ();
		::lambda_p::core::node * hello_node ();
		::lambda_p::core::node * echo_node ();
		::lambda_p::core::node * environment_node (::boost::shared_ptr < ::lambda_p::core::routine> routine);
		void run_loop ();
		void iteration ();
		void use_routine (::boost::shared_ptr < ::lambda_p::core::routine> routine);
		bool stop_m;
	};
}

