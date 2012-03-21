#pragma once

#include <mu/script/operation.h>

namespace mu
{
	namespace llvm_
	{
		namespace constant
		{
			class create_from_string : public mu::script::operation
			{
			public:
				bool operator () (mu::script::context & context_a) override;
				std::wstring name () override;
			};
		}
	}
}
