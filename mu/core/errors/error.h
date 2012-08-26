#pragma once

#include <mu/core/types.h>

namespace mu
{
	namespace core
	{
		namespace errors
		{
			class error
			{
			public:
                virtual ~error ();
				virtual void string (mu::ostream & stream) = 0;
			};
		}
	}
}