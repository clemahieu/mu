#pragma once

#include <mu/script/operation.h>

#include <map>

namespace mu
{
	namespace io
	{
        namespace keywording
        {
            class extensions;
        }
	}
	namespace script
	{
		namespace exec
		{
			class operation : public mu::script::operation
			{
			public:
				bool operator () (mu::script::context & context_a) override;
			};
		}
	}
}
