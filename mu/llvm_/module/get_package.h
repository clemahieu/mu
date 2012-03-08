#pragma once

#include <mu/script/fixed.h>

namespace mu
{
	namespace llvm_
	{
		namespace module
		{
			class get_package : public mu::script::fixed
			{
			public:
				void operator () (mu::script::context & context_a) override;
				size_t count () override;
				std::wstring name () override;
			};
		}
	}
}
