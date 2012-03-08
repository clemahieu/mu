#pragma once

#include <mu/script/fixed.h>

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
			class node : public mu::script::fixed
			{
			public:
				node ();
				node (std::vector <boost::shared_ptr <mu::script::runtime::routine>> routines_a);
				node (std::map <std::wstring, boost::shared_ptr <mu::script::runtime::routine>> names_a, std::vector <boost::shared_ptr <mu::script::runtime::routine>> routines_a);
				void operator () (mu::script::context & context_a) override;
				size_t count () override;
				std::map <std::wstring, boost::shared_ptr <mu::script::runtime::routine>> names;
				std::vector <boost::shared_ptr <mu::script::runtime::routine>> routines;
			};
		}
	}
}
