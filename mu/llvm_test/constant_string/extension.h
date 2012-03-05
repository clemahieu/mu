#pragma once

#include <boost/shared_ptr.hpp>

namespace mu
{
	namespace core
	{
		class cluster;
	}
	namespace llvm_test
	{
		namespace constant_string
		{
			class extension
			{
			public:
				void run ();
				void run_1 ();
				void junk (boost::shared_ptr <mu::core::cluster> cluster_a);
			};
		}
	}
	}

