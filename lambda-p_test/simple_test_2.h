#pragma once

#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/shared_ptr.hpp>

#include <iostream>
#include <string>

#include <lambda_p/serialization/simple.h>

namespace lambda_p_test
{
	class simple_test_2
	{
	public:
		simple_test_2 (void);
		~simple_test_2 (void);
		void run ();
	};
}
