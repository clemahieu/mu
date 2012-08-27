#include <gtest/gtest.h>

#include <mu/script/api.h>
#include <mu/script/extensions_node.h>
#include <mu/io/keywording_extensions.h>

// Creation of api extensions
TEST (script_test, api1)
{
    auto api (mu::script::api::core ());
    ASSERT_TRUE (api != nullptr);
    auto tilde ((*api->extensions) (mu::string (U"~")));
    ASSERT_TRUE (!boost::get <0> (tilde).empty ());
}