function exit
[int32 code]
[
	[asm void {%%%}
		mov %%1, $rax
		mov %%0, $rdi
		syscall %%%]
]
[[]]

function entry
[]
[
	[exit cint32 #0]
]
[[]]