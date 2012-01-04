#pragma once

#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

#include <stack>

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
			lexer (boost::function <void (lambda_p_io::tokens::token *)> target_a);
			~lexer ();
			void operator () (wchar_t character);
			void reset ();
			boost::shared_ptr <lambda_p_io::lexer::error> error ();
		private:
			boost::function <void (lambda_p_io::tokens::token *)> target;
		public:
			std::stack <boost::shared_ptr <lambda_p_io::lexer::state>> state;
		};
	}
}