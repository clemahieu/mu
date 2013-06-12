function exit_linux
[int32 code]
[
	let nothing [asm unit {%%%}
		mov $$60, %rax
		mov $$0, %rdi
		syscall %%% {}]
]
[[;nothing]]

function exit_osx
[int32 code]
[
	let nothing [asm unit {%%%}
		mov $$0x2000001, %rax
		mov $$0, %rdi
		syscall %%% {}]
]
[[;nothing]]

function linux
[]
[]
[[int1 cint1 #1]]

function exit
[int32 code]
[
	let linux_l osx [if [linux]]
	let result [join [exit_linux code; linux_l] [exit_osx code; osx]]
]
[[; result]]

function entry
[]
[
	let result [exit cint32 #0]
]
[[; result]]
