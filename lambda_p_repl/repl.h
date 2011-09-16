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
	class repl_quit;
	class repl
	{
	public:
		repl(void);
		~repl(void);
		void run ();
		void stop ();
		void reset ();
	private:
		void run_loop ();
		void iteration ();
		bool stop_m;
		::boost::shared_ptr < ::lambda_p_repl::repl_quit> quit;
	};
}

