#include <gtest/gtest.h>

#include <mu/script/api.h>
#include <mu/script/parser_scope_node.h>
#include <mu/io/keywording_extensions.h>
#include <mu/script/identity_operation.h>
#include <mu/script/runtime_routine.h>
#include <mu/script/context.h>
#include <mu/core/errors/error_target.h>
#include <mu/script/string_node.h>

// Creation of api extensions
TEST (script_test, api1)
{
    auto api (mu::script::api::core ());
    ASSERT_TRUE (api != nullptr);
    ASSERT_TRUE (api->extensions != nullptr);
    auto & map (api->injected);
    ASSERT_TRUE (!map.empty ());
    auto tilde_existing (map.find (mu::string (U"~")));
    ASSERT_TRUE (tilde_existing != map.end ());
    auto tilde (dynamic_cast <mu::script::identity::operation *> (tilde_existing->second));
    ASSERT_TRUE (tilde != nullptr);
    auto context_existing (map.find (mu::string (U"context")));
    ASSERT_TRUE (context_existing != map.end ());
    auto context (dynamic_cast <mu::script::runtime::routine *> (context_existing->second));
    ASSERT_TRUE (context != nullptr);
    auto loadb_existing (map.find (mu::string (U"loadb")));
    ASSERT_TRUE (loadb_existing != map.end ());
    auto loadb (dynamic_cast <mu::script::runtime::routine *> (loadb_existing->second));
    ASSERT_TRUE (loadb != nullptr);
    auto loads_existing (map.find (mu::string (U"loads")));
    ASSERT_TRUE (loads_existing != map.end ());
    auto loads (dynamic_cast <mu::script::runtime::routine *> (loads_existing->second));
    ASSERT_TRUE (loads != nullptr);
}

// Creation of context
TEST (script_test, api2)
{
    auto api (mu::script::api::core ());
    ASSERT_TRUE (api != nullptr);
    auto & map (api->injected);
    auto context_existing (map.find (mu::string (U"context")));
    ASSERT_TRUE (context_existing != map.end ());
    auto context (dynamic_cast <mu::script::runtime::routine *> (context_existing->second));
    ASSERT_TRUE (context != nullptr);
    mu::script::context ctx;
    ctx.push (context);
    auto valid (ctx ());
    ASSERT_TRUE (valid);
    ASSERT_TRUE (ctx.working_size () == 1);
    auto new_context (dynamic_cast <mu::script::parser_scope::node *> (ctx.working (0)));
    ASSERT_TRUE (new_context != nullptr);
    ASSERT_TRUE (new_context->injected.size () == api->injected.size ());
    ASSERT_TRUE (new_context->extensions->extensions_m.size () == api->extensions->extensions_m.size ());
}

// Creation of loads
TEST (script_test, api3)
{
    auto api (mu::script::api::core ());
    ASSERT_TRUE (api != nullptr);
    auto & map (api->injected);
    auto loads_existing (map.find (mu::string (U"loads")));
    ASSERT_TRUE (loads_existing != map.end ());
    auto loads (dynamic_cast <mu::script::runtime::routine *> (loads_existing->second));
    ASSERT_TRUE (loads != nullptr);
    mu::script::context ctx;
    ctx.push (loads);
    auto scope (new (GC) mu::script::parser_scope::node);
    ctx.push (scope);
    ctx.push (new (GC) mu::script::string::node (mu::string (U"prefix")));
    ctx.push (new (GC) mu::script::string::node (mu::string (U"source_test.mu")));
    auto valid (ctx ());
    ASSERT_TRUE (valid);
    ASSERT_TRUE (scope->injected.size () == 2);
    ASSERT_TRUE (scope->injected.find (mu::string (U"prefixa")) != scope->injected.end ());
    ASSERT_TRUE (scope->injected.find (mu::string (U"prefixb")) != scope->injected.end ());
}