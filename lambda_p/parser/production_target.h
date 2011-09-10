#pragma once

#include <boost/shared_ptr.hpp>

#include <lambda_p/parser/reference_identifiers.h>

namespace lambda_p
{
	namespace core
	{
		class reference;
	}
	namespace tokens
	{
		class identifier;
	}
	namespace parser
	{
		class simple_parser;
		class production_target
		{
		public:
			virtual void sink_reference (::lambda_p::parser::simple_parser & parser, ::lambda_p::parser::reference_identifiers reference);
			virtual void sink_data (::lambda_p::parser::simple_parser & parser, ::lambda_p::tokens::identifier * identifier);
			virtual void sink_declaration (::lambda_p::parser::simple_parser & parser, ::lambda_p::tokens::identifier * identifier);
		};
	}
}

