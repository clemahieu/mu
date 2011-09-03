//
//  error.h
//  lambda_p
//
//  Created by Colin LeMahieu on 9/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

#include <lambda_p/tokens/token.h>

#include <string>

namespace lambda_p
{
    namespace tokens
    {
        class error : public token
        {
        public:
            error (::std::wstring message_a);
			size_t token_id ();
        private:
            ::std::wstring message;
        };
    }
}