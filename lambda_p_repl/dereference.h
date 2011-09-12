#pragma once

#include <boost/shared_ptr.hpp>

#include <lambda_p/core/node.h>
#include <lambda_p/binder/node_instance.h>

#include <map>

namespace lambda_p_repl
{
	class dereference
	{
	public:
		dereference (void);
		~dereference (void);
		::std::map < ::std::wstring, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > nodes;
	};
}

