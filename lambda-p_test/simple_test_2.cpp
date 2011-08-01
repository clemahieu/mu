#include "simple_test_2.h"

lambda_p_test::simple_test_2::simple_test_2 (void)
{
}

lambda_p_test::simple_test_2::~simple_test_2 (void)
{
}

void lambda_p_test::simple_test_2::run ()
{
	::std::string str;
	::boost::shared_ptr < ::boost::iostreams::stream < ::boost::iostreams::back_insert_device < ::std::string> > > target (new ::boost::iostreams::stream < ::boost::iostreams::back_insert_device < ::std::string> > (::boost::iostreams::back_insert_device < ::std::string> (str)));
	::lambda_p::serialization::simple < ::boost::iostreams::stream < ::boost::iostreams::back_insert_device < ::std::string> > > simple (target);
	::boost::shared_ptr < ::lambda_p::core::routine> routine (new ::lambda_p::core::routine (::std::string ("test_function")));
	::boost::shared_ptr < ::lambda_p::core::node> item1 (new ::lambda_p::core::node (::std::string ("item1")));
	routine->external_m.push_back (item1);
	::boost::shared_ptr < ::lambda_p::core::node> item2 (new ::lambda_p::core::node (::std::string ("item2")));
	routine->external_m.push_back (item2);
	::boost::shared_ptr < ::lambda_p::core::node> item3 (new ::lambda_p::core::node (::std::string ("item3")));
	routine->external_m.push_back (item3);
	::boost::shared_ptr < ::lambda_p::core::statement> item4 (new ::lambda_p::core::statement (::std::string ("item4"), item1));
	routine->body->statements.push_back (item4);
	item4->connections.push_back (item2);
	item4->connections.push_back (item3);
	simple.routine (routine);
	target->flush ();
}