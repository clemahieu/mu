#pragma once

#include <mu/script/operation.h>

#include <vector>

#include <boost/shared_ptr.hpp>

namespace mu
{
	namespace script
	{
		class call;
		namespace cluster
		{
			class node;
		}
		class routine : public mu::script::operation
		{
		public:
			routine (boost::shared_ptr <mu::script::cluster::node> cluster_a);
			void perform (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results) override;
			std::wstring name () override;
			boost::shared_ptr <mu::script::cluster::node> cluster;
			std::vector <boost::shared_ptr <mu::script::call>> calls;
		};
	}
}
