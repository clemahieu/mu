#pragma once

#include <lambda_p_serialization/tokens/visitor.h>

#include <string>

namespace lambda_p_serialization
{
	namespace parser
	{
		class error : public lambda_p_serialization::tokens::visitor
		{
		public:
			error (std::wstring message_a);
			void operator () (lambda_p_serialization::tokens::divider * token) override;
			void operator () (lambda_p_serialization::tokens::identifier * token) override;
			void operator () (lambda_p_serialization::tokens::left_square * token) override;
			void operator () (lambda_p_serialization::tokens::right_square * token) override;
			void operator () (lambda_p_serialization::tokens::stream_end * token) override;
			std::wstring message;
		};
	}
}
