#pragma once

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	class cluster;
}
namespace lambda_p_llvm_test
{
	namespace constant_string
	{
		class extension
		{
		public:
			void run ();
			void run_1 ();
			void junk (boost::shared_ptr <lambda_p::cluster> cluster_a);
		};
	}
}

