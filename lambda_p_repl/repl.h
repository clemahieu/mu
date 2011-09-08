#pragma once

#include <lambda_p/serialization/parser/routine_vector.h>
#include <lambda_p/serialization/parser/simple_parser.h>
#include <lambda_p/serialization/lexer/simple_lexer.h>

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
		void run_loop ();
		void iteration ();
		void use_routine ();
		bool stop_m;
		::lambda_p::serialization::parser::routine_vector routines;
		::lambda_p::serialization::parser::simple_parser < ::lambda_p::serialization::parser::routine_vector> parser;
		::lambda_p::serialization::lexer::simple_lexer < ::lambda_p::serialization::parser::simple_parser < ::lambda_p::serialization::parser::routine_vector> > lexer;
	};
}

