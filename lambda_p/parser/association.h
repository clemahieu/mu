#pragma once

#include <lambda_p/parser/state.h>
#include <lambda_p/parser/data_target.h>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	namespace parser
	{
		class routine;
		class association_target;
		class parser;
		class association : public lambda_p::parser::state, public data_target
		{
		public:
			association (lambda_p::parser::parser & parser_a, lambda_p::parser::routine & routine_a, lambda_p::parser::association_target & target_a);
			void parse (lambda_p::tokens::token * token) override;
			boost::function <void (size_t)> sink_data () override;
			bool on_results;
			lambda_p::parser::routine & routine;
			lambda_p::parser::association_target &target;
			lambda_p::parser::parser & parser;
		private:
		};
	}
}

