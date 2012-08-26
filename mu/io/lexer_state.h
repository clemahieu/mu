#pragma once

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
				virtual void lex (mu::io::lexer::context const & context_a) = 0;
			};
		}
	}
}