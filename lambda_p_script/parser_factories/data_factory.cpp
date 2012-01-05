#include "data_factory.h"

#include <lambda_p_kernel/parser_states/data.h>

boost::shared_ptr <lambda_p::parser::state> lambda_p_kernel::parser_factories::data_factory::create (lambda_p::parser::parser & parser_a, lambda_p::parser::routine & routine_a, lambda_p::parser::association_target & target)
{
	return boost::shared_ptr <lambda_p::parser::state> (new lambda_p_kernel::parser_states::data (parser_a, routine_a, target));
}