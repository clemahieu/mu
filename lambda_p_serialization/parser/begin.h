#pragma once

#include <lambda_p_serialization/parser/state.h>

#include <boost/function.hpp>

namespace lambda_p_serialization
{	
	namespace core
	{
		class routine;
	}
	namespace parser
	{
		class parser;
		class begin : public lambda_p_serialization::parser::state
		{
		public:
			begin (lambda_p_serialization::parser::parser & parser_a, boost::function <void (boost::shared_ptr <lambda_p::core::routine> routine)> target_a);
			void parse (lambda_p_serialization::tokens::token * token) override;
			lambda_p_serialization::parser::parser & parser;
			boost::function <void (boost::shared_ptr <lambda_p::core::routine> routine)> target;
		};
	}
}

