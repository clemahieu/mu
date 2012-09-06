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
            class value;
			class visitor
			{
			public:
                virtual ~visitor ();
				virtual void operator () (mu::io::tokens::divider const & token) = 0;
				virtual void operator () (mu::io::tokens::identifier const & token) = 0;
				virtual void operator () (mu::io::tokens::left_square const & token) = 0;
				virtual void operator () (mu::io::tokens::right_square const & token) = 0;
				virtual void operator () (mu::io::tokens::stream_end const & token) = 0;
                virtual void operator () (mu::io::tokens::value const & token) = 0;
			};
		}
	}
}