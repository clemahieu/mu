#pragma once

#include <mu/script_runtime/operation.h>

namespace mu
{
	namespace core
	{
		class cluster;
        namespace errors
        {
            class error_target;
        }
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
			class operation : public mu::script_runtime::operation
			{
			public:
				bool operator () (mu::script_runtime::context & context_a) override;
				boost::shared_ptr <mu::io::ast::cluster> core (mu::script_runtime::context & context_a, boost::shared_ptr <mu::script::string::node> file);
			};
		}
	}
}

