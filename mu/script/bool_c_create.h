#pragma once

#include <mu/script/operation.h>

#include <map>

namespace mu
{
    namespace code
    {
        class node;
    }
	namespace script
	{
		namespace bool_c
		{
			class create : public mu::script::operation
			{
			public:
				create ();
				bool operator () (mu::script::context & context_a) override;
				std::map <mu::string, mu::core::node *> values;
			};
		}
	}
}
