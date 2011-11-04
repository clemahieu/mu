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
 get
 jit
;
context ; ctx;
adata `|%%%%|

@str = internal constant [13 x i16] 

declare void @wprintf (i16 *, ...)

define void @start ()
{
  ret void
}

%%%%; asm;
assemble asm ctx; module;
engine module; eng;
overlay eng module;;
adata `start; start;
get module start; function;
jit eng function;;
:;
