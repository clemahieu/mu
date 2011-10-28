#pragma once

#include <lambda_p/binder/binder.h>

#include <vector>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	namespace binder
	{
		class node;
	}
}
namespace lambda_p
{
	namespace binder
	{
		class list : public lambda_p::binder::binder
		{
		public:
			void bind (lambda_p::core::statement * statement, lambda_p::binder::node_list & nodes, lambda_p::errors::error_list & problems) override;
			std::wstring binder_name () override;
			std::vector <boost::shared_ptr <lambda_p::binder::node>> nodes;
		};
	}
}

