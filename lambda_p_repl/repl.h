#pragma once

#include <boost/shared_ptr.hpp>

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
	};
}

