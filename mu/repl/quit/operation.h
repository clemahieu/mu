#pragma once

#include <mu/script/fixed.h>

namespace mu
{
	namespace repl
	{
		class repl;
		namespace quit
		{
			class operation : public mu::script::fixed
			{
			public:
				operation (mu::repl::repl & repl_a);
				void operator () (mu::script::context & context_a) override;
				size_t count () override;
				std::wstring name () override;
				mu::repl::repl & repl;
			};
		}
	}
}
