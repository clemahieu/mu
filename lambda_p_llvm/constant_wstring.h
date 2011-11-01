//
//  constant_wstring.h
//  lambda_p_llvm
//
//  Created by Colin LeMahieu on 9/20/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

#include <string>

namespace llvm
{
    class Constant;
}
namespace lambda_p_llvm
{
	class generation_context;
    class constant_wstring
    {
    public:
        constant_wstring (lambda_p_llvm::generation_context & context, std::wstring const & string);
        llvm::Constant * value;
    };
}