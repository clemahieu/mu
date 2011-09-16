#pragma once

#include <lambda_p/binder/node_instance.h>

#include <string>

namespace lambda_p
{
	namespace binder
	{
		class string_instance : public ::lambda_p::binder::node_instance
		{
		public:
			string_instance (::std::wstring string_a);
			~string_instance (void);
			void operator () ();
			::std::wstring string;
		};
	}
}

