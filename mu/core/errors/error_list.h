#pragma once

#include <mu/core/errors/error_target.h>

#include <boost/shared_ptr.hpp>

#include <vector>

namespace mu
{
	namespace core
	{
		namespace errors
		{
			class error;
			class error_list : public mu::core::errors::error_target
			{
			public:
				std::vector <std::pair <boost::shared_ptr <mu::core::errors::error>, mu::core::context>> errors;
				void operator () (boost::shared_ptr <mu::core::errors::error> error, mu::core::context context_a) override;
				bool operator () () override;
                void print (std::wostream & target) override;
			};
		}
	}
}
