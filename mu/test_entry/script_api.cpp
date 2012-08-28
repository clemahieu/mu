#include <gtest/gtest.h>

#include <mu/script/api.h>
#include <mu/script/extensions_node.h>
#include <mu/io/keywording_extensions.h>
#include <mu/script/identity_operation.h>
#include <mu/script/runtime_routine.h>

// Creation of api extensions
TEST (script_test, api1)
{
    auto api (mu::script::api::core ());
    ASSERT_TRUE (boost::get <0> (api) != nullptr);
    auto & map (boost::get <1> (api));
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