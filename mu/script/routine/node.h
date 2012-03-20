#pragma once

#include <mu/script/operation.h>

namespace mu
{
	namespace script
	{
		namespace routine
		{
			class node : public mu::script::operation
			{
				bool operator () (mu::script::context & context_a) override;
			};
		}
	}
}