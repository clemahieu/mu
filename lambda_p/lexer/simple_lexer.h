#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

#include <stack>

namespace lambda_p
{
	namespace tokens
	{
		class token;
	}
	namespace lexer
	{
		class state;
		class simple_lexer
		{
		public:
			simple_lexer (::boost::function <void (::lambda_p::tokens::token *)> target_a);
			~simple_lexer ();
			void operator () (wchar_t character);
			void reset ();
			bool error ();
			void error_message (::std::wstring & target);
		private:
			void lex_internal (wchar_t character);
			void lex_error (wchar_t character);
			void lex_begin (wchar_t character);
			void lex_control (wchar_t character);
			void lex_multiline_comment (wchar_t character);
			void lex_singleline_comment (wchar_t character);
			void lex_manifest_data (wchar_t character);
			void lex_identifier (wchar_t character);
			void pop_state ();
			::boost::function <void (::lambda_p::tokens::token *)> target;
		public:
			::std::stack < ::lambda_p::lexer::state *> state;
		};
	}
}