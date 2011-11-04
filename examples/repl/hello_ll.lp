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

@str = internal constant [14 x i8] c"Hello world!\0a\00"

declare void @printf (i8 *, ...)

define void @start ()
{
  %1 = bitcast [14 x i8] * @str to i8 *
  call void (i8*, ...)* @printf (i8* %1)
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
