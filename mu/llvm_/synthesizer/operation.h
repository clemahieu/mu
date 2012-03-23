#pragma once

#include <mu/script/operation.h>

#include <map>

namespace mu
{
	namespace core
	{
		class expression;
	}
	namespace llvm_
	{
		namespace function
		{
			class node;
		}
		namespace synthesizer
		{
			class operation : public mu::script::operation
			{
			public:
				bool operator () (mu::script::context & context_a) override;
			};
		}
	}
}