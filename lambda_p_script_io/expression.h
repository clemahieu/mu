#pragma once

#include <core/visitor.h>

#include <boost/shared_ptr.hpp>

#include <map>

namespace lambda_p
{
	class expression;
	class node;
	class routine;
}
namespace lambda_p_script
{
	class call;
	class routine;
	namespace cluster
	{
		class node;
	}
}
namespace lambda_p_script_io
{
	class generator;
	class expression : public mu::core::visitor
	{
	public:
		expression (boost::shared_ptr <lambda_p_script::cluster::node> cluster_a, std::map <boost::shared_ptr <mu::core::expression>, size_t> & reservations_a, boost::shared_ptr <lambda_p_script::call> call_a, boost::shared_ptr <mu::core::node> node_a);
		void operator () (mu::core::expression * expression_a) override;
		void operator () (mu::core::parameters * parameters_a) override;
		void operator () (mu::core::reference * reference_a) override;
		void operator () (mu::core::node * node_a) override;
		void operator () (mu::core::routine * routine_a) override;
		boost::shared_ptr <mu::core::node> node;
		boost::shared_ptr <lambda_p_script::call> call_m;
		boost::shared_ptr <lambda_p_script::cluster::node> cluster;
		std::map <boost::shared_ptr <mu::core::expression>, size_t> & reservations;
	};
}

