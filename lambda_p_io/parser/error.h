#pragma once

#include <lambda_p_io/tokens/visitor.h>

#include <string>

namespace lambda_p_io
{
	namespace parser
	{
		class error : public lambda_p_io::tokens::visitor
		{
		public:
			error (std::wstring message_a);
			void operator () (lambda_p_io::tokens::divider * token) override;
			void operator () (lambda_p_io::tokens::identifier * token) override;
			void operator () (lambda_p_io::tokens::left_square * token) override;
			void operator () (lambda_p_io::tokens::right_square * token) override;
			void operator () (lambda_p_io::tokens::stream_end * token) override;
			std::wstring message;
		};
	}
}
