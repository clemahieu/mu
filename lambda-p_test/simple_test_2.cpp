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
	routine->surface.push_back (item1);
	::boost::shared_ptr < ::lambda_p::core::node> item2 (new ::lambda_p::core::node (::std::string ("item2")));
	routine->surface.push_back (item2);
	::boost::shared_ptr < ::lambda_p::core::node> item3 (new ::lambda_p::core::node (::std::string ("item3")));
	routine->surface.push_back (item3);
	::boost::shared_ptr < ::lambda_p::core::node> item4 (new ::lambda_p::core::node (::std::string ("item4")));
	::boost::shared_ptr < ::lambda_p::core::statement> item5 (new ::lambda_p::core::statement (item1));
	routine->body->statements.push_back (item5);
	item5->connections.push_back (item2);
	item5->connections.push_back (item3);
	item5->connections.push_back (item4);
	simple.routine (routine);
	target->flush ();
}