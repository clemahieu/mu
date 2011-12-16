#pragma once

#include <lambda_p_serialization/parser/state.h>
#include <lambda_p_serialization/parser/signature_state.h>

#include <vector>
#include <string>

namespace lambda_p_serialization
{
	namespace parser
	{
		class parser;
		class signature_sink;
		class signature : public lambda_p_serialization::parser::state
		{
		public:
			signature (lambda_p_serialization::parser::parser & parser_a, lambda_p_serialization::parser::signature_sink & sink_a);
			void parse (lambda_p_serialization::tokens::token * token) override;
			std::vector <std::wstring> local_names;
			std::wstring full_name;
			lambda_p_serialization::parser::signature_state state;
			lambda_p_serialization::parser::parser & parser;
			lambda_p_serialization::parser::signature_sink & sink;
		};
	}
}

