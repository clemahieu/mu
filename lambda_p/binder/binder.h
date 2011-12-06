#pragma once

#include <lambda_p/binder/node.h>

#include <boost/shared_ptr.hpp>

#include <string>
#include <map>

namespace lambda_p
{
	namespace core
	{
		class expression;
	}
	namespace errors
	{
		class error_list;
	}
	namespace binder
	{
		class list;
		class binder : virtual public lambda_p::binder::node
		{
		public:
			virtual void bind (lambda_p::core::expression * expression, std::map <lambda_p::core::expression *, boost::shared_ptr <lambda_p::binder::node>> & nodes, lambda_p::errors::error_list & problems) = 0;
			virtual std::wstring binder_name () = 0;
		protected:
			void check_binder (boost::shared_ptr <lambda_p::binder::node> binder_a, size_t position, wchar_t * expected, lambda_p::errors::error_list & problems);
			void add_error (wchar_t * message, lambda_p::errors::error_list & problems);
			void add_error (std::wstring message, lambda_p::errors::error_list & problems);
			void unexpected_binder_type_error (size_t position, wchar_t * expected, lambda_p::errors::error_list & problems);
		};
	}
}

