#include "node.h"

#include <lambda_p/routine.h>
#include <lambda_p_llvm/value/node.h>

void lambda_p_llvm::cluster::node::set_names (std::map <std::wstring, boost::shared_ptr <lambda_p::routine>> & names_a, std::map <boost::shared_ptr <lambda_p::node>, boost::shared_ptr <lambda_p::node>> & remap_a)
{
	for (auto i (names_a.begin ()), j (names_a.end ()); i != j; ++i)
	{
		auto existing (remap_a.find (i->second));
		if (existing != remap_a.end ())
		{
			auto value (boost::static_pointer_cast <lambda_p_llvm::value::node> (existing->second));
			names [i->first] = value;
		}
	}
}