function exit_linux
[int32 code]
[
	let nothing [asm unit {%%%}
		mov $$1, %rax
		mov $$0, %rdi
		syscall %%% {}]
]
[[;nothing]]

function exit_osx
[int32 code]
[
]
[]

function linux
[]
[]
[[int1 cint1 #0]]

function exit
[int32 code]
[
	let osx linux_l [linux]
	let exit_l [exit_linux code; linux_l]
	let exit_o [exit_osx code; osx]
]
[[; [join exit_l exit_o]]]

function entry
[]
[
	[exit cint32 #0]
]
[[]]
