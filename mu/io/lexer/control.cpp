#include <mu/io/lexer/control.h>

#include <mu/core/errors/error_target.h>
#include <mu/io/lexer/lexer.h>
#include <mu/io/lexer/multiline_comment.h>
#include <mu/io/lexer/singleline_comment.h>
#include <mu/io/lexer/error.h>
#include <mu/io/tokens/parameters.h>
#include <mu/io/lexer/hex_code.h>
#include <mu/io/lexer/identifier.h>

#include <gc_cpp.h>

mu::io::lexer::control::control (mu::io::lexer::lexer & lexer_a, mu::io::debugging::position first_a)
	: first (first_a),
	lexer (lexer_a)
{
}

void mu::io::lexer::control::lex (char32_t character)
{
	if (character != L'\uffff')
	{
		switch (character)
		{
		case U'~':
			lexer.target (new (GC) mu::io::tokens::parameters, mu::io::debugging::context (first, lexer.position));
			lexer.state.pop ();
			break;
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
            identifier->add (L'{');
        }
            break;
        case U'}':
        {
            lexer.state.pop ();
            auto identifier (new (GC) mu::io::lexer::identifier (lexer, first));
            lexer.state.push (identifier);
            identifier->add (L'}');
        }
            break;
        case U'[':
        {
            lexer.state.pop ();
            auto identifier (new (GC) mu::io::lexer::identifier (lexer, first));
            lexer.state.push (identifier);
            identifier->add (L'[');
        }
            break;
        case U']':
        {
            lexer.state.pop ();
            auto identifier (new (GC) mu::io::lexer::identifier (lexer, first));
            lexer.state.push (identifier);
            identifier->add (L']');
        }
            break;
        case U':':
        {
            lexer.state.pop ();
            auto identifier (new (GC) mu::io::lexer::identifier (lexer, first));
            lexer.state.push (identifier);
            identifier->add (L':');
        }
            break;
        case U';':
        {
            lexer.state.pop ();
            auto identifier (new (GC) mu::io::lexer::identifier (lexer, first));
            lexer.state.push (identifier);
            identifier->add (L';');
        }
            break;
		case U'a':
			{
				lexer.state.pop ();
				auto identifier (new (GC) mu::io::lexer::identifier (lexer, first));
				lexer.state.push (identifier);
				identifier->lex (L':');
				identifier->lex (L'a');
			}
			break;
        case U' ':
        {
            lexer.state.pop ();
            auto identifier (new (GC) mu::io::lexer::identifier (lexer, first));
            lexer.state.push (identifier);
            identifier->add (L' ');
        }
            break;
        case U'\0':
        {
            lexer.state.pop ();
            auto identifier (new (GC) mu::io::lexer::identifier (lexer, first));
            lexer.state.push (identifier);
            identifier->add (L'\0');
        }
            break;
        case U'\t':
        {
            lexer.state.pop ();
            auto identifier (new (GC) mu::io::lexer::identifier (lexer, first));
            lexer.state.push (identifier);
            identifier->add (L'\t');
        }
            break;
        case U'\f':
        {
            lexer.state.pop ();
            auto identifier (new (GC) mu::io::lexer::identifier (lexer, first));
            lexer.state.push (identifier);
            identifier->add (L'\f');
        }
            break;
        case U'\r':
        {
            lexer.state.pop ();
            auto identifier (new (GC) mu::io::lexer::identifier (lexer, first));
            lexer.state.push (identifier);
            identifier->add (L'\r');
        }
            break;
		case U'u':
			{
				lexer.state.pop ();
				auto identifier (new (GC) mu::io::lexer::identifier (lexer, first));
				lexer.state.push (identifier);
				identifier->lex (L':');
				identifier->lex (L'u');
			}
			break;
		default:
			mu::string message (U"Unknown token: :");
			message.push_back (character);
			(*lexer.errors) (message);
			lexer.state.push (new (GC) mu::io::lexer::error);
			break;
		}
	}
	else
	{
		mu::string message (U"End of stream when parsing control character");
		(*lexer.errors) (message);
		lexer.state.push (new (GC) mu::io::lexer::error);
	}
}