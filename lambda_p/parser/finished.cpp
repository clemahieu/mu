//
//  finished.cpp
//  lambda_p
//
//  Created by Colin LeMahieu on 9/28/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <lambda_p/parser/finished.h>

#include <lambda_p/parser/error.h>
#include <lambda_p/parser/parser.h>

lambda_p::parser::finished::finished (lambda_p::parser::parser & parser_a)
	: parser (parser_a)
{
}

void lambda_p::parser::finished::parse (lambda_p::tokens::token * token)
{
    std::wstring message (L"Token received after parser is finished");
    parser.state.push (boost::shared_ptr < lambda_p::parser::state> (new lambda_p::parser::error (message)));
}