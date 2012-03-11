#pragma once

#include <mu/core/segment.h>
#include <mu/core/errors/error_target.h>

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
		class context : public mu::core::errors::error_target
		{
		public:
			context (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters_a, std::vector <boost::shared_ptr <mu::core::node>> & results_a, std::vector <std::type_info const *> & stack_a);
			context (mu::script::context & context_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters_a, std::vector <boost::shared_ptr <mu::core::node>> & results_a);
			mu::core::segment <boost::shared_ptr <mu::core::node>> parameters;
			std::vector <boost::shared_ptr <mu::core::node>> & results;
            std::vector <std::type_info const *> & stack;
			void operator () (boost::shared_ptr <mu::core::errors::error> error, mu::core::context context_a) override;
			bool operator () () override;
			void operator () (std::wstring error) override;
			void operator () (wchar_t const * error) override;
            void print (std::wostream & target) override;
			boost::shared_ptr <mu::core::errors::error_target> errors;
		};
	}
}