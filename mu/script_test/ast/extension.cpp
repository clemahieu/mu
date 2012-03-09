#include "extension.h"

#include <mu/core/expression.h>
#include <mu/script/runtime/routine.h>
#include <mu/script_io/builder.h>
#include <mu/io/ast/expression.h>
#include <mu/io/ast/identifier.h>
#include <mu/io/ast/cluster.h>
#include <mu/core/errors/error_list.h>
#include <mu/script/cluster/node.h>

#include <boost/bind.hpp>

void mu::script_test::ast::extension::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
}

void mu::script_test::ast::extension::run_1 ()
{
	mu::script_io::builder builder;
	mu::io::source source (boost::bind (&mu::io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[~ .ast []]");
	source ();
	assert (builder.errors->errors.empty ());
	assert (builder.clusters.size () == 1);
	auto cluster (builder.clusters [0]);
	assert (cluster->routines.size () == 1);
	auto routine (cluster->routines [0]);
	std::vector <boost::shared_ptr <mu::core::node>> a1;
	std::vector <boost::shared_ptr <mu::core::node>> r1;
    auto ctx (mu::script::context (builder.errors, a1, r1));
	(*routine) (ctx);
	assert (r1.size () == 1);
	auto cl (boost::dynamic_pointer_cast <mu::io::ast::cluster> (r1 [0]));
	assert (cl.get () != nullptr);
	assert (cl->expressions.size () == 0);
}

void mu::script_test::ast::extension::run_2 ()
{
	mu::script_io::builder builder;
	mu::io::source source (boost::bind (&mu::io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[~ .ast thing]");
	source ();
	assert (!builder.errors->errors.empty ());
	assert (builder.clusters.empty ());
}

void mu::script_test::ast::extension::run_3 ()
{
	mu::script_io::builder builder;
	mu::io::source source (boost::bind (&mu::io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[~ .ast [[]]]");
	source ();
	assert (builder.errors->errors.empty ());
	assert (builder.clusters.size () == 1);
	auto cluster (builder.clusters [0]);
	assert (cluster->routines.size () == 1);
	auto routine (cluster->routines [0]);
	std::vector <boost::shared_ptr <mu::core::node>> a1;
	std::vector <boost::shared_ptr <mu::core::node>> r1;
    auto ctx (mu::script::context (builder.errors, a1, r1));
	(*routine) (ctx);
	assert (r1.size () == 1);
	auto cl (boost::dynamic_pointer_cast <mu::io::ast::cluster> (r1 [0]));
	assert (cl.get () != nullptr);
	assert (cl->expressions.size () == 1);
	auto expression (cl->expressions [0]);
}