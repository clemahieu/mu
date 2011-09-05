#include <lambda_p/core/routine.h>
#include <lambda_p/tokens/identifier.h>
#include <lambda_p/tokens/error.h>
#include <lambda_p/tokens/routine_end.h>
#include <lambda_p/tokens/statement_end.h>
#include <lambda_p/tokens/declaration.h>
#include <lambda_p/tokens/hex_data_token.h>
#include <lambda_p/tokens/data_token.h>
#include <lambda_p/tokens/complex_identifier.h>

#include <lambda_p/serialization/lexer/state.h>
#include <lambda_p/serialization/lexer/begin.h>
#include <lambda_p/serialization/lexer/error_state.h>
#include <lambda_p/serialization/lexer/whitespace.h>
#include <lambda_p/serialization/lexer/control.h>
#include <lambda_p/serialization/lexer/identifier_state.h>
#include <lambda_p/serialization/lexer/multiline_comment.h>
#include <lambda_p/serialization/lexer/singleline_comment.h>
#include <lambda_p/serialization/lexer/manifest_data.h>

#include <boost/circular_buffer.hpp>
#include <boost/scoped_ptr.hpp>

#include <stack>

namespace lambda_p
{
	namespace serialization
	{
		namespace lexer
		{
			template <typename token_sink>
			class simple_lexer
			{
			public:
				simple_lexer (token_sink & target_a)
					: target (target_a)
				{
					state.push (new ::lambda_p::serialization::lexer::begin);
				}
				~simple_lexer ()
				{
				}
				void operator () (wchar_t character)
				{
					lex_internal (character);
				}
				void end ()
				{
					state_id state_l (state.top ()->state_type ());
					switch (state_l)
					{
					case ::lambda_p::serialization::lexer::state_error:
						break;
					case ::lambda_p::serialization::lexer::state_begin:
						break;
					case ::lambda_p::serialization::lexer::state_whitespace:
						pop_state ();
						end ();
						break;
					case ::lambda_p::serialization::lexer::state_control:
						{
							::std::wstring message (L"End of stream in the middle of control_token");
							state.push (new ::lambda_p::serialization::lexer::error_state (message));
						}
						break;
					case ::lambda_p::serialization::lexer::state_identifier:
						{							
							::lambda_p::serialization::lexer::identifier_state * state_l (static_cast < ::lambda_p::serialization::lexer::identifier_state *> (state.top ()));
							::lambda_p::tokens::identifier * identifier = new ::lambda_p::tokens::identifier (state_l->string);
							target (identifier);
							pop_state ();
							end ();
						}
						break;
					case ::lambda_p::serialization::lexer::state_multiline_comment:
						{
							::std::wstring message (L"End of stream in the middle of multiline comment");
							state.push (new ::lambda_p::serialization::lexer::error_state (message));
						}
						break;
					case ::lambda_p::serialization::lexer::state_singleline_comment:
						pop_state ();
						end ();
						break;
					case ::lambda_p::serialization::lexer::state_manifest_data:
						{
							::std::wstring message (L"End of stream in the middle of manifest data");
							state.push (new ::lambda_p::serialization::lexer::error_state (message));
						}
						break;
					default:
						assert (false);
					}
				}
				void reset ()
				{
					while (!state.empty ())
					{
						pop_state ();
					}
					state.push (new ::lambda_p::serialization::lexer::begin);
				}
				bool error ()
				{
					bool result (state.top ()->state_type () == ::lambda_p::serialization::lexer::state_error);
					return result;
				}
			private:
				void lex_internal (wchar_t character)
				{
					state_id state_l (state.top ()->state_type ());
					switch (state_l)
					{
					case ::lambda_p::serialization::lexer::state_error:
						lex_error (character);
						break;
					case ::lambda_p::serialization::lexer::state_begin:
						lex_begin (character);
						break;
					case ::lambda_p::serialization::lexer::state_whitespace:
						lex_whitespace (character);
						break;
					case ::lambda_p::serialization::lexer::state_control:
						lex_control (character);
						break;
					case ::lambda_p::serialization::lexer::state_identifier:
						lex_identifier (character);
						break;
					case ::lambda_p::serialization::lexer::state_multiline_comment:
						lex_multiline_comment (character);
						break;
					case ::lambda_p::serialization::lexer::state_singleline_comment:
						lex_singleline_comment (character);
						break;
					case ::lambda_p::serialization::lexer::state_manifest_data:
						lex_manifest_data (character);
						break;
					default:
						assert (false);
					}
				}
				void lex_error (wchar_t character)
				{
					// Do nothing, remain in error state
				}
				void lex_begin (wchar_t character)
				{
					switch (character)
					{
					case L' ':
					case L'\t':
					case L'\n':
					case L'\f':
					case L'\0':
						state.push (new ::lambda_p::serialization::lexer::whitespace);
						lex_whitespace (character);
						break;
					case L';':
						state.push (new ::lambda_p::serialization::lexer::control);
						break;
					default:
						state.push (new ::lambda_p::serialization::lexer::identifier_state);
						lex_identifier (character);
						break;
					}
				}
				void lex_whitespace (wchar_t character)
				{
					switch (character)
					{
					case L' ':
					case L'\t':
					case L'\n':
					case L'\f':
					case L'\0':
						// Eat whitespace
						break;
					default:
						pop_state ();
						lex_internal (character);
						break;
					}			
				}
				void lex_control (wchar_t character)
				{
					::lambda_p::serialization::lexer::control * state_l (static_cast < ::lambda_p::serialization::lexer::control *> (state.top ()));
					if (!state_l->complete)
					{
						switch (character)
						{
						case L'*':
							pop_state ();
							state.push (new ::lambda_p::serialization::lexer::multiline_comment);
							break;
						case L'/':
							pop_state ();
							state.push (new ::lambda_p::serialization::lexer::singleline_comment);
							break;
						case L'"':
							pop_state ();
							state.push (new ::lambda_p::serialization::lexer::manifest_data);
							break;
						case L'#':
							{
								state_l->complete = true;
								::lambda_p::tokens::hex_data_token * token = new ::lambda_p::tokens::hex_data_token;
								target (token);
							}
							break;
						case L'\'':
							{
								state_l->complete = true;
								::lambda_p::tokens::data_token * token = new ::lambda_p::tokens::data_token;
								target (token);
							}
							break;
						case L'.':
							{
								state_l->complete = true;
								::lambda_p::tokens::routine_end * token = new ::lambda_p::tokens::routine_end;
								target (token);
							}
							break;
						case L'!':
							{
								state_l->complete = true;
								::lambda_p::tokens::declaration * token = new ::lambda_p::tokens::declaration;
								target (token);
							}
							break;
						case L';':
							{
								state_l->complete = true;
								::lambda_p::tokens::statement_end * token = new ::lambda_p::tokens::statement_end;
								target (token);
							}
							break;
						case L' ':
						case L'\t':
						case L'\n':
						case L'\f':
						case L'\0':						
							pop_state ();
							break;
						default:
							::std::wstring message (L"Unknown token: ;");
							message.push_back (character);
							state.push (new ::lambda_p::serialization::lexer::error_state (message));
							break;
						}
					}
					else
					{
						::std::wstring message (L"Expecting whitespace after control_token");
						state.push (new ::lambda_p::serialization::lexer::error_state (message));	
					}
				}
				void lex_multiline_comment (wchar_t character)
				{
					::lambda_p::serialization::lexer::multiline_comment * state_l (static_cast < ::lambda_p::serialization::lexer::multiline_comment *> (state.top ()));
					if (state_l->have_semicolon)
					{
						switch (character)
						{
						case L'*':
							pop_state ();
							break;
						case L';':
							// Remain in have_semicolon state
							break;
						default:
							state_l->have_semicolon = false;
							break;
						}
					}
					else
					{
						// Eat comments
					}
				}
				void lex_singleline_comment (wchar_t character)
				{
					::lambda_p::serialization::lexer::singleline_comment * state_l (static_cast < ::lambda_p::serialization::lexer::singleline_comment *> (state.top ()));
					switch (character)
					{
					case L'\n':
					case L'\f':
						pop_state ();
						break;
					}
				}
				void lex_manifest_data (wchar_t character)
				{
					::lambda_p::serialization::lexer::manifest_data * state_l (static_cast < ::lambda_p::serialization::lexer::manifest_data *> (state.top ()));
					if (!state_l->have_end_token)
					{
						switch (character)
						{
						case L';':
							state_l->have_end_token = true;
							break;
						default:
							state_l->end_token.push_back (character);
							break;
						}
					}
					else
					{
						state_l->last_characters.push_back (character);
						state_l->data.push_back (character);
						if (state_l->match ())
						{
							state_l->data.resize (state_l->data.size () - state_l->end_token.size ());
							::lambda_p::tokens::complex_identifier * token (new ::lambda_p::tokens::complex_identifier (state_l->data, state_l->end_token));
							target (token);
							pop_state ();
						}
					}
				}
				void lex_identifier (wchar_t character)
				{				
					::lambda_p::serialization::lexer::identifier_state * state_l (static_cast < ::lambda_p::serialization::lexer::identifier_state *> (state.top ()));
					switch (character)
					{
					case L' ':
					case L'\t':
					case L'\n':
					case L'\f':
					case L';':
					case L'\0':
						{
							::lambda_p::tokens::identifier * identifier = new ::lambda_p::tokens::identifier (state_l->string);
							target (identifier);
							pop_state ();
						}
						break;
					default:
						state_l->string.push_back (character);
						break;
					}
				}
				void pop_state ()
				{
					delete state.top ();
					state.pop ();
				}
				::std::stack < ::lambda_p::serialization::lexer::state *> state;
				token_sink & target;
			};
		}
	}
}