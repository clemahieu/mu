#pragma once

#include <mu/llvm_/analyzer/context.h>
#include <mu/script/operation.h>

#include <vector>

namespace llvm
{
	class Function;
}
namespace mu
{
	namespace core
	{
		class cluster;
        namespace errors
        {
            class error_target;
        }
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
		namespace debugging
		{
			class mapping;
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
			class operation : public mu::script::operation
			{
			public:
				operation ();
				bool operator () (mu::script::context & context_a) override;
				void finish_types (mu::script::context & context_a, bool & valid_a, std::vector <std::pair <boost::shared_ptr <mu::llvm_::function::node>, boost::shared_ptr <mu::llvm_::function_type::node>>> & functions, std::vector <boost::shared_ptr <mu::llvm_::function::node>> & types, boost::shared_ptr <mu::core::cluster> cluster_a, boost::shared_ptr <mu::io::debugging::mapping> cluster_info_a);
				void finish_bodies (mu::script::context & context_a, bool & valid_a, std::vector <std::pair <boost::shared_ptr <mu::llvm_::function::node>, boost::shared_ptr <mu::llvm_::function_type::node>>> & functions, boost::shared_ptr <mu::core::cluster> cluster_a, boost::shared_ptr <mu::io::debugging::mapping> cluster_info_a);
				mu::llvm_::analyzer::context context;
				//boost::shared_ptr <mu::llvm_::analyzer::reference> reference_m;
				boost::shared_ptr <mu::io::analyzer::extensions::extensions> extensions;
			};
		}
	}
}

