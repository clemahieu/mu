#include <lambda_p/parser/begin.h>

#include <lambda_p/tokens/token.h>
#include <lambda_p/parser/routine.h>
#include <lambda_p/parser/parser.h>
#include <lambda_p/parser/error.h>

lambda_p::parser::begin::begin (lambda_p::parser::parser & parser_a, boost::function <void (boost::shared_ptr <lambda_p::core::routine> routine)> target_a)
	: parser (parser_a),
	target (target_a)
{
}

void lambda_p::parser::begin::parse (lambda_p::tokens::token * token)
{
	lambda_p::tokens::token_ids token_id (token->token_id ());
	switch (token_id)
	{
        case lambda_p::tokens::token_id_identifier:
        case lambda_p::tokens::token_id_complex_identifier:
		case lambda_p::tokens::token_id_divider:
        {
            boost::shared_ptr <lambda_p::parser::state> new_state (new lambda_p::parser::routine (parser, target));
            parser.state.push (new_state);
            parser (token);
        }
        break;
	case lambda_p::tokens::token_id_stream_end:
		parser.state.pop ();
		break;
	default:
        {
            std::wstring message (L"At top level, expecting identifier or end of stream");
            parser.state.push (boost::shared_ptr < lambda_p::parser::state> (new lambda_p::parser::error (message)));
        }
		break;
	}
}