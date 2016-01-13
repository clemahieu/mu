#pragma once

#include <mu/core/types.hpp>
#include <mu/core/stream.hpp>

namespace mu
{
	namespace io
	{
		class token;
		class lexer;
		class stream_token : public mu::io::stream <mu::io::token *>
		{
		public:
			stream_token (mu::io::lexer & lexer_a, size_t size_a);
			void consume (size_t size_a) override;
			mu::io::token * & operator [] (size_t size_a) override;
			size_t size () override;
		private:
			void refill ();
			size_t size_m;
			std::deque <mu::io::token *> buffer;
			mu::io::lexer & lexer;
		};
	}
}
