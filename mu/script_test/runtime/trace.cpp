#include <mu/script_test/runtime/trace.h>

#include <mu/script/closure/single.h>
#include <mu/script/identity/operation.h>
#include <mu/script/fail/operation.h>
#include <mu/core/errors/error_list.h>
#include <mu/script/context.h>
#include <mu/script_io/builder.h>
#include <mu/io/source.h>
#include <mu/io/analyzer/extensions/extensions.h>
#include <mu/io/analyzer/extensions/global.h>
#include <mu/script/cluster/node.h>
#include <mu/script/runtime/routine.h>
#include <mu/script/runtime/stacktrace_error.h>
#include <mu/script/runtime/trace_target.h>
#include <mu/script/debugging/flat_mapping.h>

#include <boost/make_shared.hpp>
#include <boost/bind.hpp>

void mu::script_test::runtime::trace_target::run ()
{
    run_1 ();
}

void mu::script_test::runtime::trace_target::run_1 ()
{
	auto errors (boost::make_shared <mu::core::errors::error_list> ());
	std::vector <boost::shared_ptr <mu::core::node>> a1;
	std::vector <boost::shared_ptr <mu::core::node>> r1;
	auto extensions (boost::make_shared <mu::io::analyzer::extensions::extensions> ());
	auto fail (boost::make_shared <mu::script::fail::operation> ());
	extensions->extensions_m [std::wstring (L"fail")] = boost::make_shared <mu::io::analyzer::extensions::global> (fail);
	mu::script_io::builder builder (extensions);
	mu::io::source source (boost::bind (&mu::io::lexer::lexer::operator (), &builder.lexer, _1));
	source (L"[a][b;;a][c;;b][d;;c][fail;;d]");
	source ();
	assert (builder.errors->errors.empty ());
	auto cluster (builder.clusters [0]);
	auto routine (cluster->routines [0]);
	std::vector <boost::shared_ptr <mu::script::operation>> stack;
	auto ctx (mu::script::context (errors, a1, r1, stack));
	mu::script::debugging::flat_mapping mapping;
	mapping.map [fail] = std::wstring (L"mu::script::fail::operation");
	ctx.errors = boost::make_shared <mu::script::runtime::trace_target> (ctx, mapping, errors);
	(*routine) (ctx);
	assert (!errors->errors.empty ());
	auto error (boost::dynamic_pointer_cast <mu::script::runtime::stacktrace_error> (errors->errors [0].first));
	assert (error.get () != nullptr);
	assert (error->stack.size () == 5);
}