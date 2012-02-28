#include "builder.h"

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
#include <mu/script/cluster/get.h>
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

#include <boost/make_shared.hpp>

mu::script_io::builder::builder ()
	: errors (new mu::core::errors::error_list),
	analyzer (boost::bind (&mu::script_io::builder::operator(), this, _1), errors, mu::script_io::extensions ()),
	parser (errors, boost::bind (&mu::io::analyzer::analyzer::input, &analyzer, _1)),
	lexer (errors, boost::bind (&mu::io::parser::parser::operator (), &parser, _1, _2))
{
	set_self ();
}

mu::script_io::builder::builder (boost::shared_ptr <mu::io::analyzer::extensions::extensions> extensions_a)
	: errors (new mu::core::errors::error_list),
	analyzer (boost::bind (&mu::script_io::builder::operator(), this, _1), errors, extensions_a),
	parser (errors, boost::bind (&mu::io::analyzer::analyzer::input, &analyzer, _1)),
	lexer (errors, boost::bind (&mu::io::parser::parser::operator (), &parser, _1, _2))
{
	set_self ();
}

void mu::script_io::builder::set_self ()
{
	auto get (boost::make_shared <mu::script::cluster::get> ());
	self = boost::make_shared <mu::script::closure::single> (get);
	analyzer.extensions->extensions_m [L"."] = boost::make_shared <mu::io::analyzer::extensions::global> (self);
}

void mu::script_io::builder::operator () (boost::shared_ptr <mu::core::cluster> cluster_a)
{
	std::vector <boost::shared_ptr <mu::core::node>> arguments;
	std::vector <boost::shared_ptr <mu::core::node>> results;
	arguments.push_back (cluster_a);
	synthesizer (errors, arguments, results);
	if (results.size () == 1)
	{
		auto result (boost::dynamic_pointer_cast <mu::script::cluster::node> (results [0]));
		assert (result.get () != nullptr);		
		self->closed.push_back (results [0]);
		clusters.push_back (result);
		set_self ();
		fwprintf (stderr, L"");
	}
}

boost::shared_ptr <mu::io::analyzer::extensions::extensions> mu::script_io::extensions ()
{
	auto result (boost::shared_ptr <mu::io::analyzer::extensions::extensions> (new mu::io::analyzer::extensions::extensions));
	result->extensions_m [std::wstring (L"=>")] = boost::make_shared <mu::script_io::lambda> ();
	result->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"->"), boost::make_shared <mu::script_io::lambda_single> ()));
	result->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"#"), boost::make_shared <mu::script::integer::extension> ()));
	result->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"`"), boost::make_shared <mu::script::string::extension> ()));;
	result->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"{"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::values::create> ())));;
	result->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"`a"), boost::make_shared <mu::script::astring::extension> ()));
	result->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"~"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::identity::operation> ())));
	result->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L".()"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::unit::operation> ())));
	result->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L".apply"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::closure::create_single> ())));
	result->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L".ast"), boost::make_shared <mu::script::ast::extension> ()));
	result->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L".create"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::closure::create> ())));	
	result->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L".exec"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::exec::operation> (result))));
	add_loadb (result);	
	add_loads (result);
	result->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L".loadb"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::loadb::operation> ())));
	result->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L".synthesize"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script_io::synthesizer> ())));
	result->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"?"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::closure::hole> ())));
	result->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"script/ast/read_from_file"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::ast::read_from_file> ())));
	result->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"script/ast/merge"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::ast::merge> ())));
	result->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"script/astring/truncate"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::astring::truncate> ())));
	result->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"script/bool_c/create"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::bool_c::create> ())));
	result->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"script/bool_c/equal"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::bool_c::equal> ())));
	result->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"script/chain/operation"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::chain::operation> ())));
	result->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"script/cluster/get_named"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::cluster::get_named> ())));
	result->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"script/extensions/create"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::extensions::create> ())));
	result->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"script/extensions/merge_package"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::extensions::merge_package> ())));
	result->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"script/integer/equal"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::integer::equal> ())));
	result->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"script/integer/subtract"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::integer::subtract> ())));
	result->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"script/print/operation"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::print::operation> ())));
	result->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"script/package/add"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::package::add> ())));
	result->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"script/package/create"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::package::create> ())));
	result->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"script/package/get"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::package::get> ())));
	result->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"script/package/remove"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::package::remove> ())));
	result->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"script/times/operation"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::times::operation> ())));
	return result;
}

void mu::script_io::add_loadb (boost::shared_ptr <mu::io::analyzer::extensions::extensions> result_a)
{
	auto cluster (boost::make_shared <mu::script::cluster::node> ());
	auto routine (boost::make_shared <mu::script::runtime::routine> (cluster));
	auto core_routine (boost::make_shared <mu::core::routine> ());
	cluster->mapping [core_routine] = routine;
	cluster->routines.push_back (routine);
	auto call1 (boost::make_shared <mu::script::runtime::call> (0));
	call1->arguments.push_back (boost::make_shared <mu::script::runtime::parameters> ());
	auto call2 (boost::make_shared <mu::script::runtime::call> (1));
	call2->arguments.push_back (boost::make_shared <mu::script::runtime::constant> (boost::make_shared <mu::script::loadb::operation> ()));
	call2->arguments.push_back (boost::make_shared <mu::script::runtime::reference> (0, 2));
	auto call3 (boost::make_shared <mu::script::runtime::call> (2));
	call3->arguments.push_back (boost::make_shared <mu::script::runtime::constant> (boost::make_shared <mu::script::extensions::merge> ()));
	call3->arguments.push_back (boost::make_shared <mu::script::runtime::reference> (0, 0));
	call3->arguments.push_back (boost::make_shared <mu::script::runtime::reference> (0, 1));
	call3->arguments.push_back (boost::make_shared <mu::script::runtime::reference> (1, 0));
	result_a->extensions_m [std::wstring (L".loadb")] = boost::make_shared <mu::io::analyzer::extensions::global> (routine);
}

void mu::script_io::add_loads (boost::shared_ptr <mu::io::analyzer::extensions::extensions> result_a)
{
	auto cluster (boost::make_shared <mu::script::cluster::node> ());
	auto routine (boost::make_shared <mu::script::runtime::routine> (cluster));
	auto core_routine (boost::make_shared <mu::core::routine> ());
	cluster->mapping [core_routine] = routine;
	cluster->routines.push_back (routine);
	auto call1 (boost::make_shared <mu::script::runtime::call> (0));
	call1->arguments.push_back (boost::make_shared <mu::script::runtime::parameters> ());
	auto call2 (boost::make_shared <mu::script::runtime::call> (1));
	call2->arguments.push_back (boost::make_shared <mu::script::runtime::constant> (boost::make_shared <mu::script::loads::operation> ()));
	call2->arguments.push_back (boost::make_shared <mu::script::runtime::reference> (0, 2));
	auto call3 (boost::make_shared <mu::script::runtime::call> (2));
	call3->arguments.push_back (boost::make_shared <mu::script::runtime::constant> (boost::make_shared <mu::script::extensions::merge_cluster> ()));
	call3->arguments.push_back (boost::make_shared <mu::script::runtime::reference> (0, 0));
	call3->arguments.push_back (boost::make_shared <mu::script::runtime::reference> (0, 1));
	call3->arguments.push_back (boost::make_shared <mu::script::runtime::reference> (1, 0));
	result_a->extensions_m [std::wstring (L".loads")] = boost::make_shared <mu::io::analyzer::extensions::global> (routine);
}