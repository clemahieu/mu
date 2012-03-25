#pragma once

#include <mu/script/operation.h>

namespace mu
{
	namespace core
	{
		class cluster;
		class routine;
		class expression;
		class reference;
	}
	namespace script
	{
		namespace cluster
		{
			class remap : public mu::script::operation
			{
			public:
				bool operator () (mu::script::context & context_a) override;
				void operator () (boost::shared_ptr <mu::core::cluster> source, boost::shared_ptr <mu::core::cluster> target);
				void operator () (boost::shared_ptr <mu::core::routine> source, boost::shared_ptr <mu::core::routine> target);
				void operator () (boost::shared_ptr <mu::core::expression> source, boost::shared_ptr <mu::core::expression> target);
				void operator () (boost::shared_ptr <mu::core::reference> source, boost::shared_ptr <mu::core::reference> target);
				virtual boost::shared_ptr <mu::core::node> operator () (boost::shared_ptr <mu::core::node> node_a) = 0;
			};
		}
	}
}