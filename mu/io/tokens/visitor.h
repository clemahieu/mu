#pragma once

namespace mu
{
	namespace io
	{
		namespace tokens
		{
			class divider;
			class identifier;
			class left_square;
			class right_square;
			class stream_end;
			class token;
			class parameters;
            class value;
			class visitor
			{
			public:
                virtual ~visitor ();
				virtual void operator () (mu::io::tokens::divider * token) = 0;
				virtual void operator () (mu::io::tokens::identifier * token) = 0;
				virtual void operator () (mu::io::tokens::left_square * token) = 0;
				virtual void operator () (mu::io::tokens::right_square * token) = 0;
				virtual void operator () (mu::io::tokens::stream_end * token) = 0;
				virtual void operator () (mu::io::tokens::parameters * token) = 0;
                virtual void operator () (mu::io::tokens::value * token) = 0;
			};
		}
	}
}