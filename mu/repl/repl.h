#pragma once

#include <boost/shared_ptr.hpp>

namespace mu
{
	namespace core
	{
		namespace errors
		{
			class error_list;
		}
	}
	namespace repl
	{
		class repl_quit;
		class repl
		{
		public:
			repl ();
			void run ();
			void stop ();
			void reset ();
		private:
			void run_loop ();
			void iteration ();
			bool stop_m;
		};
	}
}

