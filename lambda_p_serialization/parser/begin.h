#pragma once

#include <lambda_p/parser/state.h>

#include <boost/function.hpp>

namespace lambda_p
{	
	namespace core
	{
		class routine;
	}
	namespace parser
	{
		class parser;
		class begin : public state
		{
		public:
			begin (lambda_p::parser::parser & parser_a, boost::function <void (boost::shared_ptr <lambda_p::core::routine> routine)> target_a);
			void parse (lambda_p::tokens::token * token) override;
			lambda_p::parser::parser & parser;
			boost::function <void (boost::shared_ptr <lambda_p::core::routine> routine)> target;
		};
	}
}

