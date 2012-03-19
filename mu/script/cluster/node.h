#pragma once

#include <mu/script_runtime/operation.h>

#include <vector>
#include <map>
#include <set>

#include <boost/shared_ptr.hpp>

namespace mu
{
	namespace core
	{
		class routine;
	}
	namespace script
	{
		namespace runtime
		{
			class routine;
		}
		namespace cluster
		{
			class node : public mu::script_runtime::operation
			{
			public:
				node ();
				node (std::vector <boost::shared_ptr <mu::script::runtime::routine>> routines_a);
				node (std::map <std::wstring, boost::shared_ptr <mu::script::runtime::routine>> names_a, std::vector <boost::shared_ptr <mu::script::runtime::routine>> routines_a);
				bool operator () (mu::script_runtime::context & context_a) override;
				std::map <std::wstring, boost::shared_ptr <mu::script::runtime::routine>> names;
				std::vector <boost::shared_ptr <mu::script::runtime::routine>> routines;
			};
		}
	}
}
