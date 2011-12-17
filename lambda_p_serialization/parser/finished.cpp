//
//  finished.cpp
//  lambda_p
//
//  Created by Colin LeMahieu on 9/28/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <lambda_p_serialization/parser/finished.h>

#include <lambda_p_serialization/parser/error.h>
#include <lambda_p_serialization/parser/parser.h>

lambda_p_serialization::parser::finished::finished (lambda_p_serialization::parser::parser & parser_a)
	: parser (parser_a)
{
}

void lambda_p_serialization::parser::finished::parse (lambda_p_serialization::tokens::token * token)
{
    std::wstring message (L"Token received after parser is finished");
    parser.state.push (boost::shared_ptr <lambda_p_serialization::parser::state> (new lambda_p_serialization::parser::error (message)));
}