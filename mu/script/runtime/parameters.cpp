#include <mu/script/runtime/parameters.h>

#include <mu/core/errors/error_target.h>
#include <mu/script/runtime/frame.h>

#include <sstream>

void mu::script::runtime::parameters::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::script::runtime::frame & frame, std::vector <boost::shared_ptr <mu::core::node>> & target)
{
	target.push_back (frame.parameters);
}