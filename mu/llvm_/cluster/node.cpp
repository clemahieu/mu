#include "node.h"

#include <mu/core/routine.h>
#include <mu/llvm_/function/node.h>
#include <mu/script/cluster/node.h>

std::wstring mu::llvm_::cluster::node::name ()
{
	return std::wstring (L"mu::llvm_::cluster::node");
}