#include <mu/script_test/string/extension.h>

#include <mu/core/errors/error_list.h>
#include <mu/io/builder.h>
#include <mu/io/analyzer/analyzer.h>
#include <mu/io/source.h>
#include <mu/io/debugging/error.h>
#include <mu/script/api.h>
#include <mu/script/extensions/node.h>

#include <boost/bind.hpp>

void mu::script_test::string::extension::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
}

void mu::script_test::string::extension::run_1 ()
{
	mu::io::builder builder (boost::shared_ptr <mu::script::extensions::node> (mu::script::api::core ())->extensions);
	builder (L"[` ;; 1]");
	assert (!builder.errors->errors.empty ());
	auto e1 (boost::dynamic_pointer_cast <mu::io::debugging::error> (builder.errors->errors [0]));
	assert (e1.get () != nullptr);
	assert (e1->context == mu::io::debugging::context (builder.stream, 1, 2, 1, 1, 2, 1));
}

void mu::script_test::string::extension::run_2 ()
{
	mu::io::builder builder (boost::shared_ptr <mu::script::extensions::node> (mu::script::api::core ())->extensions);
	builder (L"[`[] ;; 1]");
	assert (!builder.errors->errors.empty ());
	auto e1 (boost::dynamic_pointer_cast <mu::io::debugging::error> (builder.errors->errors [0]));
	assert (e1.get () != nullptr);
	assert (e1->context == mu::io::debugging::context (builder.stream, 1, 2, 1, 1, 4, 3));
}

void mu::script_test::string::extension::run_3 ()
{
	mu::io::builder builder (boost::shared_ptr <mu::script::extensions::node> (mu::script::api::core ())->extensions);
	builder (L"[` a ;; 1]");
	assert (builder.errors->errors.empty ());
}