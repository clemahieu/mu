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
				std::vector <boost::shared_ptr <mu::core::errors::error>> errors;
				void operator () (boost::shared_ptr <mu::core::errors::error> error) override;
				bool operator () () override;
                void print (std::wostream & target) override;
			};
		}
	}
}
