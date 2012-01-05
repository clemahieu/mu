#include "number.h"

#include <lambda_p_kernel/parser_states/number.h>

boost::shared_ptr <lambda_p::parser::state> lambda_p_kernel::parser_factories::number::create (lambda_p::parser::parser & parser_a, lambda_p::parser::routine & routine_a, lambda_p::parser::association_target & target)
{
	return boost::shared_ptr <lambda_p_kernel::parser_states::number> (new lambda_p_kernel::parser_states::number (parser_a, routine_a, target));
}