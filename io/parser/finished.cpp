//
//  finished.cpp
//  lambda_p
//
//  Created by Colin LeMahieu on 9/28/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <io/parser/finished.h>

#include <io/parser/error.h>
#include <io/parser/parser.h>
#include <io/tokens/divider.h>
#include <io/tokens/identifier.h>
#include <io/tokens/left_square.h>
#include <io/tokens/right_square.h>
#include <io/tokens/stream_end.h>
#include <io/tokens/parameters.h>
#include <core/errors/error_target.h>

mu::io::parser::finished::finished (mu::io::parser::parser & parser_a)
	: parser (parser_a)
{
}

void mu::io::parser::finished::operator () (mu::io::tokens::divider * token)
{
	add_error (token);
}

void mu::io::parser::finished::operator () (mu::io::tokens::identifier * token)
{
	add_error (token);
}

void mu::io::parser::finished::operator () (mu::io::tokens::left_square * token)
{
	add_error (token);
}

void mu::io::parser::finished::operator () (mu::io::tokens::right_square * token)
{
	add_error (token);
}

void mu::io::parser::finished::operator () (mu::io::tokens::stream_end * token)
{
	add_error (token);
}

void mu::io::parser::finished::operator () (mu::io::tokens::parameters * token)
{
	add_error (token);
}

void mu::io::parser::finished::add_error (mu::io::tokens::token * token)
{
    std::wstring message (L"Token received after parser is finished");
	(*parser.errors) (message);
	parser.state.push (boost::shared_ptr <mu::io::tokens::visitor> (new mu::io::parser::error));
}