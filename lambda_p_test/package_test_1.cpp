#include "package_test_1.h"

#include <lambda_p_kernel/package.h>
#include <lambda_p_kernel/null_binder.h>
#include <lambda_p/core/statement.h>
#include <lambda_p_kernel/bind_procedure.h>
#include <lambda_p/core/routine.h>
#include <lambda_p/core/association.h>
#include <lambda_p_kernel/nodes/data.h>
#include <lambda_p/errors/error_list.h>

#include <sstream>

lambda_p_test::package_test_1::package_test_1(void)
{
}

lambda_p_test::package_test_1::~package_test_1(void)
{
}

void lambda_p_test::package_test_1::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
	run_4 ();
}

void lambda_p_test::package_test_1::run_1 ()
{
    boost::shared_ptr < lambda_p_kernel::null_binder> null_binder (new lambda_p_kernel::null_binder);
    boost::shared_ptr < lambda_p_kernel::package> package (new lambda_p_kernel::package);
    std::wstring name (L"null_binder");
    package->nodes [name] = null_binder;
    boost::shared_ptr < lambda_p::core::routine> routine (new lambda_p::core::routine); 
    size_t declaration (routine->add_declaration ());
	routine->surface->declarations.push_back (declaration);
    lambda_p::core::statement * statement1 (routine->add_statement ());
	statement1->target = declaration;
	size_t declaration2 (routine->add_declaration ());
	statement1->association->declarations.push_back (declaration2);
	statement1->association->references.push_back (routine->inject_declaration (boost::shared_ptr <lambda_p::binder::node> (new lambda_p_kernel::nodes::data (std::wstring (name)))));
	lambda_p::binder::list nodes;
    nodes [declaration] = package;
    lambda_p_kernel::bind_procedure bind_procedure (routine, nodes);
	lambda_p::errors::error_list problems;
	bind_procedure (problems);
	assert (problems.errors.empty ());
	assert (nodes [declaration2].get () != nullptr);
	assert (nodes [declaration2] == null_binder);
}

void lambda_p_test::package_test_1::run_2 ()
{
    boost::shared_ptr < lambda_p_kernel::null_binder> null_binder (new lambda_p_kernel::null_binder);
    boost::shared_ptr < lambda_p_kernel::package> inner (new lambda_p_kernel::package);
    std::wstring name (L"null_binder");
    inner->nodes [name] = null_binder;
	boost::shared_ptr < lambda_p_kernel::package> outer (new lambda_p_kernel::package);
	std::wstring name2 (L"package");
	outer->nodes [name2] = inner;
    boost::shared_ptr < lambda_p::core::routine> routine (new lambda_p::core::routine); 
    size_t declaration (routine->add_declaration ());
    routine->surface->declarations.push_back (declaration);
    lambda_p::core::statement * statement1 (routine->add_statement ());
	statement1->target = declaration;
	size_t declaration2 (routine->add_declaration ());
	statement1->association->declarations.push_back (declaration2);
	std::wstring dname (L"package/null_binder");
	statement1->association->references.push_back (routine->inject_declaration (boost::shared_ptr <lambda_p::binder::node> (new lambda_p_kernel::nodes::data (std::wstring (dname)))));
	lambda_p::binder::list nodes;
    nodes [declaration] = outer;
    lambda_p_kernel::bind_procedure bind_procedure (routine, nodes);
	lambda_p::errors::error_list problems;
	bind_procedure (problems);
	assert (problems.errors.empty ());
	assert (nodes [declaration2].get () != nullptr);
	assert (nodes [declaration2] == null_binder);
}

void lambda_p_test::package_test_1::run_3 ()
{
    boost::shared_ptr < lambda_p_kernel::null_binder> null_binder (new lambda_p_kernel::null_binder);
    boost::shared_ptr < lambda_p_kernel::package> package (new lambda_p_kernel::package);
    std::wstring name (L"null_binder");
	std::wstring junk (L"junk");
    package->nodes [name] = null_binder;
    boost::shared_ptr < lambda_p::core::routine> routine (new lambda_p::core::routine); 
    size_t declaration (routine->add_declaration ());
	routine->surface->declarations.push_back (declaration);
    lambda_p::core::statement * statement1 (routine->add_statement ());
	statement1->target = declaration;
	statement1->association->references.push_back (declaration);
	size_t declaration2 (routine->add_declaration ());
	statement1->association->declarations.push_back (declaration2);
	statement1->association->references.push_back (routine->inject_declaration (boost::shared_ptr <lambda_p::binder::node> (new lambda_p_kernel::nodes::data (std::wstring (junk)))));
	statement1->association->references.push_back (routine->inject_declaration (boost::shared_ptr <lambda_p::binder::node> (new lambda_p_kernel::nodes::data (std::wstring (name)))));
	lambda_p::binder::list nodes;
    nodes [declaration] = package;
    lambda_p_kernel::bind_procedure bind_procedure (routine, nodes);
	lambda_p::errors::error_list problems;
	bind_procedure (problems);
	assert (!problems.errors.empty ());
}

void lambda_p_test::package_test_1::run_4 ()
{
    boost::shared_ptr < lambda_p_kernel::null_binder> null_binder (new lambda_p_kernel::null_binder);
    boost::shared_ptr < lambda_p_kernel::package> package (new lambda_p_kernel::package);
    std::wstring name (L"null_binder");
    package->nodes [name] = null_binder;
    boost::shared_ptr < lambda_p::core::routine> routine (new lambda_p::core::routine); 
    size_t declaration (routine->add_declaration ());
	routine->surface->declarations.push_back (declaration);
    lambda_p::core::statement * statement1 (routine->add_statement ());
	statement1->target = declaration;
    size_t d1 (routine->add_declaration ());
	statement1->association->declarations.push_back (d1);
    size_t d2 (routine->add_declaration ());
	statement1->association->declarations.push_back (d2);
	statement1->association->references.push_back (routine->inject_declaration (boost::shared_ptr <lambda_p::binder::node> (new lambda_p_kernel::nodes::data (std::wstring (name)))));
    statement1->association->references.push_back (routine->inject_declaration (boost::shared_ptr <lambda_p::binder::node> (new lambda_p_kernel::nodes::data (std::wstring (name)))));
	lambda_p::binder::list nodes;
    nodes [declaration] = package;
    lambda_p_kernel::bind_procedure bind_procedure (routine, nodes);
	lambda_p::errors::error_list problems;
	bind_procedure (problems);
	assert (problems.errors.empty ());
	assert (nodes [d1].get () != nullptr);
	assert (nodes [d2].get () != nullptr);
}