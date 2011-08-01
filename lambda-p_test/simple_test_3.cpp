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
	::boost::shared_ptr < ::lambda_p::core::node> and (new ::lambda_p::core::node (::std::string ("and")));
	routine->surface.push_back (and);
	::boost::shared_ptr < ::lambda_p::core::node> or (new ::lambda_p::core::node (::std::string ("or")));
	routine->surface.push_back (or);
	::boost::shared_ptr < ::lambda_p::core::node> value1 (new ::lambda_p::core::node (::std::string ("value1")));
	routine->surface.push_back (value1);
	::boost::shared_ptr < ::lambda_p::core::node> value2 (new ::lambda_p::core::node (::std::string ("value2")));
	routine->surface.push_back (value2);
	::boost::shared_ptr < ::lambda_p::core::node> value3 (new ::lambda_p::core::node (::std::string ("value3")));
	routine->surface.push_back (value3);
	::boost::shared_ptr < ::lambda_p::core::node> value4 (new ::lambda_p::core::node (::std::string ("value4")));
	routine->surface.push_back (value4);
	::boost::shared_ptr < ::lambda_p::core::node> conjunction (new ::lambda_p::core::node (::std::string ("conjunction")));
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