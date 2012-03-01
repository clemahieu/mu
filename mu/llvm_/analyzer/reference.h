#pragma once

#include <mu/script_io/reference.h>

#include <map>

namespace mu
{
	namespace core
	{
		class routine;
	}
	namespace script
	{
		namespace runtime
		{
			class routine;
		}
	}
	namespace llvm_
	{
		namespace function
		{
			class node;
		}
		namespace analyzer
		{
			class reference : public mu::script_io::reference
			{
			public:
				boost::shared_ptr <mu::core::node> operator () (boost::shared_ptr <mu::core::routine> routine_a) override;				
				std::map <boost::shared_ptr <mu::core::routine>, boost::shared_ptr <mu::script::runtime::routine>> script_mapping;
				std::map <boost::shared_ptr <mu::script::runtime::routine>, boost::shared_ptr <mu::llvm_::function::node>> function_mapping;
			};
		}
	}
}

