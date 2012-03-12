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
				std::wstring stacktrace (boost::shared_ptr <mu::script::operation> operation_a) override;
				std::map <boost::shared_ptr <mu::script::operation>, std::wstring> map;
			};
		}
	}
}