//
//  data_to_string_binder_test_1.cpp
//  lambda_p_test
//
//  Created by Colin LeMahieu on 9/19/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#define __STDC_LIMIT_MACROS
#define __STDC_CONSTANT_MACROS

#include <lambda_p_test/data_to_string_binder_test_1.h>
#include <lambda_p_llvm/data_to_string_binder.h>
#include <lambda_p/core/routine.h>
#include <lambda_p_llvm/generation_context.h>
#include <lambda_p_llvm/value.h>
#include <lambda_p/core/association.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/binder/data.h>
#include <lambda_p_kernel/bind_procedure.h>

#include <llvm/LLVMContext.h>
#include <llvm/Module.h>

#include <boost/shared_ptr.hpp>

#include <sstream>

void lambda_p_test::data_to_string_binder_test_1::run ()
{
	boost::shared_ptr <lambda_p::core::routine> routine (new lambda_p::core::routine);
    size_t p1 = routine->add_declaration ();
	routine->surface->declarations.push_back (p1);
    lambda_p::core::statement * statement = routine->add_statement ();
	statement->target = p1;
    size_t declaration = routine->add_declaration ();
    statement->association->declarations.push_back (declaration);
    size_t data = routine->add_data (std::wstring (L"Test string"));
    statement->association->references.push_back (data);
    llvm::LLVMContext llvm_context;
    std::string module_string ("test");
    llvm::StringRef module_name (module_string);
    llvm::Module * module = new llvm::Module (module_name, llvm_context);
    lambda_p_llvm::generation_context context (llvm_context, module, nullptr);
	boost::shared_ptr < lambda_p_llvm::data_to_string_binder> binder (new lambda_p_llvm::data_to_string_binder (context));
	lambda_p::binder::node_list nodes;
	nodes [0] = binder;
	lambda_p::errors::error_list problems;
	lambda_p_kernel::bind_procedure bind_procedure (routine, nodes);
	bind_procedure (problems);
    //binder->bind (statement, nodes, problems);
	assert (problems.errors.size () == 0);
    assert (module->getGlobalList ().size () == 1);
	assert (nodes.nodes.size () == 3);
    assert (nodes [declaration].get () != nullptr);
    assert (boost::dynamic_pointer_cast < lambda_p_llvm::value> (nodes [declaration]).get () != nullptr);
}