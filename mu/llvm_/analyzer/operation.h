#pragma once

#include <mu/llvm_/analyzer/context.h>
#include <mu/script/fixed.h>

namespace mu
{
	namespace core
	{
		class cluster;
	}
	namespace io
	{
		namespace analyzer
		{
			namespace extensions
			{
				class extensions;
			}
		}
	}
	namespace llvm_
	{
		namespace context
		{
			class node;
		}
		namespace instruction
		{
			class node;
		}
		namespace analyzer
		{
			class operation : public mu::script::fixed
			{
			public:
				operation ();
				void operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results) override;
				size_t count () override;
				void add (std::vector <boost::shared_ptr <mu::core::node>> * results, boost::shared_ptr <mu::core::cluster> cluster_a);
				mu::llvm_::analyzer::context context;
				boost::shared_ptr <mu::io::analyzer::extensions::extensions> extensions;
			};
		}
	}
}

