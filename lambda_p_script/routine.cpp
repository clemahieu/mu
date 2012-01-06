#include "routine.h"

#include <lambda_p_script/call.h>

void lambda_p_script::routine::operator () (std::vector <boost::shared_ptr <lambda_p::node>> & context, size_t base)
{
	auto base_l (base);
	auto open (base_l + count);
	for (auto i (body.begin ()), j (body.end ()); i != j; ++i)
	{
		(*(*i)) (context, base_l, open);
	}
}