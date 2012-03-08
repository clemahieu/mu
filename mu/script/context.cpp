#include <mu/script/context.h>

mu::script::context::context (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters_a, std::vector <boost::shared_ptr <mu::core::node>> & results_a)
	: errors (errors_a),
	parameters (parameters_a),
	results (results_a)
{
}