#include <mu/script_io/builder.h>

#include <boost/bind.hpp>

#include <mu/script/integer/extension.h>
#include <mu/script/string/extension.h>
#include <mu/io/analyzer/extensions/global.h>
#include <mu/script/identity/operation.h>
#include <mu/script/unit/operation.h>
#include <mu/io/analyzer/extensions/global.h>
#include <mu/script/closure/apply.h>
#include <mu/script/closure/create.h>
#include <mu/script/closure/create_single.h>
#include <mu/script/closure/hole.h>
#include <mu/script/bool_c/create.h>
#include <mu/script/bool_c/equal.h>
#include <mu/script/chain/operation.h>
#include <mu/script_io/lambda.h>
#include <mu/script_io/lambda_single.h>
#include <mu/script/integer/equal.h>
#include <mu/script/integer/subtract.h>
#include <mu/script/package/add.h>
#include <mu/script/package/create.h>
#include <mu/script/package/get.h>
#include <mu/script/package/remove.h>
#include <mu/script/times/operation.h>
#include <mu/script/exec/operation.h>
#include <mu/script/astring/extension.h>
#include <mu/script/package/node.h>
#include <mu/script/closure/single.h>
#include <mu/script/package/get_recursive.h>
#include <mu/io/analyzer/extensions/extensions.h>
#include <mu/script/print/operation.h>
#include <mu/core/routine.h>
#include <mu/script/runtime/routine.h>
#include <mu/script/ast/extension.h>
#include <mu/script/cluster/node.h>
#include <mu/script/closure/single.h>
#include <mu/script/values/create.h>
#include <mu/script/ast/read_from_file.h>
#include <mu/script/astring/truncate.h>
#include <mu/script/loads/operation.h>
#include <mu/script/cluster/get_named.h>
#include <mu/script/ast/merge.h>
#include <mu/script/extensions/create.h>
#include <mu/script/extensions/merge_package.h>
#include <mu/script/loadb/operation.h>
#include <mu/script/loads/operation.h>
#include <mu/script/extensions/merge.h>
#include <mu/script/runtime/call.h>
#include <mu/script/runtime/parameters.h>
#include <mu/script/runtime/reference.h>
#include <mu/script/runtime/constant.h>
#include <mu/script/extensions/merge_cluster.h>
#include <mu/script/extensions/node.h>
#include <mu/script/run/operation.h>
#include <mu/script/context.h>
#include <mu/script/debugging/source_info.h>

#include <boost/make_shared.hpp>
#include <boost/bind.hpp>

mu::script_io::builder::builder ()
	: errors (new mu::core::errors::error_list),
	analyzer (boost::bind (&mu::script_io::builder::operator(), this, _1), errors, mu::script_io::extensions ()),
	parser (errors, boost::bind (&mu::io::analyzer::analyzer::input, &analyzer, _1)),
	lexer (errors, boost::bind (&mu::io::parser::parser::operator (), &parser, _1, _2))
{
}

mu::script_io::builder::builder (boost::shared_ptr <mu::io::analyzer::extensions::extensions> extensions_a)
	: errors (new mu::core::errors::error_list),
	analyzer (boost::bind (&mu::script_io::builder::operator(), this, _1), errors, extensions_a),
	parser (errors, boost::bind (&mu::io::analyzer::analyzer::input, &analyzer, _1)),
	lexer (errors, boost::bind (&mu::io::parser::parser::operator (), &parser, _1, _2))
{
}

void mu::script_io::builder::operator () (boost::shared_ptr <mu::core::cluster> cluster_a)
{
	std::vector <boost::shared_ptr <mu::core::node>> arguments;
	std::vector <boost::shared_ptr <mu::core::node>> results;
	arguments.push_back (cluster_a);
	std::vector <boost::shared_ptr <mu::script::debugging::call_info>> stack;
    auto ctx (mu::script::context (errors, arguments, results, stack));
	synthesizer (ctx);
	if (results.size () == 1)
	{
		auto result (boost::dynamic_pointer_cast <mu::script::cluster::node> (results [0]));
		assert (result.get () != nullptr);	
		assert (result->routines.size () == cluster_a->routines.size ());	
		clusters.push_back (result);
	}
}

