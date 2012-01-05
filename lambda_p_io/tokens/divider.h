//
//  statement_end.h
//  lambda_p
//
//  Created by Colin LeMahieu on 9/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

#include <lambda_p_io/tokens/token.h>

#include <string>

namespace lambda_p_io
{
    namespace tokens
    {
        class divider : public lambda_p_io::tokens::token
        {
			std::wstring token_name () override;
			void operator () (lambda_p_io::tokens::visitor * visitor_a) override;
        };
    }
}