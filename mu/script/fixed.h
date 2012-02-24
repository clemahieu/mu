#pragma once

#include <mu/script/operation.h>

namespace mu
{
	namespace script
	{
		class fixed : public mu::script::operation
		{
		public:
			void perform (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results) override;
			virtual void operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results) = 0;
			virtual size_t count () = 0;
		};
	}
}
