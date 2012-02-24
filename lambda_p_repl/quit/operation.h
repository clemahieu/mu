#pragma once

#include <lambda_p_script/fixed.h>

namespace lambda_p_repl
{
	class repl;
	namespace quit
	{
		class operation : public lambda_p_script::fixed
		{
		public:
			operation (lambda_p_repl::repl & repl_a);
			void operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results) override;
			size_t count () override;
			std::wstring name () override;
			lambda_p_repl::repl & repl;
		};
	}
}

