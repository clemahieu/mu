#include "adata.h"

#include <lambda_p_kernel/parser_states/adata.h>

boost::shared_ptr <lambda_p::parser::state> lambda_p_kernel::parser_factories::adata::create (lambda_p::parser::parser & parser_a, lambda_p::parser::routine & routine_a, lambda_p::parser::association_target & target)
{
	return boost::shared_ptr <lambda_p::parser::state> (new lambda_p_kernel::parser_states::adata (parser_a, routine_a, target));
}
