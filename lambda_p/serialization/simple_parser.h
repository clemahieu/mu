#include <lambda_p/core/routine.h>
#include <lambda_p/tokens/whitespace.h>
#include <lambda_p/tokens/control.h>
#include <lambda_p/tokens/identifier.h>

namespace lambda_p
{
	namespace serialization
	{
		template <typename stream_type, typename token_sink>
		class simple_parser
		{
		public:
			simple_parser (stream_type & source_a, token_sink & target_a)
				: source (source_a),
				target (target_a)
			{

			}
			~simple_parser ()
			{
			}
			void parse ()
			{
				parse_all ();
			}
		private:
			void parse_all ()
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
						parse_whitespace ();
						break;
					case L';':
						parse_control ();
						break;
					default:
						parse_identifier ();
						break;
					}
				}
			}
			void parse_whitespace ()
			{
				::std::streampos begin (source.tellg ());
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
				::std::streampos end (source.tellg ());
				::lambda_p::tokens::whitespace <stream_type> * whitespace = new ::lambda_p::tokens::whitespace <stream_type> (source, begin, end);
				target (whitespace);
			}
			void parse_control ()
			{
				::std::streampos begin (source.tellg ());
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
						consume ();
						break;
					}
				}
				::std::streampos end (source.tellg ());
				::lambda_p::tokens::control <stream_type> * control = new ::lambda_p::tokens::control <stream_type> (source, begin, end);
				target (control);
			}
			void parse_identifier ()
			{				
				::std::streampos begin (source.tellg ());
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
						consume ();
						break;
					}
				}
				::std::streampos end (source.tellg ());
				::lambda_p::tokens::identifier <stream_type> * identifier = new ::lambda_p::tokens::identifier <stream_type> (source, begin, end);
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