#include "script.h"

#include <mu/script_io/cluster.h>
#include <mu/script/runtime.routine.h>

mu::script_io::script::script (mu::script_io::cluster & cluster_a)
	: cluster (cluster_a)
{
}

boost::shared_ptr <mu::core::node> mu::script_io::script::operator () (boost::shared_ptr <mu::core::routine> routine_a)
{
	return cluster.process_routine (routine_a);
}