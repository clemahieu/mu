#include <mu/llvmc/generator.hpp>

#include <mu/llvmc/ast.hpp>
#include <mu/core/error_string.hpp>
#include <mu/llvmc/wrapper.hpp>

#include <llvm/Module.h>
#include <llvm/DerivedTypes.h>
#include <llvm/GlobalValue.h>
#include <llvm/Constants.h>
#include <llvm/Instructions.h>

#include <boost/array.hpp>

#include <gc_cpp.h>

mu::llvmc::generator::generator ():
result ({nullptr, nullptr}),
module (nullptr),
function (nullptr)
{
}

void mu::llvmc::generator::generate (mu::llvmc::ast::node * node_a)
{
    auto module_l (dynamic_cast <mu::llvmc::ast::module *> (node_a));
    if (module_l != nullptr)
    {
        module = new llvm::Module ("test", context);
        for (auto i (module_l->functions.begin ()), j (module_l->functions.end ()); i != j; ++i)
        {
            auto function (dynamic_cast <mu::llvmc::ast::function *> (*i));
            if (function != nullptr)
            {
                generate_function (function);
            }
            else
            {
                result.error = new (GC) mu::core::error_string (U"Module is expected to contain functions");
            }
        }
        if (result.error == nullptr)
        {
            result.module = module;
        }
    }
    else
    {
        result.error = new (GC) mu::core::error_string (U"Expecting a module");
    }
    module = nullptr;
}

void mu::llvmc::generator::generate_function (mu::llvmc::ast::function * function_a)
{
    std::vector <llvm::Type *> parameter_types;
    for (auto i (function_a->parameters.begin ()), j (function_a->parameters.end ()); i != j && result.error == nullptr; ++i)
    {
        auto type (dynamic_cast <mu::llvmc::wrapper::type *> ((*i)->type));
        if (type != nullptr)
        {
            parameter_types.push_back (type->type_m);
        }
        else
        {
            result.error = new (GC) mu::core::error_string (U"Expecting type");
        }
    }
    std::vector <llvm::Type *> return_types;
    return_types.push_back (llvm::Type::getInt8Ty (context));
    for (auto i (function_a->results.begin ()), j (function_a->results.end ()); i != j && result.error == nullptr; ++i)
    {
        for (auto k (i->begin ()), l (i->end ()); k != l; ++k)
        {
            auto type (dynamic_cast <mu::llvmc::wrapper::type *> ((*k)->written_type));
            if (type != nullptr)
            {
                return_types.push_back (type->type_m);
            }
            else
            {
                result.error = new (GC) mu::core::error_string (U"Expecting type");
            }
        }
    }
    if (result.error == nullptr)
    {
        auto function_type (llvm::FunctionType::get (llvm::StructType::get (context, return_types), parameter_types, false));
        function = llvm::Function::Create (function_type, llvm::GlobalValue::LinkageTypes::InternalLinkage);
        mu::llvmc::body_generator body (function_a, function);
        body.generate ();
        result.error = body.error;
        if (result.error == nullptr)
        {
            module->getFunctionList ().push_back (function);
        }
    }
    function = nullptr;
}

mu::llvmc::body_generator::body_generator (mu::llvmc::ast::function * ast_a, llvm::Function * function_a):
last_branch (0),
ast (ast_a),
error (nullptr),
function (function_a)
{
    entry.index = 0;
    auto block (llvm::BasicBlock::Create (function_a->getContext ()));
    function_a->getBasicBlockList ().push_back (block);
    entry.first = block;
    entry.last = block;
    auto k (function_a->getArgumentList().begin ());
    auto l (function_a->getArgumentList().end ());
    auto i (ast_a->parameters.begin ());
    auto j (ast_a->parameters.end ());
    for (; i != j && k != l; ++i, ++k)
    {
        auto value (*i);
        llvm::Argument * argument (k);
        complete [value] = decltype (complete)::mapped_type (argument, &entry);
        entry.values.insert (value);
    }
    if ((i == j) != (k == l))
    {
        error = new (GC) mu::core::error_string (U"Unexpected number of parameters");
    }
}

void mu::llvmc::body_generator::generate ()
{
    size_t result_index (0);
    size_t result_element_index (1);
    for (auto i (ast->results.begin ()), j (ast->results.end ()); i != j && error == nullptr; ++i, ++result_index)
    {
        auto & result_set (*i);
        auto highest (&entry);
        mu::vector <llvm::Value *> results;
        for (auto k (result_set.begin ()), l (result_set.end ()); k != l && error == nullptr; ++k)
        {
            auto result (dynamic_cast <mu::llvmc::ast::result *> (*k));
            if (result != nullptr)
            {
                auto new_value (generate_value (result->value));
                if (error == nullptr)
                {
                    highest = highest->index > new_value.second->index ? highest : new_value.second;
                }
                results.push_back (new_value.first);
            }
            else
            {
                error = new (GC) mu::core::error_string (U"Expecting result");
            }
        }
        if (error == nullptr)
        {
            llvm::Value * result (llvm::UndefValue::get (function->getReturnType ()));
            auto insert_instruction (llvm::InsertValueInst::Create (result, llvm::ConstantInt::get (llvm::Type::getInt8Ty (function->getContext ()), result_index), llvm::ArrayRef <unsigned> (0)));
            result = insert_instruction;
            highest->last->getInstList().push_back (insert_instruction);
            for (auto i (results.begin ()), j (results.end ()); i != j; ++i, ++result_element_index)
            {
                insert_instruction = llvm::InsertValueInst::Create (result, *i, llvm::ArrayRef <unsigned> (result_element_index));
                highest->last->getInstList().push_back (insert_instruction);
                result = insert_instruction;
            }
            highest->last->getInstList().push_back (llvm::ReturnInst::Create (function->getContext (), result));
        }
    }
}

auto mu::llvmc::body_generator::generate_value (mu::llvmc::ast::node * node_a) -> decltype (complete)::mapped_type
{
    decltype (complete)::mapped_type result;
    auto existing (complete.find (node_a));
    if (existing == complete.end ())
    {
        
    }
    else
    {
        result = existing->second;
    }
    return result;
}