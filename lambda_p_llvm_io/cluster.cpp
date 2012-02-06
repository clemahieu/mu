#include "cluster.h"

#include <lambda_p_llvm/cluster.h>
#include <lambda_p/cluster.h>
#include <lambda_p_llvm_io/routine.h>
#include <lambda_p/errors/error_target.h>

lambda_p_llvm_io::cluster::cluster (boost::shared_ptr <lambda_p::errors::error_target> errors_a, boost::shared_ptr <lambda_p::cluster> cluster_a, boost::shared_ptr <lambda_p_llvm::module::node> module_a)
	: result (new lambda_p_llvm::cluster)
{
	for (auto i (cluster_a->routines.begin ()), j (cluster_a->routines.end ()); i != j; ++i)
	{
		lambda_p_llvm_io::routine routine (errors_a, *i, module_a);
		if (!(*errors_a) ())
		{
			result->routines.push_back (routine.result);
		}
	}
}