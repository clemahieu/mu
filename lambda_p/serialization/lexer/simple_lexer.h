#include <lambda_p/core/routine.h>
#include <lambda_p/tokens/identifier.h>
#include <lambda_p/tokens/routine_end.h>
#include <lambda_p/tokens/statement_end.h>
#include <lambda_p/tokens/declaration.h>
#include <lambda_p/tokens/hex_data_token.h>
#include <lambda_p/tokens/data_token.h>
#include <lambda_p/tokens/complex_identifier.h>

#include <lambda_p/serialization/lexer/state.h>
#include <lambda_p/serialization/lexer/begin.h>
#include <lambda_p/serialization/lexer/error.h>
#include <lambda_p/serialization/lexer/whitespace.h>
#include <lambda_p/serialization/lexer/control.h>
#include <lambda_p/serialization/lexer/identifier.h>
#include <lambda_p/serialization/lexer/multiline_comment.h>
#include <lambda_p/serialization/lexer/singleline_comment.h>
#include <lambda_p/serialization/lexer/manifest_data.h>

#include <boost/circular_buffer.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/function.hpp>

#include <stack>

namespace lambda_p
{
	namespace serialization
	{
		namespace lexer
		{
			class simple_lexer
			{
			public:
				simple_lexer (::boost::function <void (::lambda_p::tokens::token *)> & target_a);
				~simple_lexer ();
				void operator () (wchar_t character);
				void end ();
				void reset ();
				bool error ();
				void error_message (::std::wstring & target);
			private:
				void lex_internal (wchar_t character);
				void lex_error (wchar_t character);
				void lex_begin (wchar_t character);
				void lex_whitespace (wchar_t character);
				void lex_control (wchar_t character);
				void lex_multiline_comment (wchar_t character);
				void lex_singleline_comment (wchar_t character);
				void lex_manifest_data (wchar_t character);
				void lex_identifier (wchar_t character);
				void pop_state ();
				::boost::function <void (::lambda_p::tokens::token *)> target;
			public:
				::std::stack < ::lambda_p::serialization::lexer::state *> state;
			};
		}
	}
}