#include "routine.h"

lambda_p_script::routine::routine (size_t count_a)
	: count (count_a)
{
}

void lambda_p_script::routine::operator () (std::vector <boost::shared_ptr <lambda_p::node>> & context, size_t base)
{
	auto open (base + count);
	for (auto i (body.begin ()), j (body.end ()); i != j; ++i)
	{
		(*(*i)) (context, base);
	}
}