#pragma once

#include <lambda_p_script/operation.h>

#include <vector>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	class node;
}
namespace lambda_p_script
{
	class call;
	namespace cluster
	{
		class node;
	}
	class routine : public lambda_p_script::operation
	{
	public:
		routine (boost::shared_ptr <lambda_p_script::cluster::node> cluster_a);
		void perform (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results) override;
		std::wstring name () override;
		boost::shared_ptr <lambda_p_script::cluster::node> cluster;
		std::vector <boost::shared_ptr <lambda_p_script::call>> calls;
	};
}

