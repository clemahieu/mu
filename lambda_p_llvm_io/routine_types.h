#pragma once

#include <boost/shared_ptr.hpp>

#include <map>

namespace lambda_p
{
	class routine;
	class expression;
	class node;
	namespace errors
	{
		class error_target;
	}
}
namespace lambda_p_llvm
{
	namespace module
	{
		class node;
	}
}
namespace lambda_p_llvm_io
{
	class cluster_types;
	class routine_types
	{
	public:
		routine_types (boost::shared_ptr <lambda_p::errors::error_target> errors_a, boost::shared_ptr <lambda_p::routine> routine_a, boost::shared_ptr <lambda_p_llvm::module::node> module_a, lambda_p_llvm_io::cluster_types & cluster_a);
		std::map <boost::shared_ptr <lambda_p::expression>, std::vector <boost::shared_ptr <lambda_p::node>>> values;
		lambda_p_llvm_io::cluster_types & cluster;
		boost::shared_ptr <lambda_p::routine> routine;
		boost::shared_ptr <lambda_p_llvm::module::node> module;
		bool type_set;
	};
}

