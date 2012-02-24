//
//  finished.h
//  lambda_p
//
//  Created by Colin LeMahieu on 9/28/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

#include <io/tokens/visitor.h>

namespace mu
{
	namespace io
	{
		namespace parser
		{
			class parser;
			class finished : public mu::io::tokens::visitor
			{
			public:
				finished (mu::io::parser::parser & parser_a);
				void operator () (mu::io::tokens::divider * token) override;
				void operator () (mu::io::tokens::identifier * token) override;
				void operator () (mu::io::tokens::left_square * token) override;
				void operator () (mu::io::tokens::right_square * token) override;
				void operator () (mu::io::tokens::stream_end * token) override;
				void operator () (mu::io::tokens::parameters * token) override;
				void add_error (mu::io::tokens::token * token);
				mu::io::parser::parser & parser;
			};
		}
	}
}