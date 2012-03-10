#pragma once

#include <mu/core/segment.h>

#include <boost/shared_ptr.hpp>

#include <vector>

namespace mu
{
	namespace core
	{
		class node;
		namespace errors
		{
			class error_target;
		}
	}
	namespace script
	{
		class context
		{
		public:
			context (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters_a, std::vector <boost::shared_ptr <mu::core::node>> & results_a);
			boost::shared_ptr <mu::core::errors::error_target> errors;
			mu::core::segment <boost::shared_ptr <mu::core::node>> parameters;
			std::vector <boost::shared_ptr <mu::core::node>> & results;
            std::vector <std::type_info const *> stack;
		};
	}
}