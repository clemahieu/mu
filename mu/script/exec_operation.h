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
				operation (mu::io::keywording::extensions * extensions_a);
				mu::io::keywording::extensions * extensions;
				bool operator () (mu::script::context & context_a) override;
				mu::string name () override;
			};
		}
	}
}
