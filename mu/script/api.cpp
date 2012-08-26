#include <mu/script/api.h>

#include <mu/io/keywording_extensions.h>
#include <mu/script/extensions/node.h>
#include <mu/script/string/extension.h>
#include <mu/script/astring/extension.h>
#include <mu/script/integer/extension.h>
#include <mu/io/keywording_global.h>
#include <mu/script/identity/operation.h>
#include <mu/script/astring/truncate.h>
#include <mu/script/bool_c/create.h>
#include <mu/script/bool_c/equal.h>
#include <mu/script/chain/operation.h>
#include <mu/script/extensions/create.h>
#include <mu/script/extensions/merge_package.h>
#include <mu/script/integer/equal.h>
#include <mu/script/integer/subtract.h>
#include <mu/script/print/operation.h>
#include <mu/script/package/add.h>
#include <mu/script/package/create.h>
#include <mu/script/package/get.h>
#include <mu/script/package/remove.h>
#include <mu/script/times/operation.h>
#include <mu/script/string/extension.h>
#include <mu/script/astring/extension.h>
#include <mu/script/integer/extension.h>
#include <mu/script/closure/create_single.h>

#include <gc_cpp.h>

mu::script::extensions::node * mu::script::api::core ()
{
	auto result (new (GC) mu::script::extensions::node);
    mu::io::keywording::extensions & extensions (*result->extensions);
    extensions (mu::string (U"~"), new (GC) mu::script::identity::operation);
	extensions.add <mu::script::string::extension> (mu::string (U"`"));
	extensions.add <mu::script::astring::extension>(mu::string (U"a`"));
	extensions.add <mu::script::integer::extension> (mu::string (U"#"));
	extensions (mu::string (U".apply"), new (GC) mu::script::closure::create_single);
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