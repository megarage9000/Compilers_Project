declare void @print_int(i32)
declare void @print_string(i8*)
declare i32 @read_int()

; store the newline as a string constant
; more specifically as a constant array containing i8 integers
@.nl = constant [2 x i8] c"\0A\00"

define i32 @add1(i32 %a, i32 %b) {
entry:
  %tmp1 = add i32 %a, %b
  ret i32 %tmp1
}

define i32 @add_recur(i32 %a, i32 %b) {
entry:
    %cond = icmp eq i32 %a, 0
    br i1 %cond, label %done, label %repeat

    done:
    ret i32 %b

    repeat:
    %new_a = sub i32 %a, 1
    %new_b = add i32 %b, 1
    %result = call i32 @add_recur(i32 %new_a, i32 %new_b)
    ret i32 %result
}

define i32 @fact(i32 %a) {
entry:
    %if_1 = icmp eq i32 %a, 1
    br i1 %if_1, label %isOne, label %notOne

    isOne:
        ret i32 1
    
    notOne:
        %b = sub i32 %a, 1
        %b_fact = call i32 @fact(i32 %b)
        %new_val = mul i32 %a, %b_fact
        ret i32 %new_val
}

define i32 @main() {
entry:
  %tmp6 = call i32 @fact(i32 11)
  call void @print_int(i32 %tmp6)
  ; convert the constant newline array into a pointer to i8 values
  ; using getelementptr, arg1 = @.nl, 
  ; arg2 = first element stored in @.nl which is of type [2 x i8]
  ; arg3 = the first element of the constant array
  ; getelementptr will return the pointer to the first element
  %cast.nl = getelementptr [2 x i8], [2 x i8]* @.nl, i8 0, i8 0
  call void @print_string(i8* %cast.nl)
  ret i32 0
}
