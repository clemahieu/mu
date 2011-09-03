#include <lambda_p/core/routine.h>
#include <lambda_p/tokens/identifier.h>
#include <lambda_p/tokens/error.h>
#include <lambda_p/tokens/routine_end.h>
#include <lambda_p/tokens/statement_end.h>
#include <lambda_p/tokens/declaration.h>
#include <lambda_p/tokens/dereference.h>
#include <lambda_p/tokens/hex_data_token.h>
#include <lambda_p/tokens/data_token.h>
#include <lambda_p/tokens/complex_identifier.h>

#include <boost/circular_buffer.hpp>

namespace lambda_p
{
	namespace serialization
	{
		template <typename stream_type, typename token_sink>
		class simple_lexer
		{
		public:
			simple_lexer (stream_type & source_a, token_sink & target_a)
				: source (source_a),
				target (target_a),
                next_char (L';'),
				lex_error (false)
			{

			}
			~simple_lexer ()
			{
			}
			void lex ()
			{
				lex_all ();
			}
		private:
			void lex_all ()
			{
				peek ();
				while (next_char != L'\0')
				{
					switch (next_char)
					{
					case L' ':
					case L'\t':
					case L'\n':
					case L'\f':
						lex_whitespace ();
						break;
					case L';':
						lex_control ();
						break;
					default:
						lex_identifier ();
						break;
					}
				}
			}
			void lex_whitespace ()
			{
				bool done (false);
				while (!done)
				{
					switch (next_char)
					{
					case L' ':
					case L'\t':
					case L'\n':
					case L'\f':
						consume ();
						break;
					case L'\0':
					default:
						done = true;
						break;
					}
				}				
			}
			void lex_control ()
			{
				consume ();
				switch (next_char)
				{
				case L'*':
					lex_multiline_comment ();
					break;
				case L'/':
					lex_single_line_comment ();
					break;
				case L'"':
					lex_manifest_data ();
					break;
				default:
					lex_control_token ();
					break;
				}
			}
			void lex_control_token ()
			{
                switch (next_char)
                {
                case L'#':
                    {
                        consume ();
                        ::lambda_p::tokens::hex_data_token * token = new ::lambda_p::tokens::hex_data_token;
                        target (token);
                    }
                    break;
                case L'\'':
                    {
                        consume ();
                        ::lambda_p::tokens::data_token * token = new ::lambda_p::tokens::data_token;
                        target (token);
                    }
                    break;
                case L'.':
                    {
                        consume ();
                        ::lambda_p::tokens::routine_end * token = new ::lambda_p::tokens::routine_end;
                        target (token);
                    }
                    break;
                case L'!':
                    {
                        consume ();
                        ::lambda_p::tokens::declaration * token = new ::lambda_p::tokens::declaration;
                        target (token);
                    }
                    break;
                case L';':
                    {
                        consume ();
                        ::lambda_p::tokens::statement_end * token = new ::lambda_p::tokens::statement_end;
                        target (token);
                    }
                    break;
                default:
                    {
                        ::std::wstring message;
                        message.append (L"Unknown token: ");
                        message.push_back (';');
                        message.push_back (next_char);
                        ::lambda_p::tokens::error * error = new ::lambda_p::tokens::error (message);
                        target (error);
                        next_char = L'\0';
                    }
                    break;
                }
			}
			void lex_multiline_comment ()
			{
				bool done (false);
				consume ();
				while (!done)
				{
					switch (next_char)
					{
					case L';':
						consume ();
						switch (next_char)
						{
						case L'*':
							done = true;
							break;
						default:
							break;
						}
						break;
					case L'\0':
						{
							::std::wstring message;
							message.append (L"End of file in the middle of a multi-line comment");
							::lambda_p::tokens::error * error = new ::lambda_p::tokens::error (message);
							target (error);
							done = true;
						}
						break;
					default:
						break;
					}
					consume ();
				}
			}
			void lex_single_line_comment ()
			{
				bool done (false);
				consume ();
				while (!done)
				{
					switch (next_char)
					{
					case L'\n':
					case L'\f':
					case L'\0':
						done = true;
						break;
					}
					consume ();
				}
			}
			void lex_manifest_data ()
			{
                consume ();
                ::std::wstring end_token;
                bool done (false);
				bool has_end_token (false);
                while (!done)
                {
                    switch (next_char)
                    {
                        case ';':
							consume ();
							has_end_token = true;
                        case '\0':
                            done = true;
                            break;
                        default:
                            end_token.push_back (next_char);
                            consume ();
                            break;
                    }
                }
				if (has_end_token)
				{
					::std::wstring data;
					::boost::circular_buffer <wchar_t> last_characters;
					bool matched (match (last_characters, end_token));
					while (!matched && next_char != '\0')
					{
						last_characters.push_back (next_char);
						data.push_back (next_char);
						consume ();
					}
					if (matched)
					{
						data.resize (data.size () - end_token.size ());
						::lambda_p::tokens::complex_identifier * token = new ::lambda_p::tokens::complex_identifier (data, end_token);
						target (token);
					}
					else
					{
						::std::wstring message;
						message.append (L"Manifest data did not end before end of stream");
						::lambda_p::tokens::error * error = new ::lambda_p::tokens::error (message);
						target (error);
					}
				}
				else
				{
					::std::wstring message;
					message.append (L"Manifest data end token not complete before end of file");
					::lambda_p::tokens::error * error = new ::lambda_p::tokens::error (message);
					target (error);
				}
			}
            bool match (::boost::circular_buffer <wchar_t> & last_characters, ::std::wstring & end_token)
            {
                bool result (true);
                ::boost::circular_buffer <wchar_t>::const_iterator i = last_characters.begin ();
                ::std::wstring::const_iterator j = end_token.begin ();
                while (result && i != last_characters.end () && j != end_token.end ())
                {
                    ++i;
                    ++j;
                }
                return result;
            }
			void lex_identifier ()
			{				
				::std::wstring string;
				bool done (false);
				while (!done)
				{
					switch (next_char)
					{
					case L' ':
					case L'\t':
					case L'\n':
					case L'\f':
					case L';':
					case L'\0':
						done = true;
						break;
					default:
						string.push_back (next_char);
						consume ();
						break;
					}
				}
				::lambda_p::tokens::identifier * identifier = new ::lambda_p::tokens::identifier (string);
				target (identifier);
			}
			void peek ()
			{
				next_char = source.peek ();
				if (source.eof ())
				{
					next_char = L'\0';
				}
			}
			void consume ()
			{
				source.get ();
				peek ();
			}
			bool lex_error;
			wchar_t next_char;
			token_sink & target;
			stream_type & source;
		};
	}
}