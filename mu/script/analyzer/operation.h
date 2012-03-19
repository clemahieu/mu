#pragma once

#include <mu/script_runtime/operation.h>

#include <boost/shared_ptr.hpp>

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
		namespace cluster
		{
			class node;
		}
		namespace extensions
		{
			class node;
		}
		namespace analyzer
		{
			class operation : public mu::script_runtime::operation
			{
			public:
				bool operator () (mu::script_runtime::context & context_a) override;
				boost::shared_ptr <mu::core::cluster> core (mu::script_runtime::context & context_a, boost::shared_ptr <mu::script::extensions::node> extensions, boost::shared_ptr <mu::io::ast::cluster> ast);
				void build (boost::shared_ptr <mu::core::cluster> * result_a, boost::shared_ptr <mu::core::cluster> cluster_a);
			};
		}
	}
}
