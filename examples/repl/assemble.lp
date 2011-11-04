environment
 `adata
 `llvm/context
 `llvm/execution_engine
 `llvm/assemble
 `llvm/overlay
 `llvm/module_get_function
 `llvm/jit_function
;
 adata
 context
 engine
 assemble
 overlay
 jit
 get
;
context ; ctx;
adata `|%%%%|

define void @start ()
{
  ret
}

%%%%; asm;
assemble asm ctx; module;
engine module; eng;
overlay eng module;;
adata `start; start;
get module start; function;
jit eng function;;
:;
