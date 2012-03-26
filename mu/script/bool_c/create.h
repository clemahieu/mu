#pragma once

#include <mu/script/operation.h>

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
			class create : public mu::script::operation
			{
			public:
				create ();
				bool operator () (mu::script::context & context_a) override;
				std::wstring name () override;
				std::map <std::wstring, boost::shared_ptr <mu::core::node>> values;
			};
		}
	}
}
