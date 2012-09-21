#pragma once

#include <mu/io/scope_scope.h>

namespace mu
{
    namespace io
    {
        class context;
        namespace analyzer
        {
            class extensions;
        }
        namespace scope
        {
            class global : public mu::io::scope::scope
            {
            public:
                global (mu::io::analyzer::extensions & extensions_a);
                bool declare (mu::core::errors::error_target & errors_a, mu::string const & name_a, mu::core::node * const node_a, mu::io::context const & context_a);
                bool fill (mu::string const & name_a, mu::core::node_list & target_a) override;
                bool reserve (mu::core::errors::error_target & errors_a, mu::string const & name_a) override;
                void pass (mu::multimap <mu::string, mu::core::node_list *> const & unresolved_a) override;
                bool end (mu::core::errors::error_target & errors_a);
                mu::io::analyzer::extensions & extensions;
                mu::map <mu::string, mu::core::node *> mapping;                
                mu::multimap <mu::string, mu::core::node_list *> unresolved;
            };
        }
    }
}