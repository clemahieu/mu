#pragma once

#include <mu/script/operation.h>

namespace mu
{
	namespace llvm_
	{
		namespace global_variable
		{
			class create_set : public mu::script::operation
			{
			public:
				bool operator () (mu::script::context & context_a) override;
				std::wstring name () override;
			};
		}
	}
}
