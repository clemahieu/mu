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
`a |%|
define void @WinMainCRTStartup ()
{
 ret void
}
define void @WinMain ()
{
 ret void
}
%; code;
assemble code ctx; mod;
`a ./test.o; name;
compile mod name;;
:;
