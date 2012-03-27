#pragma once

#include <mu/io/debugging/context.h>
#include <mu/io/source.h>

#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

#include <cryptopp/sha.h>

#include <stack>

namespace mu
{
	namespace core
	{
		namespace errors
		{
			class error_target;
		}
	}
	namespace io
	{
		namespace debugging
		{
			class stream;
		}
		namespace tokens
		{
			class token;
		}
		namespace lexer
		{
			class state;
			class begin;
			class complex_identifier;
			class identifier;
			class multiline_comment;
			class singleline_comment;
			class control;
			class error;
			class lexer : mu::io::source
			{
				friend class mu::io::lexer::begin;
				friend class mu::io::lexer::complex_identifier;
				friend class mu::io::lexer::identifier;
				friend class mu::io::lexer::multiline_comment;
				friend class mu::io::lexer::singleline_comment;
				friend class mu::io::lexer::control;
			public:
				using mu::io::source::operator ();
				lexer (boost::shared_ptr <mu::core::errors::error_target> errors_a, boost::function <void (mu::io::tokens::token *, mu::io::debugging::context)> target_a, boost::shared_ptr <mu::io::debugging::stream> stream_a);
				void operator () (wchar_t char_a) override;
				void reset ();
				mu::io::debugging::position position;
				CryptoPP::SHA256 hash;
				boost::shared_ptr <mu::io::debugging::stream> stream;
				boost::shared_ptr <mu::core::errors::error_target> errors;
				boost::function <void (mu::io::tokens::token *, mu::io::debugging::context)> target;
				std::stack <boost::shared_ptr <mu::io::lexer::state>> state;
			};
		}
	}
}