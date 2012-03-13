#pragma once

#include <mu/core/errors/error_target.h>

#include <boost/shared_ptr.hpp>

#include <vector>

namespace mu
{
	namespace core
	{
		class node;
	}
	namespace script
	{
		class operation;
        namespace debugging
        {
            class call_info;
        }
		class context : public mu::core::errors::error_target
		{
		public:
			context (boost::shared_ptr <mu::core::errors::error_target> errors_a, std::vector <boost::shared_ptr <mu::core::node>> & parameters_a, std::vector <boost::shared_ptr <mu::core::node>> & results_a, std::vector <boost::shared_ptr <mu::script::debugging::call_info>> & function_stack_a);
			context (mu::script::context & context_a, std::vector <boost::shared_ptr <mu::core::node>> & parameters_a, std::vector <boost::shared_ptr <mu::core::node>> & results_a);
            std::vector <boost::shared_ptr <mu::core::node>> & parameters;
			std::vector <boost::shared_ptr <mu::core::node>> & results;
            std::vector <boost::shared_ptr <mu::script::debugging::call_info>> & call_stack;
			void operator () (boost::shared_ptr <mu::core::errors::error> error, mu::core::context context_a) override;
			bool operator () () override;
			void operator () (std::wstring error) override;
			void operator () (wchar_t const * error) override;
            void print (std::wostream & target) override;
			boost::shared_ptr <mu::core::errors::error_target> errors;
		};
	}
}