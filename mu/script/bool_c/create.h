#pragma once

#include <mu/script/fixed.h>

#include <map>

namespace mu
{
	namespace script
	{
		namespace bool_c
		{
			class create : public mu::script::fixed
			{
			public:
				create ();
				void operator () (mu::script::context & context_a) override;
				size_t count () override;
				std::wstring name () override;
				std::map <std::wstring, boost::shared_ptr <mu::core::node>> values;
			};
		}
	}
}
