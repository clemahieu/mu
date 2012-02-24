#pragma once

#include <lambda_p_script/fixed.h>

#include <vector>
#include <map>
#include <set>

#include <boost/shared_ptr.hpp>

namespace mu
{
	namespace core
	{
		class routine;
	}
}
namespace lambda_p_script
{
	class routine;
	namespace cluster
	{
		class node : public lambda_p_script::fixed
		{
		public:
			node ();
			node (std::vector <boost::shared_ptr <lambda_p_script::routine>> routines_a, std::map <boost::shared_ptr <mu::core::routine>, boost::shared_ptr <mu::core::node>> mapping_a);
			node (std::map <std::wstring, boost::shared_ptr <mu::core::routine>> names_a, std::vector <boost::shared_ptr <lambda_p_script::routine>> routines_a, std::map <boost::shared_ptr <mu::core::routine>, boost::shared_ptr <mu::core::node>> mapping_a);
			void operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results) override;
			size_t count () override;
			void remap (std::map <boost::shared_ptr <mu::core::node>, boost::shared_ptr <mu::core::node>> & remap_a);
			std::map <std::wstring, boost::shared_ptr <mu::core::routine>> names;
			std::map <boost::shared_ptr <mu::core::routine>, boost::shared_ptr <mu::core::node>> mapping;
			std::vector <boost::shared_ptr <lambda_p_script::routine>> routines;
		};
	}
}

