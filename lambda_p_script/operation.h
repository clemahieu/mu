#pragma once

#include <mu/core/node.h>
#include <mu/core/segment.h>

#include <boost/shared_ptr.hpp>

#include <vector>

namespace mu
{
	namespace core
	{
		class node;
		namespace errors
		{
			class error_target;
		}
	}
}
namespace lambda_p_script
{
	class operation : public mu::core::node
	{
	public:
		virtual void perform (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results) = 0;
		bool check_count (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, size_t expected);
		void invalid_type (boost::shared_ptr <mu::core::errors::error_target> errors_a, boost::shared_ptr <mu::core::node> node_a, size_t position);
	};
}

