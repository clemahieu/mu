#pragma once

#include <lambda_p/binder/instance.h>
#include <lambda_p/errors/error.h>

#include <boost/shared_ptr.hpp>

#include <iostream>
#include <map>
#include <vector>

namespace lambda_p
{
	namespace core
	{
		class statement;
	}
	namespace binder
	{
		class routine_instances;
		class binder : virtual public instance
		{
		public:
			binder(void);
			~binder(void);
			virtual void bind (lambda_p::core::statement * statement, lambda_p::binder::routine_instances & instances, std::vector < boost::shared_ptr < lambda_p::errors::error> > & problems) = 0;
			virtual std::wstring binder_name () = 0;
		protected:
			void add_error (std::wstring message, std::vector < boost::shared_ptr < lambda_p::errors::error> > & problems);
			void unexpected_binder_type_error (size_t position, std::wstring expected, std::vector < boost::shared_ptr < lambda_p::errors::error> > & problems);
			// Checks for the specified number of results and arguments
			void check_count (size_t result_count, size_t argument_count, lambda_p::core::statement * statement, std::vector < boost::shared_ptr < lambda_p::errors::error> > & problems);
		};
	}
}

