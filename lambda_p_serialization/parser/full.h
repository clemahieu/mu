#pragma once

#include <lambda_p_serialization/tokens/visitor.h>

#include <vector>

namespace lambda_p_serialization
{
	namespace parser
	{
		class full : public lambda_p_serialization::tokens::visitor
		{
		public:
			void operator () (lambda_p_serialization::tokens::divider * token) override;
			void operator () (lambda_p_serialization::tokens::identifier * token) override;
			void operator () (lambda_p_serialization::tokens::left_square * token) override;
			void operator () (lambda_p_serialization::tokens::right_square * token) override;
			void operator () (lambda_p_serialization::tokens::stream_end * token) override;
			void unexpected_token (lambda_p_serialization::tokens::token * token);
			std::vector <std::wstring> names;
			std::wstring full_name;
		};
	}
}

