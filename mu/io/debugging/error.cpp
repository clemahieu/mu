#include <mu/io/debugging/error.h>

mu::io::debugging::error::error (boost::shared_ptr <mu::core::errors::error> error_a, mu::io::debugging::context context_a)
	: error_m (error_a),
	context (context_a)
{
}

void mu::io::debugging::error::string (std::wostream & stream)
{
	error_m->string (stream);
}