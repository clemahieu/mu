#pragma once

#include <mu/script/fixed.h>

namespace mu
{
	namespace core
	{
		class cluster;
	}
	namespace io
	{
		namespace ast
		{
			class cluster;
		}
	}
	namespace script
	{
		namespace string
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
				void operator () (mu::script::context & context_a) override;
				boost::shared_ptr <mu::io::ast::cluster> core (boost::shared_ptr <mu::core::errors::error_target> errors_a, boost::shared_ptr <mu::script::string::node> file);
				size_t count () override;
			};
		}
	}
}

