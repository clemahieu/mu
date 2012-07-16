#pragma once

namespace mu
{
	namespace io
	{
		namespace lexer
		{
			class state
			{
			public:
                virtual ~state ();
				virtual void lex (char32_t character) = 0;
			};
		}
	}
}