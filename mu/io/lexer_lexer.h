#pragma once

#include <mu/io/context.h>

#include <boost/function.hpp>
#include <boost/circular_buffer.hpp>

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
            class context;
			class lexer
			{
				friend class mu::io::lexer::begin;
				friend class mu::io::lexer::complex_identifier;
				friend class mu::io::lexer::identifier;
				friend class mu::io::lexer::multiline_comment;
				friend class mu::io::lexer::singleline_comment;
				friend class mu::io::lexer::control;
			public:
				lexer (mu::core::errors::error_target & errors_a, boost::function <void (mu::io::tokens::token const &)> target_a);
				void operator () (boost::circular_buffer <mu::io::lexer::context> & context_a);
				void reset ();
				mu::core::errors::error_target & errors;
				boost::function <void (mu::io::tokens::token const &)> target;
				mu::stack <mu::io::lexer::state *> state;
			};
		}
	}
}