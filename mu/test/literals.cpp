extern char const * const generate_empty_expected = R"%%%(
define void @0() {
  unreachable
}
)%%%";

extern char const * const generate_add_expected = R"%%%(
define i1 @0(i1) {
  %2 = and i1 true, true
  %3 = and i1 %2, true
  %4 = add i1 %0, %0
  ret i1 %4
}
)%%%";

extern char const * const generate_two_return_expected = R"%%%(
%0 = type { i1, i1 }

define %0 @0(i1) {
  %2 = insertvalue %0 undef, i1 %0, 0
  %3 = insertvalue %0 %2, i1 %0, 1
  ret %0 %3
}
)%%%";

extern char const * const generate_if_expected = R"%%%(
define i8 @0(i1) {
  %2 = and i1 true, true
  %3 = icmp eq i1 %0, false
  %4 = and i1 %2, %3
  %5 = icmp eq i1 %0, true
  %6 = and i1 %2, %5
  %7 = and i1 true, %4
  %8 = select i1 %7, i8 0, i8 undef
  %9 = and i1 true, %6
  %10 = select i1 %9, i8 1, i8 %8
  ret i8 %10
}
)%%%";

extern char const * const generate_if_value_expected = R"%%%(
%0 = type { i32, i32, i8 }

define %0 @0(i1) {
  %2 = and i1 true, true
  %3 = icmp eq i1 %0, false
  %4 = and i1 %2, %3
  %5 = icmp eq i1 %0, true
  %6 = and i1 %2, %5
  %7 = and i1 true, %4
  %8 = and i1 %7, true
  %9 = select i1 %8, i8 0, i8 undef
  %10 = and i1 true, %6
  %11 = and i1 %10, true
  %12 = select i1 %11, i8 1, i8 %9
  %13 = insertvalue %0 undef, i32 4, 0
  %14 = insertvalue %0 %13, i32 5, 1
  %15 = insertvalue %0 %14, i8 %12, 2
  ret %0 %15
}
)%%%";

extern char const * const generate_if_join_expected = R"%%%(
define void @0(i1) {
  %2 = and i1 true, true
  %3 = icmp eq i1 %0, false
  %4 = and i1 %2, %3
  %5 = icmp eq i1 %0, true
  %6 = and i1 %2, %5
  %7 = or i1 false, %4
  %8 = or i1 %7, %6
  ret void
}
)%%%";

extern char const * const generate_if_join_value_expected = R"%%%(
define i1 @0(i1) {
  %2 = and i1 true, true
  %3 = and i1 %2, true
  %4 = and i1 true, true
  %5 = icmp eq i1 %0, false
  %6 = and i1 %4, %5
  %7 = icmp eq i1 %0, true
  %8 = and i1 %4, %7
  %9 = and i1 %3, %6
  %10 = add i1 %0, %0
  %11 = or i1 false, %3
  %12 = select i1 %3, i1 %10, i1 undef
  %13 = and i1 true, true
  %14 = and i1 %13, true
  %15 = and i1 %14, %8
  %16 = add i1 %0, %0
  %17 = or i1 %11, %14
  %18 = select i1 %14, i1 %16, i1 %12
  ret i1 %18
}
)%%%";

extern char const * const generate_if_join_2value_expected = R"%%%(
%0 = type { i1, i1, i8 }

define %0 @0(i1) {
  %2 = and i1 true, true
  %3 = and i1 %2, true
  %4 = and i1 true, true
  %5 = icmp eq i1 %0, false
  %6 = and i1 %4, %5
  %7 = icmp eq i1 %0, true
  %8 = and i1 %4, %7
  %9 = and i1 %3, %6
  %10 = add i1 %0, %0
  %11 = or i1 false, %3
  %12 = select i1 %3, i1 %10, i1 undef
  %13 = and i1 true, true
  %14 = and i1 %13, true
  %15 = and i1 %14, %8
  %16 = add i1 %0, %0
  %17 = or i1 %11, %14
  %18 = select i1 %14, i1 %16, i1 %12
  %19 = and i1 true, %17
  %20 = select i1 %19, i8 0, i8 undef
  %21 = and i1 true, true
  %22 = and i1 %21, true
  %23 = and i1 %22, %6
  %24 = add i1 %0, %0
  %25 = or i1 false, %22
  %26 = select i1 %22, i1 %24, i1 undef
  %27 = and i1 true, true
  %28 = and i1 %27, true
  %29 = and i1 %28, %8
  %30 = add i1 %0, %0
  %31 = or i1 %25, %28
  %32 = select i1 %28, i1 %30, i1 %26
  %33 = and i1 true, %31
  %34 = select i1 %33, i8 1, i8 %20
  %35 = insertvalue %0 undef, i1 %18, 0
  %36 = insertvalue %0 %35, i1 %32, 1
  %37 = insertvalue %0 %36, i8 %34, 2
  ret %0 %37
}
)%%%";

