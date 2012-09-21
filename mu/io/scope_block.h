#pragma once

#include <mu/io/scope_scope.h>
#include <mu/io/context.h>

namespace mu
{
    namespace io
    {
        namespace scope
        {
            class block : public mu::io::scope::scope
            {
            public:
                block (mu::io::scope::scope & parent_a);
                bool declare (mu::core::errors::error_target & errors_a, mu::string const & name_a, mu::core::node * const node_a, mu::io::context const & context_a);
                void refer (mu::string const & name_a, mu::io::context const & context_a, mu::core::node_list & target_a);
                bool fill (mu::string const & name_a, mu::core::node_list & target_a) override;
                bool reserve (mu::core::errors::error_target & errors_a, mu::string const & name_a) override;
                void pass (mu::multimap <mu::string, mu::core::node_list *> const & unresolved_a) override;
                void end ();
                mu::io::scope::scope & parent;
                mu::map <mu::string, mu::core::node *> mapping;
                mu::multimap <mu::string, mu::core::node_list *> unresolved;
            };
        }
    }
}