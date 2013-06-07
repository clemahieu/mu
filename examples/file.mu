function exit
[int32 code]
[
	let nothing [asm unit {%%%}
		mov $$1, %rax
		mov $$0, %rdi
		syscall %%% {}]
]
[[;nothing]]

function entry
[]
[
	[exit cint32 #0]
]
[[]]
