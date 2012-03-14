#include <mu/script_test/string/extension.h>

#include <mu/script_io/builder.h>
#include <mu/io/source.h>
#include <mu/io/debugging/error.h>

#include <boost/bind.hpp>

void mu::script_test::string::extension::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
}

void mu::script_test::string::extension::run_1 ()
{
	mu::script_io::builder builder;
	mu::io::source source (boost::bind (&mu::io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[` ;; 1]");
	assert (!builder.errors->errors.empty ());
	auto e1 (boost::dynamic_pointer_cast <mu::io::debugging::error> (builder.errors->errors [0]));
	assert (e1.get () != nullptr);
	assert (e1->context == mu::core::context (1, 2, 1, 1, 2, 1));
}

void mu::script_test::string::extension::run_2 ()
{
	mu::script_io::builder builder;
	mu::io::source source (boost::bind (&mu::io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[`[] ;; 1]");
	assert (!builder.errors->errors.empty ());
	auto e1 (boost::dynamic_pointer_cast <mu::io::debugging::error> (builder.errors->errors [0]));
	assert (e1.get () != nullptr);
	assert (e1->context == mu::core::context (1, 2, 1, 1, 4, 3));
}

void mu::script_test::string::extension::run_3 ()
{
	mu::script_io::builder builder;
	mu::io::source source (boost::bind (&mu::io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[` a ;; 1]");
	assert (builder.errors->errors.empty ());
}