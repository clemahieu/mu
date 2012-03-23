#include <mu/llvm_/synthesizer/operation.h>

#include <mu/script/context.h>
#include <mu/script/check.h>
#include <mu/core/cluster.h>
#include <mu/llvm_/module/node.h>
#include <mu/llvm_/cluster/node.h>
#include <mu/script/builder.h>
#include <mu/script/synthesizer/operation.h>
#include <mu/script/cluster/node.h>
#include <mu/script/runtime/routine.h>

#include <boost/make_shared.hpp>

bool mu::llvm_::synthesizer::operation::operator () (mu::script::context & context_a)
{
	bool valid (mu::script::check <mu::core::cluster, mu::llvm_::module::node> () (context_a));
	if (valid)
	{
		auto cluster (boost::static_pointer_cast <mu::core::cluster> (context_a.parameters (0)));
		auto module (boost::static_pointer_cast <mu::llvm_::module::node> (context_a.parameters (1)));
		context_a.reserve (1);
		auto result (boost::make_shared <mu::llvm_::cluster::node> ());
		context_a.locals (0) = result;
		context_a.push (boost::make_shared <mu::script::synthesizer::operation> ());
		context_a.push (cluster);
		valid = context_a ();
		assert (context_a.working_size () == 1);
		assert (boost::dynamic_pointer_cast <mu::script::cluster::node> (context_a.working (0)).get () == nullptr);
		auto cluster_l (boost::static_pointer_cast <mu::script::cluster::node> (context_a.working (0)));
		context_a.slide ();
		std::map <boost::shared_ptr <mu::core::routine>, boost::shared_ptr <mu::llvm_::function::node>> routine_mapping;
		if (cluster_l->routines.size () % 2 == 0)
		{
			for (auto i (cluster_l->routines.begin ()), j (cluster_l->routines.end ()); i != j; ++++i)
			{
				context_a.push (*i);
				auto valid_l (context_a ());
				valid = valid && valid_l;
				if (valid_l)
				{
					assert (context_a.working_size () == 1);
				}
				context_a.drop ();
			}
			if (valid)
			{
				for (auto i (cluster_l->routines.begin () + 1), j (cluster_l->routines.end ()); i != j; ++++i)
				{

				}
			}
		}
		else
		{
			context_a.errors (L"Cluster does not contain a signature routine for every body routine");
			valid = false;
		}
	}
	return valid;
}