//
//  error.h
//  lambda_p
//
//  Created by Colin LeMahieu on 9/24/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

#include <ostream>

namespace lambda_p
{
    namespace errors
    {
        enum error_id
        {
            error_orphan_node,
            error_orphan_reference,
            error_undefined_reference,
			error_unresolved_statement,
			error_unexpected_result_count,
			error_unexpected_argument_count,
			error_unexpected_node_type,
			error_binder_string,
			error_node_out_of_order,
			error_target_not_bindable
        };
        class error
        {
        public:
            virtual error_id error_type () = 0;
            virtual void string (::std::wostream & stream) = 0;
        };
    }
}