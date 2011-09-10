#include "node_list.h"

lambda_p::parser::node_list::node_list(void)
{
}

lambda_p::parser::node_list::~node_list(void)
{
}

::lambda_p::parser::state_id lambda_p::parser::node_list::state_type ()
{
	return lambda_p::parser::state_node_list;
}
