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
			void print_errors (boost::shared_ptr <mu::core::errors::error_list> errors_a);
			void run_loop ();
			void iteration ();
			bool stop_m;
		};
	}
}

