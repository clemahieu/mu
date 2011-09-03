//
//  declaration.h
//  lambda_p
//
//  Created by Colin LeMahieu on 9/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

#include <lambda_p/tokens/token.h>

namespace lambda_p
{
    namespace tokens
    {
        class declaration : public token
        {
			size_t token_id ();
        };
    }
}