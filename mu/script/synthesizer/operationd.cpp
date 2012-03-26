#include <mu/script/synthesizer/operationd.h>

#include <mu/script/context.h>
#include <mu/script/check.h>
#include <mu/core/cluster.h>
#include <mu/script/cluster/node.h>
#include <mu/script/runtime/routine.h>
#include <mu/script/runtime/expression.h>
#include <mu/script/runtime/locals.h>
#include <mu/script/runtime/reference.h>
#include <mu/core/routine.h>
#include <mu/script/topology/core.h>
#include <mu/script/topology/node.h>
#include <mu/core/expression.h>
#include <mu/core/reference.h>
#include <mu/script/runtime/selection.h>
#include <mu/script/runtime/fixed.h>
#include <mu/core/parameters.h>
#include <mu/io/debugging/mapping.h>

#include <boost/make_shared.hpp>

bool mu::script::synthesizer::operationd::operator () (mu::script::context & context_a)
{
	bool valid (mu::script::check <mu::core::cluster, mu::io::debugging::mapping> () (context_a));
	if (valid)
	{
		auto cluster (boost::static_pointer_cast <mu::core::cluster> (context_a.parameters (0)));
		auto cluster_mapping (boost::static_pointer_cast <mu::io::debugging::mapping> (context_a.parameters (1)));
		context_a.reserve (2);
		auto result (boost::make_shared <mu::script::cluster::node> ());
		context_a.locals (0) = result;
		auto result_debugging (boost::make_shared <mu::io::debugging::mapping> ());
		context_a.locals (1) = result_debugging;
		map (cluster_mapping, result_debugging, cluster, result);
		std::map <boost::shared_ptr <mu::core::routine>, boost::shared_ptr <mu::script::runtime::routine>> routine_mapping;
		for (auto i (cluster->routines.begin ()), j (cluster->routines.end ()); i != j; ++i)
		{
			auto parameters (boost::make_shared <mu::script::runtime::expression> ());
			auto routine (boost::make_shared <mu::script::runtime::routine> (parameters));
			routine_mapping [*i] = routine;
		}
		for (auto i (cluster->routines.begin ()), j (cluster->routines.end ()); i != j; ++i)
		{
			auto existing (routine_mapping.find (*i));
			assert (existing != routine_mapping.end ());
			auto routine (existing->second);
			map (cluster_mapping, result_debugging, *i, routine);
			mu::script::topology::core topology ((*i)->body);
			valid = valid && topology.acyclic;
			if (topology.acyclic)
			{
				std::map <boost::shared_ptr <mu::core::expression>, boost::shared_ptr <mu::script::runtime::expression>> expression_mapping;
				for (auto k (topology.topology->expressions.begin ()), l (topology.topology->expressions.end ()); k != l; ++k)
				{
					auto expression (boost::make_shared <mu::script::runtime::expression> ());
					map (cluster_mapping, result_debugging, *k, expression);
					routine->expressions.push_back (expression);
					for (auto m ((*k)->dependencies.begin ()), n ((*k)->dependencies.end ()); m != n; ++m)
					{
						auto routine_l (boost::dynamic_pointer_cast <mu::core::routine> (*m));
						if (routine_l.get () != nullptr)
						{
							auto existing (routine_mapping.find (routine_l));
							assert (existing != routine_mapping.end ());
							expression->dependencies.push_back (boost::make_shared <mu::script::runtime::fixed> (existing->second));
						}
						else
						{
							auto expression_l (boost::dynamic_pointer_cast <mu::core::expression> (*m));
							if (expression_l.get () != nullptr)
							{
								auto existing (expression_mapping.find (expression_l));
								assert (existing != expression_mapping.end ());
								expression->dependencies.push_back (boost::make_shared <mu::script::runtime::reference> (existing->second));
							}
							else
							{
								auto reference_l (boost::dynamic_pointer_cast <mu::core::reference> (*m));
								if (reference_l.get () != nullptr)
								{
									auto existing (expression_mapping.find (reference_l->expression));
									assert (existing != expression_mapping.end ());
									expression->dependencies.push_back (boost::make_shared <mu::script::runtime::selection> (existing->second, reference_l->index));
								}
								else
								{
									auto parameters_l (boost::dynamic_pointer_cast <mu::core::parameters> (*m));
									if (parameters_l.get () != nullptr)
									{
										expression->dependencies.push_back (boost::make_shared <mu::script::runtime::reference> (routine->parameters));
									}
									else
									{
										expression->dependencies.push_back (boost::make_shared <mu::script::runtime::fixed> (*m));
									}
								}
							}
						}
					}
					expression_mapping [*k] = expression;
				}
				result->routines.push_back (routine);
			}
			else
			{
				context_a.errors (L"Routine has cycles");
			}
		}
		for (auto i (cluster->names.begin ()), j (cluster->names.end ()); i != j; ++i)
		{
			auto existing (routine_mapping.find (i->second));
			assert (existing != routine_mapping.end ());
			result->names [i->first] = existing->second;
		}
		context_a.push (context_a.locals (0));
		context_a.push (context_a.locals (1));
	}
	return valid;
}

void mu::script::synthesizer::operationd::map (boost::shared_ptr <mu::io::debugging::mapping> source_a, boost::shared_ptr <mu::io::debugging::mapping> target_a, boost::shared_ptr <mu::core::node> original_a, boost::shared_ptr <mu::core::node> new_a)
{
	auto existing (source_a->nodes.find (original_a));
	if (existing != source_a->nodes.end ())
	{
		target_a->nodes [new_a] = existing->second;
	}
}