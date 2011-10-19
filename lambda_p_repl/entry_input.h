//
//  entry_input.h
//  lambda_p_repl
//
//  Created by Colin LeMahieu on 9/16/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

#include <iostream>

#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>

namespace lambda_p
{
    namespace core
    {
        class routine;
    }
}
namespace lambda_p_repl
{
	class character_stream;
    class entry_input
    {
    public:  
		void operator () (boost::shared_ptr < lambda_p_repl::character_stream> in_a, std::wostream & out_a);
        boost::shared_ptr < lambda_p::core::routine> routine;
    };
}
