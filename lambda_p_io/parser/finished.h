//
//  finished.h
//  lambda_p
//
//  Created by Colin LeMahieu on 9/28/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

#include <lambda_p_io/tokens/visitor.h>

namespace lambda_p_io
{
    namespace parser
    {
		class parser;
        class finished : public lambda_p_io::tokens::visitor
        {
        public:
			finished (lambda_p_io::parser::parser & parser_a);
			void operator () (lambda_p_io::tokens::divider * token) override;
			void operator () (lambda_p_io::tokens::identifier * token) override;
			void operator () (lambda_p_io::tokens::left_square * token) override;
			void operator () (lambda_p_io::tokens::right_square * token) override;
			void operator () (lambda_p_io::tokens::stream_end * token) override;
			void add_error (lambda_p_io::tokens::token * token);
			lambda_p_io::parser::parser & parser;
        };
    }
}