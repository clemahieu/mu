#pragma once

namespace mu
{
	namespace script
	{
		namespace extensions
		{
			class node;
		}
		namespace api
		{
			mu::script::extensions::node * core ();
			mu::script::extensions::node * full ();
		}
	}
}