#pragma once

#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

#include <stack>

namespace lambda_p_serialization
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
			friend class lambda_p::lexer::begin;
			friend class lambda_p::lexer::complex_identifier;
			friend class lambda_p::lexer::identifier;
			friend class lambda_p::lexer::multiline_comment;
			friend class lambda_p::lexer::singleline_comment;
			friend class lambda_p::lexer::control;
		public:
			lexer (boost::function <void (lambda_p::tokens::token *)> target_a);
			~lexer ();
			void operator () (wchar_t character);
			void reset ();
			boost::shared_ptr <lambda_p::lexer::error> error ();
		private:
			boost::function <void (lambda_p::tokens::token *)> target;
		public:
			std::stack <boost::shared_ptr <lambda_p::lexer::state>> state;
		};
	}
}