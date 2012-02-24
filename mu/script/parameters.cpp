#include "parameters.h"

#include <mu/core/errors/error_target.h>
#include <mu/script/context.h>

#include <sstream>

void mu::script::parameters::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::script::context & context, std::vector <boost::shared_ptr <mu::core::node>> & target)
{
	target.push_back (context.parameters);
}