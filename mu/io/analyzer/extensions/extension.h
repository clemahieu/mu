#pragma once

#include <boost/shared_ptr.hpp>

namespace mu
{
	namespace core
	{
		namespace errors
		{
			class error_target;
		}
	}
	namespace io
	{
		namespace analyzer
		{
			class expression;
			namespace extensions
			{
				class extension
				{
				public:
                    virtual ~extension ();
					virtual void operator () (mu::core::errors::error_target * errors_a, mu::io::analyzer::expression & expression_a) = 0;
				};
			}
		}
	}
}

