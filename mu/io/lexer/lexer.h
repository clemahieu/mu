#pragma once

#include <mu/core/context.h>

#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

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
			class lexer
			{
				friend class mu::io::lexer::begin;
				friend class mu::io::lexer::complex_identifier;
				friend class mu::io::lexer::identifier;
				friend class mu::io::lexer::multiline_comment;
				friend class mu::io::lexer::singleline_comment;
				friend class mu::io::lexer::control;
			public:
				lexer (boost::shared_ptr <mu::core::errors::error_target> errors_a, boost::function <void (mu::io::tokens::token *, mu::core::context)> target_a);
				void operator () (wchar_t character);
				void reset ();
				mu::core::position position;
				boost::shared_ptr <mu::core::errors::error_target> errors;
				boost::function <void (mu::io::tokens::token *, mu::core::context)> target;
				std::stack <boost::shared_ptr <mu::io::lexer::state>> state;
			};
		}
	}
}