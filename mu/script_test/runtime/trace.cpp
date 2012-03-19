#include <mu/script_test/runtime/trace.h>

#include <mu/script/closure/single.h>
#include <mu/script/identity/operation.h>
#include <mu/script/fail/operation.h>
#include <mu/core/errors/error_list.h>
#include <mu/script_runtime/context.h>
#include <mu/script_io/builder.h>
#include <mu/io/source.h>
#include <mu/io/analyzer/extensions/extensions.h>
#include <mu/io/analyzer/extensions/global.h>
#include <mu/script/cluster/node.h>
#include <mu/script/runtime/routine.h>
#include <mu/script/runtime/stacktrace_error.h>
#include <mu/script/runtime/trace_target.h>
#include <mu/script/debugging/binary_info.h>
#include <mu/script/debugging/source_info.h>

#include <boost/make_shared.hpp>
#include <boost/bind.hpp>

void mu::script_test::runtime::trace_target::run ()
{
    //run_1 ();
    //run_2 ();
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
	std::vector <boost::shared_ptr <mu::script::debugging::call_info>> stack;
	auto ctx (mu::script::context (errors, a1, r1, stack));
	ctx.errors = boost::make_shared <mu::script::runtime::trace_target> (ctx, errors);
	(*routine) (ctx);
	assert (!errors->errors.empty ());
	auto error (boost::dynamic_pointer_cast <mu::script::runtime::stacktrace_error> (errors->errors [0]));
	assert (error.get () != nullptr);
	assert (error->stack.size () == 6);
	auto e1 (boost::dynamic_pointer_cast <mu::script::debugging::source_info> (error->stack [0]));
	assert (e1.get () != nullptr);
	assert (e1->context == mu::io::debugging::context (1, 1, 0, 1, 3, 2));
	auto e2 (boost::dynamic_pointer_cast <mu::script::debugging::source_info> (error->stack [1]));
	assert (e2.get () != nullptr);
	assert (e2->context == mu::io::debugging::context (1, 4, 3, 1, 9, 8));
	auto e3 (boost::dynamic_pointer_cast <mu::script::debugging::source_info> (error->stack [2]));
	assert (e3.get () != nullptr);
	assert (e3->context == mu::io::debugging::context (1, 10, 9, 1, 15, 14));
	auto e4 (boost::dynamic_pointer_cast <mu::script::debugging::source_info> (error->stack [3]));
	assert (e4.get () != nullptr);
	assert (e4->context == mu::io::debugging::context (1, 16, 15, 1, 21, 20));
	auto e5 (boost::dynamic_pointer_cast <mu::script::debugging::source_info> (error->stack [4]));
	assert (e5.get () != nullptr);
	assert (e5->context == mu::io::debugging::context (1, 22, 21, 1, 30, 29));
	auto e6 (boost::dynamic_pointer_cast <mu::script::debugging::binary_info> (error->stack[5]));
	assert (e6.get () != nullptr);
	assert (e6->type == typeid (mu::script::fail::operation));
}

void mu::script_test::runtime::trace_target::run_2 ()
{
	auto errors (boost::make_shared <mu::core::errors::error_list> ());
	std::vector <boost::shared_ptr <mu::core::node>> a1;
	std::vector <boost::shared_ptr <mu::core::node>> r1;
	auto extensions (boost::make_shared <mu::io::analyzer::extensions::extensions> ());
	auto identity (boost::make_shared <mu::script::identity::operation> ());
	extensions->extensions_m [std::wstring (L"id")] = boost::make_shared <mu::io::analyzer::extensions::global> (identity);
	auto fail (boost::make_shared <mu::script::fail::operation> ());
	extensions->extensions_m [std::wstring (L"fail")] = boost::make_shared <mu::io::analyzer::extensions::global> (fail);
	mu::script_io::builder builder (extensions);
	mu::io::source source (boost::bind (&mu::io::lexer::lexer::operator (), &builder.lexer, _1));
	source (L"[id [a]][id [b];;a][id [c];;b][id [d];;c][fail;;d]");
	source ();
	assert (builder.errors->errors.empty ());
	auto cluster (builder.clusters [0]);
	auto routine (cluster->routines [0]);
	std::vector <boost::shared_ptr <mu::script::debugging::call_info>> stack;
	auto ctx (mu::script::context (errors, a1, r1, stack));
	ctx.errors = boost::make_shared <mu::script::runtime::trace_target> (ctx, errors);
	(*routine) (ctx);
	assert (!errors->errors.empty ());
	auto error (boost::dynamic_pointer_cast <mu::script::runtime::stacktrace_error> (errors->errors [0]));
	assert (error.get () != nullptr);
	assert (error->stack.size () == 6);
	auto e1 (boost::dynamic_pointer_cast <mu::script::debugging::source_info> (error->stack [0]));
	assert (e1.get () != nullptr);
	assert (e1->context == mu::io::debugging::context (1, 5, 4, 1, 7, 6));
	auto e2 (boost::dynamic_pointer_cast <mu::script::debugging::source_info> (error->stack [1]));
	assert (e2.get () != nullptr);
	assert (e2->context == mu::io::debugging::context (1, 13, 12, 1, 15, 14));
	auto e3 (boost::dynamic_pointer_cast <mu::script::debugging::source_info> (error->stack [2]));
	assert (e3.get () != nullptr);
	assert (e3->context == mu::io::debugging::context (1, 24, 23, 1, 26, 25));
	auto e4 (boost::dynamic_pointer_cast <mu::script::debugging::source_info> (error->stack [3]));
	assert (e4.get () != nullptr);
	assert (e4->context == mu::io::debugging::context (1, 35, 34, 1, 37, 36));
	auto e5 (boost::dynamic_pointer_cast <mu::script::debugging::source_info> (error->stack [4]));
	assert (e5.get () != nullptr);
	assert (e5->context == mu::io::debugging::context (1, 42, 41, 1, 50, 49));
	auto e6 (boost::dynamic_pointer_cast <mu::script::debugging::binary_info> (error->stack[5]));
	assert (e6.get () != nullptr);
	assert (e6->type == typeid (mu::script::fail::operation));
}