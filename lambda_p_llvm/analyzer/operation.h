#pragma once

#include <lambda_p_llvm/analyzer/context.h>
#include <lambda_p_script/fixed.h>

namespace mu
{
	namespace core
	{
		class cluster;
	}
}
namespace lambda_p_io
{
	namespace analyzer
	{
		namespace extensions
		{
			class extensions;
		}
	}
}
namespace lambda_p_script
{
	class routine;
}
namespace lambda_p_llvm
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
		class operation : public lambda_p_script::fixed
		{
		public:
			operation ();
			void operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results) override;
			size_t count () override;
			void add (std::vector <boost::shared_ptr <mu::core::node>> * results, boost::shared_ptr <mu::core::cluster> cluster_a);
			lambda_p_llvm::analyzer::context context;
			boost::shared_ptr <lambda_p_io::analyzer::extensions::extensions> extensions;
		};
	}
}

