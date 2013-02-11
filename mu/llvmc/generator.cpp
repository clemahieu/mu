#include <mu/llvmc/generator.hpp>

#include <mu/llvmc/ast.hpp>
#include <mu/core/error_string.hpp>

#include <llvm/Module.h>
#include <llvm/DerivedTypes.h>
#include <llvm/GlobalValue.h>
#include <llvm/Constants.h>
#include <llvm/Instructions.h>

#include <boost/array.hpp>

#include <gc_cpp.h>

mu::llvmc::branch::branch () :
order (0),
next (nullptr),
terminator (nullptr)
{
}