#pragma once

namespace lambda_p_io
{
	namespace tokens
	{
		class divider;
		class identifier;
		class left_square;
		class right_square;
		class stream_end;
		class token;
		class visitor
		{
		public:
			virtual void operator () (lambda_p_io::tokens::divider * token) = 0;
			virtual void operator () (lambda_p_io::tokens::identifier * token) = 0;
			virtual void operator () (lambda_p_io::tokens::left_square * token) = 0;
			virtual void operator () (lambda_p_io::tokens::right_square * token) = 0;
			virtual void operator () (lambda_p_io::tokens::stream_end * token) = 0;
		};
	}
}
