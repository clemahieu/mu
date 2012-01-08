#include "expression.h"

lambda_p_script::runtime::expression::expression (size_t index_a)
	: index (index_a)
{
}

void lambda_p_script::runtime::expression::operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, std::vector <boost::shared_ptr <lambda_p::node>> & target)
{

}