extern char const * const generate_if_join_load_expected = R"%%%(
define i1 @0(i1) {
  %2 = and i1 true, true
  %3 = icmp eq i1 %0, false
  %4 = and i1 %2, %3
  %5 = icmp eq i1 %0, true
  %6 = and i1 %2, %5
  %7 = and i1 true, %4
  br i1 true, label %8, label %10

; <label>:8                                       ; preds = %1
  %9 = load i1* null
  br label %10

; <label>:10                                      ; preds = %8, %1
  %11 = phi i1 [ %9, %8 ], [ undef, %1 ]
  %12 = or i1 false, true
  %13 = select i1 true, i1 %11, i1 undef
  %14 = and i1 true, %6
  br i1 true, label %15, label %17

; <label>:15                                      ; preds = %10
  %16 = load i1* null
  br label %17

; <label>:17                                      ; preds = %15, %10
  %18 = phi i1 [ %16, %15 ], [ undef, %10 ]
  %19 = or i1 %12, true
  %20 = select i1 true, i1 %18, i1 %13
  ret i1 %20
}
)%%%";

extern char const * const generate_call_0_expected = R"%%%(
define void @0() {
  ret void
}

define void @1() {
  br i1 true, label %1, label %2

; <label>:1                                       ; preds = %0
  call void @0()
  br label %2

; <label>:2                                       ; preds = %0, %1
  ret void
}
)%%%";

extern char const * const generate_call_1_expected = R"%%%(
define i1 @0(i1) {
  ret i1 %0
}

define i1 @1(i1) {
  %2 = and i1 true, true
  br i1 %2, label %3, label %5

; <label>:3                                       ; preds = %1
  %4 = call i1 @0(i1 %0)
  br label %5

; <label>:5                                       ; preds = %1, %3
  %6 = phi i1 [ %4, %3 ], [ undef, %1 ]
  ret i1 %6
}
)%%%";

extern char const * const generate_call_2_expected = R"%%%(
define i8 @0(i1) {
  %2 = and i1 true, true
  %3 = icmp eq i1 %0, false
  %4 = and i1 %2, %3
  %5 = icmp eq i1 %0, true
  %6 = and i1 %2, %5
  %7 = and i1 true, %4
  %8 = select i1 %7, i8 0, i8 undef
  %9 = and i1 true, %6
  %10 = select i1 %9, i8 1, i8 %8
  ret i8 %10
}

define i8 @1(i1) {
  %2 = and i1 true, true
  br i1 %2, label %3, label %5

; <label>:3                                       ; preds = %1
  %4 = call i8 @0(i1 %0)
  br label %5

; <label>:5                                       ; preds = %1, %3
  %6 = phi i8 [ %4, %3 ], [ undef, %1 ]
  %7 = icmp eq i8 %6, 0
  %8 = and i1 %2, %7
  %9 = icmp eq i8 %6, 1
  %10 = and i1 %2, %9
  %11 = and i1 true, %8
  %12 = select i1 %11, i8 0, i8 undef
  %13 = and i1 true, %10
  %14 = select i1 %13, i8 1, i8 %12
  ret i8 %14
}
)%%%";

extern char const * const generate_call_3_expected = R"%%%(
%0 = type { i32, i32, i8 }

define %0 @0(i1) {
  %2 = and i1 true, true
  %3 = icmp eq i1 %0, false
  %4 = and i1 %2, %3
  %5 = icmp eq i1 %0, true
  %6 = and i1 %2, %5
  %7 = and i1 true, %4
  %8 = and i1 %7, true
  %9 = select i1 %8, i8 0, i8 undef
  %10 = and i1 true, %6
  %11 = and i1 %10, true
  %12 = select i1 %11, i8 1, i8 %9
  %13 = insertvalue %0 undef, i32 1, 0
  %14 = insertvalue %0 %13, i32 2, 1
  %15 = insertvalue %0 %14, i8 %12, 2
  ret %0 %15
}

define i8 @1(i1) {
  %2 = and i1 true, true
  br i1 %2, label %3, label %5

; <label>:3                                       ; preds = %1
  %4 = call %0 @0(i1 %0)
  br label %5

; <label>:5                                       ; preds = %1, %3
  %6 = phi %0 [ %4, %3 ], [ undef, %1 ]
  %7 = extractvalue %0 %6, 2
  %8 = icmp eq i8 %7, 0
  %9 = and i1 %2, %8
  %10 = extractvalue %0 %6, 0
  %11 = icmp eq i8 %7, 1
  %12 = and i1 %2, %11
  %13 = extractvalue %0 %6, 1
  %14 = icmp eq i8 %7, 2
  %15 = and i1 %2, %14
  %16 = and i1 true, %9
  %17 = select i1 %16, i8 0, i8 undef
  %18 = and i1 true, %12
  %19 = select i1 %18, i8 1, i8 %17
  ret i8 %19
}
)%%%";

extern char const * const generate_call_predicate_b1v0_expected = R"%%%(
define void @0() {
  ret void
}

define void @1() {
  br i1 true, label %1, label %2

; <label>:1                                       ; preds = %0
  call void @0()
  br label %2

; <label>:2                                       ; preds = %0, %1
  ret void
}
)%%%";

extern char const * const generate_call_predicate_b1v1_expected = R"%%%(
define void @0() {
  ret void
}

define i1 @1() {
  br i1 true, label %1, label %2

; <label>:1                                       ; preds = %0
  call void @0()
  br label %2

; <label>:2                                       ; preds = %0, %1
  ret i1 false
}
)%%%";