#pragma once

#include <mu/script/fixed.h>

namespace mu
{
	namespace script
	{
		namespace string
		{
			class node;
		}
		namespace extensions
		{
			class node;
		}
		namespace cluster
		{
			class node;
		}
		namespace load
		{
			class operation : public mu::script::fixed
			{
			public:
				void operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results) override;
				boost::shared_ptr <mu::script::cluster::node> core (boost::shared_ptr <mu::core::errors::error_target> errors_a, boost::shared_ptr <mu::script::extensions::node> extensions, boost::shared_ptr <mu::script::string::node> file);
				size_t count () override;
			};
		}
	}
}

