#pragma once

#include <lambda_p/parser/routine_vector.h>
#include <lambda_p/parser/simple_parser.h>
#include <lambda_p/lexer/simple_lexer.h>

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
		void run_loop ();
		void iteration ();
		void use_routine ();
		bool stop_m;
		void token_sink (::lambda_p::tokens::token *);
		::lambda_p::parser::routine_vector routines;
		::lambda_p::parser::simple_parser parser;
		::lambda_p::lexer::simple_lexer lexer;
	};
}

