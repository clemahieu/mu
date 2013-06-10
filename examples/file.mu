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
	let osx linux_l [if [linux]]
	let result [join [exit_linux code; linux_l] [exit_osx code; osx]]
]
[[; result]]

function entry
[]
[
	let result [exit cint32 #0]
]
[[; result]]
