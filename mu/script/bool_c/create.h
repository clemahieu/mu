#pragma once

#include <mu/script_runtime/operation.h>

#include <map>

#include <boost/shared_ptr.hpp>

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
			class create : public mu::script_runtime::operation
			{
			public:
				create ();
				bool operator () (mu::script_runtime::context & context_a) override;
				std::wstring name () override;
				std::map <std::wstring, boost::shared_ptr <mu::core::node>> values;
			};
		}
	}
}
