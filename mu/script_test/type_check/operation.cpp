#include <mu/script_test/type_check/operation.h>

#include <mu/core/errors/error_list.h>
#include <mu/script/type_check/operation.h>
#include <mu/script/identity/operation.h>

#include <boost/make_shared.hpp>

void mu::script_test::type_check::operation::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
	run_4 ();
	run_5 ();
	run_6 ();
}

void mu::script_test::type_check::operation::run_1 ()
{
	auto errors (boost::make_shared <mu::core::errors::error_list> ());
	auto identity (boost::make_shared <mu::script::identity::operation> ());
	mu::script::type_check::operation <> type_check (identity);
	std::vector <boost::shared_ptr <mu::core::node>> a1;
	std::vector <boost::shared_ptr <mu::core::node>> r1;
    auto ctx (mu::script::context (errors, a1, r1));
	type_check (ctx);
	assert (errors->errors.empty ());
}

void mu::script_test::type_check::operation::run_2 ()
{
	auto errors (boost::make_shared <mu::core::errors::error_list> ());
	auto identity (boost::make_shared <mu::script::identity::operation> ());
	mu::script::type_check::operation <> type_check (identity);
	std::vector <boost::shared_ptr <mu::core::node>> a1;
	a1.push_back (boost::make_shared <mu::script::identity::operation> ());
	std::vector <boost::shared_ptr <mu::core::node>> r1;
    auto ctx (mu::script::context (errors, a1, r1));
	type_check (ctx);
	assert (!errors->errors.empty ());
	assert (r1.size () == 0);
}

void mu::script_test::type_check::operation::run_3 ()
{
	auto errors (boost::make_shared <mu::core::errors::error_list> ());
	auto identity (boost::make_shared <mu::script::identity::operation> ());
	mu::script::type_check::operation <mu::script::identity::operation> type_check (identity);
	std::vector <boost::shared_ptr <mu::core::node>> a1;
	a1.push_back (boost::make_shared <mu::script::identity::operation> ());
	std::vector <boost::shared_ptr <mu::core::node>> r1;
    auto ctx (mu::script::context (errors, a1, r1));
	type_check (ctx);
	assert (errors->errors.empty ());
	assert (r1.size () == 1);
}

void mu::script_test::type_check::operation::run_4 ()
{
	auto errors (boost::make_shared <mu::core::errors::error_list> ());
	auto identity (boost::make_shared <mu::script::identity::operation> ());
	mu::script::type_check::operation <mu::script::identity::operation> type_check (identity);
	std::vector <boost::shared_ptr <mu::core::node>> a1;
	std::vector <boost::shared_ptr <mu::core::node>> r1;
    auto ctx (mu::script::context (errors, a1, r1));
	type_check (ctx);
	assert (!errors->errors.empty ());
	assert (r1.size () == 0);
}

void mu::script_test::type_check::operation::run_5 ()
{
	auto errors (boost::make_shared <mu::core::errors::error_list> ());
	auto identity (boost::make_shared <mu::script::identity::operation> ());
	mu::script::type_check::operation <mu::script::identity::operation> type_check (identity);
	std::vector <boost::shared_ptr <mu::core::node>> a1;
	a1.push_back (boost::make_shared <mu::core::node> ());
	std::vector <boost::shared_ptr <mu::core::node>> r1;
    auto ctx (mu::script::context (errors, a1, r1));
	type_check (ctx);
	assert (!errors->errors.empty ());
	assert (r1.size () == 0);
}

void mu::script_test::type_check::operation::run_6 ()
{
	auto errors (boost::make_shared <mu::core::errors::error_list> ());
	auto identity (boost::make_shared <mu::script::identity::operation> ());
	mu::script::type_check::operation <mu::core::node, mu::core::node> type_check (identity);
	std::vector <boost::shared_ptr <mu::core::node>> a1;
	a1.push_back (boost::make_shared <mu::core::node> ());
	a1.push_back (boost::make_shared <mu::core::node> ());
	std::vector <boost::shared_ptr <mu::core::node>> r1;
    auto ctx (mu::script::context (errors, a1, r1));
	type_check (ctx);
	assert (errors->errors.empty ());
	assert (r1.size () == 2);
}