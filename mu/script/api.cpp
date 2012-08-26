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

#include <gc_cpp.h>

mu::script::extensions::node * mu::script::api::core ()
{
	auto result (new (GC) mu::script::extensions::node);
    mu::io::keywording::extensions & extensions (*result->extensions);
    extensions (mu::string (U"~"), new (GC) mu::script::identity::operation);
    extensions (mu::string (U"loadb"), new (GC) mu::script::loadb::operation);
    extensions (mu::string (U"loads"), new (GC) mu::script::loads::operation);
	extensions.add <mu::script::string::extension> (mu::string (U"`"));
	extensions.add <mu::script::astring::extension>(mu::string (U"a`"));
	extensions.add <mu::script::integer::extension> (mu::string (U"#"));
	return result;
}

mu::script::extensions::node * mu::script::api::full ()
{
	auto result (new (GC) mu::script::extensions::node);
    mu::io::keywording::extensions & extensions (*result->extensions);
	extensions (mu::string (U"identity"), new (GC) mu::script::identity::operation);
	extensions (mu::string (U"astring/truncate"), new (GC) mu::script::astring::truncate);
	extensions (mu::string (U"bool_c/create"), new (GC) mu::script::bool_c::create);
	extensions (mu::string (U"bool_c/equal"), new (GC) mu::script::bool_c::equal);
	extensions (mu::string (U"chain/operation"), new (GC) mu::script::chain::operation);
	extensions (mu::string (U"extensions/create"), new (GC) mu::script::extensions::create);
	extensions (mu::string (U"extensions/merge_package"), new (GC) mu::script::extensions::merge_package);
	extensions (mu::string (U"integer/equal"), new (GC) mu::script::integer::equal);
	extensions (mu::string (U"integer/subtract"), new (GC) mu::script::integer::subtract);
	extensions (mu::string (U"print/operation"), new (GC) mu::script::print::operation);
	extensions (mu::string (U"package/add"), new (GC) mu::script::package::add);
	extensions (mu::string (U"package/create"), new (GC) mu::script::package::create);
	extensions (mu::string (U"package/get"), new (GC) mu::script::package::get);
	extensions (mu::string (U"package/remove"), new (GC) mu::script::package::remove);
	extensions (mu::string (U"times/operation"), new (GC) mu::script::times::operation);
	return result;
}