#pragma once

#include <iostream>

namespace mu
{
    namespace core
    {
        class error
        {
        public:
            virtual ~error ();
            virtual void output (std::ostream & out) = 0;
        };
    }
}