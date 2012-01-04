#include "tee.h"

void lambda_p::core::tee::operator () (std::vector <boost::shared_ptr <lambda_p::core::node>> & arguments)
{
	for (auto i (targets.begin ()), j (targets.end ()); i != j; ++i)
	{
		(*(*i)) (arguments);
	}
}