environment
 ` llvm/context
 ` llvm/assemble
 ` llvm/compile
;
 context
 assemble
 compile
;
context ; ctx;
assemble `a |%|
define void @WinMainCRTStartup ()
{
 ret void
}
define void @WinMain ()
{
 ret void
}
% ctx; mod;
compile mod `a ./test.o;;
:;
