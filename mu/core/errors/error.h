//
//  error.h
//  lambda_p
//
//  Created by Colin LeMahieu on 9/24/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

#include <mu/core/context.h>

#include <ostream>

namespace mu
{
	namespace core
	{
		namespace errors
		{
			enum error_id
			{
				error_string_error,
				error_stacktrace_error
			};
			class error
			{
			public:
				virtual error_id error_type () = 0;
				virtual void string (std::wostream & stream) = 0;
			};
		}
	}
}