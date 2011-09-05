#pragma once

namespace lambda_p
{
	namespace serialization
	{
		namespace lexer
		{
			enum state_id
			{
				state_error,
				state_begin,
				state_whitespace,
				state_control,
				state_identifier,
				state_multiline_comment,
				state_singleline_comment,
				state_manifest_data
			};
			class state
			{
			public:
				state(void);
				~state(void);
				virtual state_id state_type () = 0;
			};
		}
	}
}
