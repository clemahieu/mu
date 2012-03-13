#pragma once

#include <mu/script/debugging/mapping.h>

#include <map>

namespace mu
{
	namespace script
	{
		namespace debugging
		{
			class flat_mapping : public mu::script::debugging::mapping
			{
			public:
				boost::shared_ptr <mu::script::debugging::operation_info> operation_info (boost::shared_ptr <mu::script::operation> operation_a) override;
				std::map <boost::shared_ptr <mu::script::operation>, boost::shared_ptr <mu::script::debugging::operation_info>> map;
			};
		}
	}
}