#pragma once

#include <mu/io/analyzer/extensions/extension.h>

namespace mu
{
	namespace io_test
	{
		class extension5 : public mu::io::analyzer::extensions::extension
		{
		public:
            bool operator () () override;
			void operator () (mu::core::errors::error_target & errors_a, mu::io::analyzer::expression & expression_a, mu::string remaining) override;
		};
	}
}
