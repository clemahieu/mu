#pragma once

#include <string>

namespace lambda_p
{
	namespace core
	{
		class routine;
	}
}
namespace lambda_p_repl
{
	class repl;
	class quit_parameter
	{
	public:
		quit_parameter (::lambda_p_repl::repl & repl_a);
		~quit_parameter (void);
		void apply_to (::lambda_p::core::routine * routine_a);
		::std::wstring result;
		::lambda_p_repl::repl & repl;
	};
}

