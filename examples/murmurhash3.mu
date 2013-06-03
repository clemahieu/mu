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
]
[[]]

function entry
[]
[]
[[; unit_v [rotl32 cint32 #8 cint32 #8] [rotl64 cint64 #16 cint64 #8]]]
