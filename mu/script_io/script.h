#pragma once

#include <mu/script_io/reference.h>

namespace mu
{
	namespace script_io
	{
		class cluster;
		class script : public mu::script_io::reference
		{
		public:
			script (mu::script_io::cluster & cluster_a);
			boost::shared_ptr <mu::core::node> operator () (boost::shared_ptr <mu::core::routine> routine_a) override;
			mu::script_io::cluster & cluster;
		};
	}
}

