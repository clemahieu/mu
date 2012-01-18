#pragma once

#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

#include <stack>

namespace lambda_p
{
	namespace errors
	{
		class error_target;
	}
}
namespace lambda_p_io
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
			friend class lambda_p_io::lexer::begin;
			friend class lambda_p_io::lexer::complex_identifier;
			friend class lambda_p_io::lexer::identifier;
			friend class lambda_p_io::lexer::multiline_comment;
			friend class lambda_p_io::lexer::singleline_comment;
			friend class lambda_p_io::lexer::control;
		public:
			lexer (boost::shared_ptr <lambda_p::errors::error_target> errors_a, boost::function <void (lambda_p_io::tokens::token *)> target_a);
			void operator () (wchar_t character);
			void reset ();
			boost::shared_ptr <lambda_p::errors::error_target> errors;
			boost::function <void (lambda_p_io::tokens::token *)> target;
			std::stack <boost::shared_ptr <lambda_p_io::lexer::state>> state;
		};
	}
}