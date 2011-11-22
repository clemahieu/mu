#pragma once

#include <lambda_p/binder/binder.h>

namespace lambda_p_kernel
{
	namespace nodes
	{
		class data;
	}
}
namespace llvm
{
	class Type;
}
namespace lambda_p_llvm
{
	class module;
	class type;
	class value;
	class wstring_binder : public lambda_p::binder::binder
	{
	public:
		void bind (lambda_p::core::statement * statement, lambda_p::binder::list & nodes, lambda_p::errors::error_list & problems) override;
		std::wstring binder_name () override;
		void core (boost::shared_ptr <lambda_p_llvm::module> module, boost::shared_ptr <lambda_p_kernel::nodes::data> data, boost::shared_ptr <lambda_p_llvm::type> type, boost::shared_ptr <lambda_p_llvm::value> & value);
	};
}

