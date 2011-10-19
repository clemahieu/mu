#include "routine_instances.h"

lambda_p::binder::routine_instances::routine_instances(void)
{
}

boost::shared_ptr < lambda_p::binder::instance> & lambda_p::binder::routine_instances::operator [] (size_t node)
{
	if (node >= instances.size ())
	{
		instances.resize (node + 1);
	}
	boost::shared_ptr < lambda_p::binder::instance> & result (instances [node]);
	return result;
}