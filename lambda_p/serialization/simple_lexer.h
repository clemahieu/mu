#include <lambda_p/core/routine.h>
#include <lambda_p/tokens/control.h>
#include <lambda_p/tokens/identifier.h>

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
				target (target_a)
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
				::std::wstring string;
				string.push_back (L';');
				bool done (false);
				while (!done)
				{
					switch (next_char)
					{
					case L' ':
					case L'\t':
					case L'\n':
					case L'\f':
					case L'\0':
						done = true;
						break;
					default:
						string.push_back (next_char);
						consume ();
						break;
					}
				}
				::lambda_p::tokens::control * control = new ::lambda_p::tokens::control (string);
				target (control);
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
						done = true;
						break;
					}
					consume ();
				}
			}
			void lex_manifest_data ()
			{

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
			wchar_t next_char;
			token_sink & target;
			stream_type & source;
		};
	}
}