boost::shared_ptr <mu::io::analyzer::extensions::extensions> mu::script_io::extensions ()
{
	auto result (boost::shared_ptr <mu::io::analyzer::extensions::extensions> (new mu::io::analyzer::extensions::extensions));

	result->extensions_m [std::wstring (L"self")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::extensions::node> (result));
	result->extensions_m [std::wstring (L"exec")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::exec::operation> (result));
	result->extensions_m [std::wstring (L"run")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::run::operation> ());
	add_loadb (result);	
	add_loads (result);
	result->extensions_m [std::wstring (L"context")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::extensions::create> ());	
	result->extensions_m [std::wstring (L"~")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::identity::operation> ());
	result->extensions_m [std::wstring (L"`")] = boost::make_shared <mu::script::string::extension> ();
	result->extensions_m [std::wstring (L".ast")] = boost::make_shared <mu::script::ast::extension> ();
	result->extensions_m [std::wstring (L"#")] = boost::make_shared <mu::script::integer::extension> ();
	result->extensions_m [std::wstring (L"=>")] = boost::make_shared <mu::script_io::lambda> ();
	result->extensions_m [std::wstring (L"->")] = boost::make_shared <mu::script_io::lambda_single> ();
	result->extensions_m [std::wstring (L"{")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::values::create> ());
	result->extensions_m [std::wstring (L"`a")] = boost::make_shared <mu::script::astring::extension> ();
	result->extensions_m [std::wstring (L".()")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::unit::operation> ());
	result->extensions_m [std::wstring (L".apply")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::closure::create_single> ());
	result->extensions_m [std::wstring (L".create")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::closure::create> ());	
	result->extensions_m [std::wstring (L".synthesize")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script_io::synthesizer> ());
	return result;
}

void mu::script_io::add_loadb (boost::shared_ptr <mu::io::analyzer::extensions::extensions> result_a)
{
	auto extensions (boost::make_shared <mu::io::analyzer::extensions::extensions> ());
	extensions->extensions_m [std::wstring (L"merge")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::extensions::merge> ());
	extensions->extensions_m [std::wstring (L"loadb")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::loadb::operation> ());
	mu::script_io::builder builder (extensions);
	mu::io::source source (boost::bind (&mu::io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[merge cluster prefix [loadb file] [:~; cluster prefix file]]");
	source ();
	assert (builder.clusters.size () == 1);
	assert (builder.clusters [0]->routines.size () == 1);
	result_a->extensions_m [std::wstring (L"loadb")] = boost::make_shared <mu::io::analyzer::extensions::global> (builder.clusters [0]->routines [0]);
}

void mu::script_io::add_loads (boost::shared_ptr <mu::io::analyzer::extensions::extensions> result_a)
{
	auto extensions (boost::make_shared <mu::io::analyzer::extensions::extensions> ());
	extensions->extensions_m [std::wstring (L"merge")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::extensions::merge> ());
	auto closure (boost::make_shared <mu::script::closure::single> (boost::make_shared <mu::script::loads::operation> ()));
	closure->closed.push_back (boost::make_shared <mu::script::extensions::node> (result_a));
	extensions->extensions_m [std::wstring (L"loads")] = boost::make_shared <mu::io::analyzer::extensions::global> (closure);
	mu::script_io::builder builder (extensions);
	mu::io::source source (boost::bind (&mu::io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[merge cluster prefix [loads file] [:~; cluster prefix file]]");
	source ();
	assert (builder.clusters.size () == 1);
	assert (builder.clusters [0]->routines.size () == 1);
	result_a->extensions_m [std::wstring (L"loads")] = boost::make_shared <mu::io::analyzer::extensions::global> (builder.clusters [0]->routines [0]);
}