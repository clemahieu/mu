#include "operation.h"

#include <mu/script/times/operation.h>
#include <mu/core/errors/error_list.h>
#include <mu/script/integer/subtract.h>
#include <mu/script/integer/node.h>
#include <mu/script_io/builder.h>
#include <mu/io/source.h>
#include <mu/script/runtime/routine.h>
#include <mu/script/cluster/node.h>
#include <mu/script/context.h>

#include <boost/bind.hpp>

void mu::script_test::times::operation::run ()
{
	run_1 ();
	run_2 ();
}

void mu::script_test::times::operation::run_1 ()
{
	auto errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	mu::script::times::operation times;
	std::vector <boost::shared_ptr <mu::core::node>> arguments;
	auto n1 (boost::shared_ptr <mu::core::node> (new mu::script::integer::node (0)));
	arguments.push_back (n1);
	auto n2 (boost::shared_ptr <mu::core::node> (new mu::script::integer::subtract));
	arguments.push_back (n2);
	auto n3 (boost::shared_ptr <mu::core::node> (new mu::script::integer::node (5)));
	arguments.push_back (n3);
	auto n4 (boost::shared_ptr <mu::core::node> (new mu::script::integer::node (1)));
	arguments.push_back (n4);
	std::vector <boost::shared_ptr <mu::core::node>> results;
	std::vector <std::type_info const *> stack;
	std::vector <mu::core::context> context_stack;
    auto ctx (mu::script::context (errors, arguments, results, stack, context_stack));
	times (ctx);
	assert (errors->errors.empty ());
	assert (results.size () == 2);
	assert (results [0] == n3);
	assert (results [1] == n4);
}

void mu::script_test::times::operation::run_2 ()
{
	mu::script_io::builder builder;
	mu::io::source source (boost::bind (&mu::io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[[:~; subtract number amount] ~ subtract [subtract number amount] amount]");
	source ();
	assert (builder.errors->errors.empty ());
	mu::script::times::operation times;
	std::vector <boost::shared_ptr <mu::core::node>> arguments;
	assert (builder.clusters.size () == 1);
	auto cluster (builder.clusters [0]);
	assert (cluster->routines.size () == 1);
	auto n1 (boost::shared_ptr <mu::core::node> (new mu::script::integer::node (2)));
	arguments.push_back (n1);
	auto n2 (cluster->routines [0]);
	arguments.push_back (n2);
	auto n3 (boost::shared_ptr <mu::core::node> (new mu::script::integer::subtract));
	arguments.push_back (n3);
	auto n4 (boost::shared_ptr <mu::core::node> (new mu::script::integer::node (5)));
	arguments.push_back (n4);
	auto n5 (boost::shared_ptr <mu::core::node> (new mu::script::integer::node (1)));
	arguments.push_back (n5);
	std::vector <boost::shared_ptr <mu::core::node>> results;
	std::vector <std::type_info const *> stack;
	std::vector <mu::core::context> context_stack;
    auto ctx (mu::script::context (builder.errors, arguments, results, stack, context_stack));
	times (ctx);
	assert (builder.errors->errors.empty ());
	assert (results.size () == 3);
	auto r1 (boost::dynamic_pointer_cast <mu::script::integer::subtract> (results [0]));
	assert (r1.get () != nullptr);
	auto r2 (boost::dynamic_pointer_cast <mu::script::integer::node> (results [1]));
	assert (r2.get () != nullptr);
	assert (r2->value == 3);
	auto r3 (boost::dynamic_pointer_cast <mu::script::integer::node> (results [2]));
	assert (r3.get () != nullptr);
	assert (r3->value == 1);
}