#pragma once

#include <lambda_p/binder/instance.h>
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
		class instance;
		class routine_instances : public lambda_p::binder::instance
		{
		public:
			routine_instances (void);
			boost::shared_ptr <lambda_p::binder::instance> & operator [] (size_t node);
			void merge (routine_instances & other, lambda_p::errors::error_list & problems);
			std::vector <boost::shared_ptr <lambda_p::binder::instance>> instances;
		};
	}
}

