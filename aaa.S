	lea    -128(%rsp), %rsp
	pushf	# push FLAGS register
	push %rdi
	push %rsi
	push %rdx
	push %rcx
	xor %rdi, %rdi
	mov $1, %rdi #repair 
	xor %rsi, %rsi
	mov $1, %rsi
	xor %rdx, %rdx
	mov $1, %rdx
	xor %rcx, %rcx
	mov $1, %rcx
	push   %rbp		# creating stack frame
	mov    %rsp,%rbp	# creating stack frame
	push   %rax
	push   %rdx
	push   %rcx
	push   %r8
	push   %r9
	push   %r10
	push   %r11
lbl:	call lbl	# TODO: fix me to go to the C function
	pop    %r11
	pop    %r10
	pop    %r9
	pop    %r8
	pop    %rcx
	pop    %rdx
	pop    %rax
	leave		# clear stack frame
	pop %rcx
	pop %rdx
	pop %rsi
	pop %rdi
	popf	# pop FLAGS register
	lea    128(%rsp), %rsp
