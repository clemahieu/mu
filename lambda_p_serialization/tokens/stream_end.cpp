//
//  stream_end.cpp
//  lambda_p
//
//  Created by Colin LeMahieu on 9/28/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <lambda_p_serialization/tokens/stream_end.h>

lambda_p_serialization::tokens::token_ids lambda_p_serialization::tokens::stream_end::token_id ()
{
    return lambda_p_serialization::tokens::token_id_stream_end;
}

std::wstring lambda_p_serialization::tokens::stream_end::token_name ()
{
	return std::wstring (L"stream end");
}