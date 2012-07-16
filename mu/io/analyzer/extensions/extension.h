#pragma once

#include <mu/core/types.h>

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
                    virtual bool operator () () = 0;
					virtual void operator () (mu::core::errors::error_target * errors_a, mu::io::analyzer::expression & expression_a, mu::string remaining) = 0;
				};
			}
		}
	}
}

