#pragma once

#include <mu/script/operation.h>

namespace mu
{
	namespace script
	{
		namespace closure
		{
			class apply : public mu::script::operation
			{
			public:
				void perform (mu::script::context & context_a) override;
				std::wstring name () override;
			};
		}
	}
}
