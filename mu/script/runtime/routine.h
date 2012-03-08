#pragma once

#include <mu/script/operation.h>

#include <vector>

#include <boost/shared_ptr.hpp>

namespace mu
{
	namespace script
	{
		namespace cluster
		{
			class node;
		}
		namespace runtime
		{
			class call;
			class routine : public mu::script::operation
			{
			public:
				routine (boost::shared_ptr <mu::script::cluster::node> cluster_a);
				void perform (mu::script::context & context_a) override;
				std::wstring name () override;
				boost::shared_ptr <mu::script::cluster::node> cluster;
				std::vector <boost::shared_ptr <mu::script::runtime::call>> calls;
			};
		}
	}
}
