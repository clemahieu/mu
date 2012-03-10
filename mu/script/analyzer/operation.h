#pragma once

#include <mu/script/operation.h>

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
			class operation : public mu::script::operation
			{
			public:
				void operator () (mu::script::context & context_a) override;
				boost::shared_ptr <mu::script::cluster::node> core (boost::shared_ptr <mu::core::errors::error_target> errors_a, boost::shared_ptr <mu::script::extensions::node> extensions, boost::shared_ptr <mu::io::ast::cluster> ast);
				void build (boost::shared_ptr <mu::script::cluster::node> * result_a, boost::shared_ptr <mu::core::cluster> cluster_a);
			};
		}
	}
}
