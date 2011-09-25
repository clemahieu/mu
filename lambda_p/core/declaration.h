#pragma once

#include <iostream>

#include <lambda_p/core/node.h>

namespace lambda_p
{
    namespace serialization
    {
        template <typename> class simple;
    }
	namespace core
	{
		class routine;
		class declaration : public node
		{
            template <typename> friend class ::lambda_p::serialization::simple;
		public:
			declaration ();
			~declaration (void);
			node_id node_type () const;
			::std::wstring node_type_name () const;
		};
	}
}

