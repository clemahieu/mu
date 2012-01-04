#include "tee.h"

void lambda_p::tee::operator () (std::vector <boost::shared_ptr <lambda_p::node>> & arguments)
{
	for (auto i (targets.begin ()), j (targets.end ()); i != j; ++i)
	{
		(*(*i)) (arguments);
	}
}