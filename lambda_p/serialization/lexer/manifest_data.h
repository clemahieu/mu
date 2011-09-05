#pragma once

#include <lambda_p/serialization/lexer/state.h>

#include <string>

#include <boost/circular_buffer.hpp>

namespace lambda_p
{
	namespace serialization
	{
		namespace lexer
		{
			class manifest_data : public state
			{
			public:
				manifest_data(void);
				~manifest_data(void);
				state_id state_type ();
				::std::wstring end_token;
				::std::wstring data;
				bool have_end_token;
				::boost::circular_buffer <wchar_t> last_characters;
				bool match ();
			};
		}
	}
}

