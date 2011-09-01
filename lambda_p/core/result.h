#pragma once

#include <iostream>

#include <lambda_p/core/node.h>

namespace lambda_p
{
	namespace core
	{
		class routine;
		class result : public node
		{
		public:
			result (::lambda_p::core::routine & routine_a, size_t statement_a, size_t index_a);
			~result (void);
			void validate (::std::iostream & problems);
		private:
			::lambda_p::core::routine & routine;
			size_t statement;
			size_t index;
		};
	}
}

