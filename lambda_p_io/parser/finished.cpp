//
//  finished.cpp
//  lambda_p
//
//  Created by Colin LeMahieu on 9/28/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <lambda_p_io/parser/finished.h>

#include <lambda_p_io/parser/error.h>
#include <lambda_p_io/parser/parser.h>
#include <lambda_p_io/tokens/divider.h>
#include <lambda_p_io/tokens/identifier.h>
#include <lambda_p_io/tokens/left_square.h>
#include <lambda_p_io/tokens/right_square.h>
#include <lambda_p_io/tokens/stream_end.h>
#include <lambda_p_io/tokens/parameters.h>

lambda_p_io::parser::finished::finished (lambda_p_io::parser::parser & parser_a)
	: parser (parser_a)
{
}

void lambda_p_io::parser::finished::operator () (lambda_p_io::tokens::divider * token)
{
	add_error (token);
}

void lambda_p_io::parser::finished::operator () (lambda_p_io::tokens::identifier * token)
{
	add_error (token);
}

void lambda_p_io::parser::finished::operator () (lambda_p_io::tokens::left_square * token)
{
	add_error (token);
}

void lambda_p_io::parser::finished::operator () (lambda_p_io::tokens::right_square * token)
{
	add_error (token);
}

void lambda_p_io::parser::finished::operator () (lambda_p_io::tokens::stream_end * token)
{
	add_error (token);
}

void lambda_p_io::parser::finished::operator () (lambda_p_io::tokens::parameters * token)
{
	add_error (token);
}

void lambda_p_io::parser::finished::add_error (lambda_p_io::tokens::token * token)
{
    std::wstring message (L"Token received after parser is finished");
	parser.state.push (boost::shared_ptr <lambda_p_io::tokens::visitor> (new lambda_p_io::parser::error (message)));
}