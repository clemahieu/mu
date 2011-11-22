#pragma once

#include <lambda_p/parser/state.h>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	namespace parser
	{
		class routine;
		class association_target;
		class parser;
		class association : public lambda_p::parser::state
		{
		public:
			association (lambda_p::parser::parser & parser_a, lambda_p::parser::routine & routine_a, lambda_p::parser::association_target & target_a);
			void parse (lambda_p::tokens::token * token) override;
			bool on_results;
			lambda_p::parser::routine & routine;
			lambda_p::parser::association_target &target;
			lambda_p::parser::parser & parser;
		private:
		};
	}
}

