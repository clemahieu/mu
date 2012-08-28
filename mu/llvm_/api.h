#pragma once

namespace mu
{
	namespace script
	{
		namespace parser_scope
		{
			class node;
		}
		namespace values
		{
			class operation;
		}
	}
	namespace llvm_
	{
		namespace api
		{
			void binding (mu::script::parser_scope::node *& result_a, mu::script::values::operation *& context_a);
		};
	}
}

