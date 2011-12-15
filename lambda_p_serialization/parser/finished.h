//
//  finished.h
//  lambda_p
//
//  Created by Colin LeMahieu on 9/28/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

#include <lambda_p_serialization/parser/state.h>

namespace lambda_p_serialization
{
    namespace parser
    {
		class parser;
        class finished : public lambda_p_serialization::parser::state
        {
        public:
			finished (lambda_p_serialization::parser::parser & parser_a);
			void parse (lambda_p_serialization::tokens::token * token) override;
			lambda_p_serialization::parser::parser & parser;
        };
    }
}