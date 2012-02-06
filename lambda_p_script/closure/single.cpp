#include "single.h"

lambda_p_script::closure::single::single (boost::shared_ptr <lambda_p_script::operation> operation_a)
	: operation_m (operation_a)
{
}

lambda_p_script::closure::single::single (std::vector <boost::shared_ptr <lambda_p::node>> & closed_a, boost::shared_ptr <lambda_p_script::operation> operation_a)
	: closed (closed_a),
	operation_m (operation_a)
{
}

void lambda_p_script::closure::single::perform (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results)
{
	std::vector <boost::shared_ptr <lambda_p::node>> closed_l (closed.begin (), closed.end ());
	closed_l.insert (closed_l.end (), parameters.begin (), parameters.end ());
	operation_m->perform (errors_a, closed_l, results);
}

std::wstring lambda_p_script::closure::single::name ()
{
	return std::wstring (L"lambda_p_script::closure::single");
}