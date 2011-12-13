//
//  finished.h
//  lambda_p
//
//  Created by Colin LeMahieu on 9/28/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

#include <lambda_p/parser/state.h>

namespace lambda_p
{
    namespace parser
    {
		class parser;
        class finished : public lambda_p::parser::state
        {
        public:
			finished (lambda_p::parser::parser & parser_a);
			void parse (lambda_p::tokens::token * token) override;
			lambda_p::parser::parser & parser;
        };
    }
}