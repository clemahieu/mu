#pragma once

#include <lambda_p/binder/node.h>
#include <lambda_p/errors/error_list.h>

#include <boost/shared_ptr.hpp>

#include <vector>

namespace lambda_p
{
	namespace errors
	{
		class error;
	}
	namespace binder
	{
		class node;
		class node_list : public lambda_p::binder::node
		{
		public:
			node_list (void);
			boost::shared_ptr <lambda_p::binder::node> & operator [] (size_t node);
			void merge (node_list & other, lambda_p::errors::error_list & problems);
			std::vector <boost::shared_ptr <lambda_p::binder::node>> instances;
		};
	}
}

