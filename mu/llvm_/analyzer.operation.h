#pragma once

#include <mu/llvm_/analyzer.context.h>
#include <mu/script/fixed.h>

namespace llvm
{
	class Function;
}
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
		namespace function_address
		{
			class operation;
		}
		namespace function
		{
			class node;
		}
		namespace function_type
		{
			class node;
		}
		namespace analyzer
		{
			class reference;
			class operation : public mu::script::fixed
			{
			public:
				operation ();
				void operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results) override;
				size_t count () override;
				void finish_types (boost::shared_ptr <mu::core::errors::error_target> errors_a, std::vector <std::pair <boost::shared_ptr <mu::llvm_::function::node>, boost::shared_ptr <mu::llvm_::function_type::node>>> * functions, std::vector <boost::shared_ptr <mu::llvm_::function::node>> * types, boost::shared_ptr <mu::core::cluster> cluster_a);
				void finish_bodies (boost::shared_ptr <mu::core::errors::error_target> errors_a, std::vector <boost::shared_ptr <mu::core::node>> * results, std::vector <std::pair <boost::shared_ptr <mu::llvm_::function::node>, boost::shared_ptr <mu::llvm_::function_type::node>>> * functions, boost::shared_ptr <mu::core::cluster> cluster_a);
				mu::llvm_::analyzer::context context;
				boost::shared_ptr <mu::llvm_::analyzer::reference> reference_m;
				boost::shared_ptr <mu::io::analyzer::extensions::extensions> extensions;
			};
		}
	}
}

