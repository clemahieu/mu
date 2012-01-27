#include "node.h"

#include <lambda_p_io/ast/expression.h>
#include <lambda_p/errors/error_target.h>
#include <lambda_p_io/analyzer/analyzer.h>
#include <lambda_p/routine.h>

#include <boost/bind.hpp>

void lambda_p_script::analyzer::node::operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <lambda_p_io::ast::expression> (parameters [0]));
	if (one.get () != nullptr)
	{
		std::vector <boost::shared_ptr <lambda_p::node>> * results_l (&results);
		lambda_p_io::analyzer::analyzer analyzer (boost::bind (&lambda_p_script::analyzer::node::add, this, results_l, _1), errors_a);
		analyzer.input (one);
	}
	else
	{
		invalid_type (errors_a, parameters [0], 0);
	}
}

size_t lambda_p_script::analyzer::node::count ()
{
	return 1;
}

void lambda_p_script::analyzer::node::add (std::vector <boost::shared_ptr <lambda_p::node>> * results, boost::shared_ptr <lambda_p::cluster> cluster_a)
{
	results->push_back (cluster_a);
}