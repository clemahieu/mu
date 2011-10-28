#pragma once

namespace lambda_p
{
	namespace core
	{
		class statement;
	}
	namespace parser
	{
		class target_set
		{
		public:
			target_set (lambda_p::core::statement & statement_a);
			void operator () (size_t declaration);
			lambda_p::core::statement & statement;
		};
	}
}

