#pragma once

#include <mu/core/errors/error_list.h>

#include <vector>

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
			void operator () (mu::core::cluster * cluster_a);
			std::vector <mu::core::cluster *> clusters;
			mu::core::errors::error_list errors;
		};
	}
}
