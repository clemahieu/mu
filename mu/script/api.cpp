#include <mu/script/api.h>

#include <mu/io/keywording_extensions.h>
#include <mu/script/extensions_node.h>
#include <mu/script/string_extension.h>
#include <mu/script/astring_extension.h>
#include <mu/script/integer_extension.h>
#include <mu/io/keywording_global.h>
#include <mu/script/identity_operation.h>
#include <mu/script/astring_truncate.h>
#include <mu/script/bool_c_create.h>
#include <mu/script/bool_c_equal.h>
#include <mu/script/chain_operation.h>
#include <mu/script/extensions_create.h>
#include <mu/script/extensions_merge_package.h>
#include <mu/script/integer_equal.h>
#include <mu/script/integer_subtract.h>
#include <mu/script/print_operation.h>
#include <mu/script/package_add.h>
#include <mu/script/package_create.h>
#include <mu/script/package_get.h>
#include <mu/script/package_remove.h>
#include <mu/script/times_operation.h>
#include <mu/script/string_extension.h>
#include <mu/script/astring_extension.h>
#include <mu/script/integer_extension.h>
#include <mu/script/closure_create_single.h>
#include <mu/script/loadb_operation.h>
#include <mu/script/loads_operation.h>
#include <mu/script/extensions_create.h>
#include <mu/script/runtime_routine.h>
#include <mu/script/runtime_expression.h>
#include <mu/script/extensions_merge.h>
#include <mu/script/runtime_reference.h>
#include <mu/script/string_node.h>
#include <mu/script/runtime_fixed.h>
#include <mu/script/runtime_parameter.h>
#include <mu/script/cluster_to_extensions.h>

#include <gc_cpp.h>

auto mu::script::api::core () -> boost::tuple <mu::script::extensions::node *, mu::map <mu::string, mu::core::node *>>
{
    boost::tuple <mu::script::extensions::node *, mu::map <mu::string, mu::core::node *>> result;
    boost::get <0> (result) = new (GC) mu::script::extensions::node;
    auto & extensions (*boost::get <0> (result)->extensions);
    auto & map (boost::get <1> (result));
	extensions.add <mu::script::string::extension> (mu::string (U"`"));
	extensions.add <mu::script::astring::extension>(mu::string (U"a`"));
	extensions.add <mu::script::integer::extension> (mu::string (U"#"));
    map [mu::string (U"~")] = new (GC) mu::script::identity::operation;
    map [mu::string (U"context")] = context_extension (boost::get <0> (result));
    map [mu::string (U"loadb")] = loadb_extension ();
    map [mu::string (U"loads")] = loads_extension ();
	return result;
}

auto mu::script::api::loadb_extension () -> mu::core::node *
{
    auto result (new (GC) mu::script::runtime::routine);
    auto expression1 (new (GC) mu::script::runtime::expression);
    expression1->dependencies.push_back (new (GC) mu::script::runtime::fixed (new (GC) mu::script::loadb::operation));
    expression1->dependencies.push_back (new (GC) mu::script::runtime::parameter (2));
    result->expressions.push_back (expression1);
    auto expression2 (new (GC) mu::script::runtime::expression);
    expression2->dependencies.push_back (new (GC) mu::script::runtime::fixed (new (GC) mu::script::extensions::merge));
    expression2->dependencies.push_back (new (GC) mu::script::runtime::parameter (0));
    expression2->dependencies.push_back (new (GC) mu::script::runtime::parameter (1));
    expression2->dependencies.push_back (new (GC) mu::script::runtime::reference (expression1));
    result->expressions.push_back (expression2);
    return result;
}

auto mu::script::api::loads_extension () -> mu::core::node *
{
    auto result (new (GC) mu::script::runtime::routine);
    auto expression1 (new (GC) mu::script::runtime::expression);
    expression1->dependencies.push_back (new (GC) mu::script::runtime::fixed (new (GC) mu::script::loads::operation));
    expression1->dependencies.push_back (new (GC) mu::script::runtime::parameter (2));
    result->expressions.push_back (expression1);
    auto expression2 (new (GC) mu::script::runtime::expression);
    expression2->dependencies.push_back (new (GC) mu::script::runtime::fixed (new (GC) mu::script::cluster::to_extensions));
    expression2->dependencies.push_back (new (GC) mu::script::runtime::reference (expression1));
    result->expressions.push_back (expression2);
    auto expression3 (new (GC) mu::script::runtime::expression);
    expression3->dependencies.push_back (new (GC) mu::script::runtime::fixed (new (GC) mu::script::extensions::merge));
    expression3->dependencies.push_back (new (GC) mu::script::runtime::parameter (0));
    expression3->dependencies.push_back (new (GC) mu::script::runtime::parameter (1));
    expression3->dependencies.push_back (new (GC) mu::script::runtime::reference (expression2));
    result->expressions.push_back (expression3);
    return result;
}

auto mu::script::api::context_extension (mu::script::extensions::node * core_a) -> mu::core::node *
{
    auto result (new (GC) mu::script::runtime::routine);
    auto expression1 (new (GC) mu::script::runtime::expression);
    expression1->dependencies.push_back (new (GC) mu::script::extensions::create);
    result->expressions.push_back (expression1);
    auto expression2 (new (GC) mu::script::runtime::expression);
    expression2->dependencies.push_back (new (GC) mu::script::runtime::fixed (new (GC) mu::script::extensions::merge));
    expression2->dependencies.push_back (new (GC) mu::script::runtime::reference (expression1));
    expression2->dependencies.push_back (new (GC) mu::script::runtime::fixed (new (GC) mu::script::string::node (mu::string ())));
    expression2->dependencies.push_back (new (GC) mu::script::runtime::fixed (core_a));
    result->expressions.push_back (expression2);
    return result;
}

auto mu::script::api::full () -> boost::tuple <mu::script::extensions::node *, mu::map <mu::string, mu::core::node *>>
{
    boost::tuple <mu::script::extensions::node *, mu::map <mu::string, mu::core::node *>> result;
    boost::get <0> (result) = new (GC) mu::script::extensions::node;
    auto & map (boost::get <1> (result));
	map [mu::string (U"identity")] = new (GC) mu::script::identity::operation;
	map [mu::string (U"astring/truncate")] = new (GC) mu::script::astring::truncate;
	map [mu::string (U"bool_c/create")] = new (GC) mu::script::bool_c::create;
	map [mu::string (U"bool_c/equal")] = new (GC) mu::script::bool_c::equal;
	map [mu::string (U"chain/operation")] = new (GC) mu::script::chain::operation;
	map [mu::string (U"extensions/create")] = new (GC) mu::script::extensions::create;
	map [mu::string (U"extensions/merge_package")] = new (GC) mu::script::extensions::merge_package;
	map [mu::string (U"integer/equal")] = new (GC) mu::script::integer::equal;
	map [mu::string (U"integer/subtract")] = new (GC) mu::script::integer::subtract;
	map [mu::string (U"print/operation")] = new (GC) mu::script::print::operation;
	map [mu::string (U"package/add")] = new (GC) mu::script::package::add;
	map [mu::string (U"package/create")] = new (GC) mu::script::package::create;
	map [mu::string (U"package/get")] = new (GC) mu::script::package::get;
	map [mu::string (U"package/remove")] = new (GC) mu::script::package::remove;
	map [mu::string (U"times/operation")] = new (GC) mu::script::times::operation;
	return result;
}