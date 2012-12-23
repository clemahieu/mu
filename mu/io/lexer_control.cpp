#include <mu/io/lexer_control.h>

#include <mu/core/errors/error_target.h>
#include <mu/io/lexer_lexer.h>
#include <mu/io/lexer_multiline_comment.h>
#include <mu/io/lexer_singleline_comment.h>
#include <mu/io/lexer_error.h>
#include <mu/io/lexer_hex_code.h>
#include <mu/io/lexer_identifier.h>
#include <mu/io/lexer_context.h>

#include <gc_cpp.h>

mu::io::lexer::control::control (mu::io::lexer::lexer & lexer_a, mu::io::position first_a):
first (first_a),
lexer (lexer_a)
{
}

void mu::io::lexer::control::lex (boost::circular_buffer <mu::io::lexer::context> & context_a)
{
	assert (context_a.size () >= 1);
	switch (context_a [0].character)
	{
	case U'(':
		lexer.state.pop ();
		lexer.state.push (new (GC) mu::io::lexer::multiline_comment (lexer));
		break;
	case U'-':
		lexer.state.pop ();
		lexer.state.push (new (GC) mu::io::lexer::singleline_comment (lexer));
			break;
	case U'{':
	{
		lexer.state.pop ();
		auto identifier (new (GC) mu::io::lexer::identifier (lexer, first));
		lexer.state.push (identifier);
		identifier->add (mu::io::lexer::context (context_a [0].position, U'{'));
	}
		break;
	case U'}':
	{
		lexer.state.pop ();
		auto identifier (new (GC) mu::io::lexer::identifier (lexer, first));
		lexer.state.push (identifier);
		identifier->add (mu::io::lexer::context (context_a [0].position, U'}'));
	}
		break;
	case U'[':
	{
		lexer.state.pop ();
		auto identifier (new (GC) mu::io::lexer::identifier (lexer, first));
		lexer.state.push (identifier);
		identifier->add (mu::io::lexer::context (context_a [0].position, U'['));
	}
		break;
	case U']':
	{
		lexer.state.pop ();
		auto identifier (new (GC) mu::io::lexer::identifier (lexer, first));
		lexer.state.push (identifier);
		identifier->add (mu::io::lexer::context (context_a [0].position, U']'));
	}
		break;
	case U':':
	{
		lexer.state.pop ();
		auto identifier (new (GC) mu::io::lexer::identifier (lexer, first));
		lexer.state.push (identifier);
		identifier->add (mu::io::lexer::context (context_a [0].position, U':'));
	}
		break;
	case U';':
	{
		lexer.state.pop ();
		auto identifier (new (GC) mu::io::lexer::identifier (lexer, first));
		lexer.state.push (identifier);
		identifier->add (mu::io::lexer::context (context_a [0].position, U';'));
	}
		break;
	case U'a':
		{
			lexer.state.pop ();
			auto identifier (new (GC) mu::io::lexer::identifier (lexer, first));
			lexer.state.push (identifier);
			mu::io::lexer::context context;
			context.character = U':';
			context.position = first;
			identifier->lex (context);
			identifier->lex (context_a);
		}
		break;
	case U' ':
	{
		lexer.state.pop ();
		auto identifier (new (GC) mu::io::lexer::identifier (lexer, first));
		lexer.state.push (identifier);
		identifier->add (mu::io::lexer::context (context_a [0].position, U' '));
	}
		break;
	case U'\0':
	{
		lexer.state.pop ();
		auto identifier (new (GC) mu::io::lexer::identifier (lexer, first));
		lexer.state.push (identifier);
		identifier->add (mu::io::lexer::context (context_a [0].position, U'\0'));
	}
		break;
	case U'\t':
	{
		lexer.state.pop ();
		auto identifier (new (GC) mu::io::lexer::identifier (lexer, first));
		lexer.state.push (identifier);
		identifier->add (mu::io::lexer::context (context_a [0].position, U'\t'));
	}
		break;
	case U'\f':
	{
		lexer.state.pop ();
		auto identifier (new (GC) mu::io::lexer::identifier (lexer, first));
		lexer.state.push (identifier);
		identifier->add (mu::io::lexer::context (context_a [0].position, U'\f'));
	}
		break;
	case U'\r':
	{
		lexer.state.pop ();
		auto identifier (new (GC) mu::io::lexer::identifier (lexer, first));
		lexer.state.push (identifier);
		identifier->add (mu::io::lexer::context (context_a [0].position, U'\r'));
	}
		break;
	case U'u':
		{
			lexer.state.pop ();
			auto identifier (new (GC) mu::io::lexer::identifier (lexer, first));
			lexer.state.push (identifier);
			mu::io::lexer::context context;
			context.character = U':';
		break;
	case U'\U0000FFFF':
		mu::string message (U"End of stream when parsing control character");
		lexer.errors (message);
		lexer.state.push (new (GC) mu::io::lexer::error);

	default:
		mu::string message (U"Unknown token: :");
		message.push_back (context_a [0].character);
		lexer.errors (message);
		lexer.state.push (new (GC) mu::io::lexer::error);
		break;
	}
}