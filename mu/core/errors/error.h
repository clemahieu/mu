//
//  error.h
//  lambda_p
//
//  Created by Colin LeMahieu on 9/24/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

#include <mu/io/debugging/context.h>
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