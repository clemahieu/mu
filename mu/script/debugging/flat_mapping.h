#pragma once

#include <mu/script/debugging/mapping.h>

#include <map>

namespace mu
{
	namespace script
	{
		class operation;
		namespace extensions
		{
			class node;
		}
		namespace debugging
		{
			class flat_mapping : public mu::script::debugging::mapping
			{
			public:
				boost::shared_ptr <mu::script::debugging::operation_info> operation_info (boost::shared_ptr <mu::script::operation> operation_a) override;
				void add_with_extensions (mu::script::extensions::node * extensions_a, std::wstring name, boost::shared_ptr <mu::script::operation> operation_a);
				std::map <boost::shared_ptr <mu::script::operation>, boost::shared_ptr <mu::script::debugging::operation_info>> map;
			};
		}
	}
}