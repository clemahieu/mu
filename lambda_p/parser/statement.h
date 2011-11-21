#pragma once

#include <lambda_p/parser/state.h>
#include <lambda_p/parser/association_target.h>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	namespace core
	{
		class statement;
		class routine;
	}
	namespace parser
	{
		class routine;
		class body;
		class parser;
		class statement : public state, public lambda_p::parser::association_target
		{
		public:
			statement (lambda_p::parser::parser & parser_a, lambda_p::parser::routine & routine_a);
			void parse (lambda_p::tokens::token * token) override;
			boost::function <void (size_t)> sink_declaration () override;
			boost::function <void (size_t)> sink_argument () override ;
			bool have_target;
			bool on_results;
			lambda_p::parser::routine & routine;
			lambda_p::core::statement * statement_m;
			lambda_p::parser::parser & parser;
		};
	}
}

