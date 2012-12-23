#pragma once

#include <mu/io/lexer_context.h>
#include <mu/core/types.h>

#include <boost/circular_buffer.hpp>

namespace mu
{
	namespace io
	{
		namespace lexer
		{
            class context;
			class state
			{
			public:
                virtual ~state ();
				virtual void lex (boost::circular_buffer <mu::io::lexer::context> & context_a) = 0;
			};
		}
	}
}