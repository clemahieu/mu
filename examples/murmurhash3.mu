function rotl32
[int32 x int32 r]
[
	let result [or [shl x r] [lshr x [sub cint32 #32 r]]]
]
[[int32 result]]

function rotl64
[int64 x int64 r]
[
	let result [or [shl x r] [lshr x [sub cint64 #64 r]]]
]
[[int64 result]]

function getblock32 
[ptr int32 p int32 i]
[
	let result [getelementptr p i]
]
[[int32 result]]

function getblock64
[ptr int64 p int32 i]
[
	let result [getelementptr p i]
]
[[int64 result]]

function fmix32
[int32 h]
[
	let h1 [xor h [lshr h cint32 #16]]
	let h2 [mul h1 cint32 #2246822507]
	let h3 [xor h2 [lshr h2 #13]]
	let h4 [mul h3 cint32 #3266489909]
	let h5 [xor h4 [lshr h4 cint32 #16]]
]
[[int32 h5]]

function fmix64
[int64 k]
[
	let k1 [xor k [lshr k cint32 #33]]
	let k2 [mul k1 cint64 #18397679294719824000]
	let k3 [xor k2 [lshr k2 #33]]
	let k4 [mul k3 cint64 #14181476777654088000]
	let k5 [xor k4 [lshr k4 #33]]
]
[[int64 k5]]

function entry
[]
[]
[[; unit_v [rotl32 cint32 #8 cint32 #8] [rotl64 cint64 #16 cint64 #8]]]
