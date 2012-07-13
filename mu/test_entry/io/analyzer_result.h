#pragma once

#include <vector>

#include <boost/shared_ptr.hpp>

namespace mu
{
	namespace core
	{
		class cluster;
		namespace errors
		{
			class error_list;
		}
	}
	namespace io
	{
		namespace debugging
		{
			class mapping;
		}
	}
	namespace io_test
	{
		class analyzer_result
		{
		public:
			analyzer_result ();
			void operator () (boost::shared_ptr <mu::core::cluster> cluster_a);
			std::vector <boost::shared_ptr <mu::core::cluster>> clusters;
			mu::core::errors::error_list * errors;
		};
	}
}