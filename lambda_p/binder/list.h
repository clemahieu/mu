#pragma once

#include <lambda_p/binder/binder.h>

#include <vector>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	namespace binder
	{
		class instance;
	}
}
namespace lambda_p
{
	namespace binder
	{
		class list : public lambda_p::binder::binder
		{
		public:
			void bind (lambda_p::core::statement * statement, lambda_p::binder::routine_instances & instances, std::vector < boost::shared_ptr < lambda_p::errors::error> > & problems);
			std::wstring binder_name ();
			std::vector < boost::shared_ptr < lambda_p::binder::instance> > instances;
		};
	}
}

