#include "simple_test_3.h"

lambda_p_test::simple_test_3::simple_test_3 (void)
{
}

lambda_p_test::simple_test_3::~simple_test_3 (void)
{
}

void lambda_p_test::simple_test_3::run ()
{
	::std::string str;
	::boost::shared_ptr < ::boost::iostreams::stream < ::boost::iostreams::back_insert_device < ::std::string> > > target (new ::boost::iostreams::stream < ::boost::iostreams::back_insert_device < ::std::string> > (::boost::iostreams::back_insert_device < ::std::string> (str)));
	::lambda_p::serialization::simple < ::boost::iostreams::stream < ::boost::iostreams::back_insert_device < ::std::string> > > simple (target);
	::boost::shared_ptr < ::lambda_p::core::routine> routine (new ::lambda_p::core::routine (::std::string ("test_function")));
	::boost::shared_ptr < ::lambda_p::core::node> nor (new ::lambda_p::core::node (::std::string ("nor")));
	routine->surface.push_back (or);
	::boost::shared_ptr < ::lambda_p::core::node> r (new ::lambda_p::core::node (::std::string ("r")));
	routine->surface.push_back (value1);
	::boost::shared_ptr < ::lambda_p::core::node> s (new ::lambda_p::core::node (::std::string ("s")));
	routine->surface.push_back (value2);
	::boost::shared_ptr < ::lambda_p::core::node> q (new ::lambda_p::core::node (::std::string ("q")));
	routine->surface.push_back (value3);
	::boost::shared_ptr < ::lambda_p::core::node> qprime (new ::lambda_p::core::node (::std::string ("qprime")));
	::boost::shared_ptr < ::lambda_p::core::node> nor1 (new ::lambda_p::core::node (::std::string ("nor1")));
	::boost::shared_ptr < ::lambda_P::core::statement> nor1_instance (new ::lambda_p::core::statement (instance));
	routine->body->statements.push_back (nor1_instance);
	::boost::shared_ptr < ::lambda_p::core::node> nor2 (new ::lambda_p::core::node (::std::string ("nor2")));
	::boost::shared_ptr < ::lambda_p::core::statement> conjunction1 (new ::lambda_p::core::statement (and));
	routine->body->statements.push_back (conjunction1);
	conjunction1->connections.push_back (value1);
	conjunction1->connections.push_back (value2);
	conjunction1->connections.push_back (conjunction);
	::boost::shared_ptr < ::lambda_p::core::statement> disjunction1 (new ::lambda_p::core::statement (or));
	routine->body->statements.push_back (disjunction1);
	disjunction1->connections.push_back (conjunction);
	disjunction1->connections.push_back (value3);
	disjunction1->connections.push_back (value4);
	simple.routine (routine);
	target->flush ();
}