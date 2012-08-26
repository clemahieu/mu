#pragma once

namespace mu
{
    namespace core
    {
        class node;
    }
	namespace script
	{
		namespace extensions
		{
			class node;
		}
		namespace api
		{
			mu::script::extensions::node * core ();
            auto loadb_extension () -> mu::core::node *;
            auto loads_extension () -> mu::core::node *;
            mu::core::node * context_extension (mu::script::extensions::node * core_a);
			mu::script::extensions::node * full ();
		}
	}
}