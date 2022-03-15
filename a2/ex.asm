	.file	"ASSG2_B200738CS_CMMADHAV_1.c"
	.text
	.data
	.align 4
	.type	M, @object
	.size	M, 4
M:
	.long	2
	.local	LARGEST_PRIME
	.comm	LARGEST_PRIME,4,4
	.local	C1
	.comm	C1,4,4
	.align 4
	.type	C2, @object
	.size	C2, 4
C2:
	.long	1
	.local	MODE
	.comm	MODE,1,1
	.text
	.globl	qdProbing
	.type	qdProbing, @function
qdProbing:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	M(%rip), %ecx
	movl	-4(%rbp), %eax
	cltd
	idivl	%ecx
	movl	C1(%rip), %eax
	imull	-8(%rbp), %eax
	leal	(%rdx,%rax), %ecx
	movl	-8(%rbp), %eax
	imull	%eax, %eax
	movl	%eax, %edx
	movl	C2(%rip), %eax
	imull	%edx, %eax
	addl	%ecx, %eax
	movl	M(%rip), %ecx
	cltd
	idivl	%ecx
	movl	%edx, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	qdProbing, .-qdProbing
	.globl	dblHash
	.type	dblHash, @function
dblHash:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	M(%rip), %ecx
	movl	-4(%rbp), %eax
	cltd
	idivl	%ecx
	movl	%edx, %edi
	movl	LARGEST_PRIME(%rip), %ecx
	movl	LARGEST_PRIME(%rip), %esi
	movl	-4(%rbp), %eax
	cltd
	idivl	%esi
	movl	%ecx, %eax
	subl	%edx, %eax
	imull	-8(%rbp), %eax
	addl	%edi, %eax
	movl	M(%rip), %ecx
	cltd
	idivl	%ecx
	movl	%edx, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	dblHash, .-dblHash
	.globl	hashIt
	.type	hashIt, @function
hashIt:
.LFB8:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, %eax
	movl	%esi, -8(%rbp)
	movl	%edx, -12(%rbp)
	movb	%al, -4(%rbp)
	cmpb	$97, -4(%rbp)
	jne	.L6
	movl	-12(%rbp), %edx
	movl	-8(%rbp), %eax
	movl	%edx, %esi
	movl	%eax, %edi
	call	qdProbing
	jmp	.L7
.L6:
	movl	-12(%rbp), %edx
	movl	-8(%rbp), %eax
	movl	%edx, %esi
	movl	%eax, %edi
	call	dblHash
.L7:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	hashIt, .-hashIt
	.globl	isPrime
	.type	isPrime, @function
isPrime:
.LFB9:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -20(%rbp)
	movl	$2, -4(%rbp)
	jmp	.L9
.L12:
	movl	-20(%rbp), %eax
	cltd
	idivl	-4(%rbp)
	movl	%edx, %eax
	testl	%eax, %eax
	jne	.L10
	movl	$0, %eax
	jmp	.L11
.L10:
	addl	$1, -4(%rbp)
.L9:
	movl	-20(%rbp), %eax
	movl	%eax, %edx
	shrl	$31, %edx
	addl	%edx, %eax
	sarl	%eax
	cmpl	%eax, -4(%rbp)
	jle	.L12
	movl	$1, %eax
.L11:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	isPrime, .-isPrime
	.globl	setLargestPrime
	.type	setLargestPrime, @function
setLargestPrime:
.LFB10:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	M(%rip), %eax
	subl	$1, %eax
	movl	%eax, -4(%rbp)
	jmp	.L14
.L15:
	subl	$1, -4(%rbp)
.L14:
	movl	-4(%rbp), %eax
	movl	%eax, %edi
	call	isPrime
	testl	%eax, %eax
	je	.L15
	movl	-4(%rbp), %eax
	movl	%eax, LARGEST_PRIME(%rip)
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	setLargestPrime, .-setLargestPrime
	.globl	insertToHashTable
	.type	insertToHashTable, @function
insertToHashTable:
.LFB11:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movl	$0, -8(%rbp)
	jmp	.L17
.L21:
	movzbl	MODE(%rip), %eax
	movsbl	%al, %eax
	movl	-8(%rbp), %edx
	movl	-28(%rbp), %ecx
	movl	%ecx, %esi
	movl	%eax, %edi
	call	hashIt
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	cmpl	$-2, %eax
	je	.L18
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	cmpl	$-1, %eax
	jne	.L19
.L18:
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-24(%rbp), %rax
	addq	%rax, %rdx
	movl	-28(%rbp), %eax
	movl	%eax, (%rdx)
	jmp	.L16
.L19:
	addl	$1, -8(%rbp)
.L17:
	movl	M(%rip), %eax
	cmpl	%eax, -8(%rbp)
	jl	.L21
.L16:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE11:
	.size	insertToHashTable, .-insertToHashTable
	.globl	deleteFromHashTable
	.type	deleteFromHashTable, @function
deleteFromHashTable:
.LFB12:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movl	$0, -8(%rbp)
	jmp	.L23
.L25:
	movzbl	MODE(%rip), %eax
	movsbl	%al, %eax
	movl	-8(%rbp), %edx
	movl	-28(%rbp), %ecx
	movl	%ecx, %esi
	movl	%eax, %edi
	call	hashIt
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	cmpl	%eax, -28(%rbp)
	jne	.L24
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	$-2, (%rax)
.L24:
	addl	$1, -8(%rbp)
.L23:
	movl	M(%rip), %eax
	cmpl	%eax, -8(%rbp)
	jl	.L25
	nop
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE12:
	.size	deleteFromHashTable, .-deleteFromHashTable
	.section	.rodata
.LC0:
	.string	"1"
.LC1:
	.string	"-1"
	.text
	.globl	searchHashTable
	.type	searchHashTable, @function
searchHashTable:
.LFB13:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movl	$0, -8(%rbp)
	jmp	.L27
.L30:
	movzbl	MODE(%rip), %eax
	movsbl	%al, %eax
	movl	-8(%rbp), %edx
	movl	-28(%rbp), %ecx
	movl	%ecx, %esi
	movl	%eax, %edi
	call	hashIt
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	cmpl	%eax, -28(%rbp)
	jne	.L28
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L26
.L28:
	addl	$1, -8(%rbp)
.L27:
	movl	M(%rip), %eax
	cmpl	%eax, -8(%rbp)
	jl	.L30
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
.L26:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE13:
	.size	searchHashTable, .-searchHashTable
	.section	.rodata
.LC2:
	.string	"%d ()\n"
.LC3:
	.string	"%d (%d)\n"
	.text
	.globl	printHashTable
	.type	printHashTable, @function
printHashTable:
.LFB14:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L32
.L36:
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	cmpl	$-1, %eax
	je	.L33
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	cmpl	$-2, %eax
	jne	.L34
.L33:
	movl	-4(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC2(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	jmp	.L35
.L34:
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %edx
	movl	-4(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L35:
	addl	$1, -4(%rbp)
.L32:
	movl	M(%rip), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L36
	nop
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE14:
	.size	printHashTable, .-printHashTable
	.section	.rodata
.LC4:
	.string	"%c"
.LC5:
	.string	"%d"
	.text
	.globl	main
	.type	main, @function
main:
.LFB15:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	MODE(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC4(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_scanf@PLT
	leaq	M(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC5(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_scanf@PLT
	movl	M(%rip), %eax
	cltq
	salq	$2, %rax
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, -16(%rbp)
	movl	M(%rip), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-16(%rbp), %rax
	movl	$-1, %esi
	movq	%rax, %rdi
	call	memset@PLT
	movl	$0, %eax
	call	setLargestPrime
	jmp	.L38
.L44:
	cmpb	$105, -21(%rbp)
	jne	.L39
	leaq	-20(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC5(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_scanf@PLT
	movl	-20(%rbp), %edx
	movq	-16(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	insertToHashTable
.L39:
	cmpb	$115, -21(%rbp)
	jne	.L40
	leaq	-20(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC5(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_scanf@PLT
	movl	-20(%rbp), %edx
	movq	-16(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	searchHashTable
.L40:
	cmpb	$100, -21(%rbp)
	jne	.L41
	leaq	-20(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC5(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_scanf@PLT
	movl	-20(%rbp), %edx
	movq	-16(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	deleteFromHashTable
.L41:
	cmpb	$112, -21(%rbp)
	jne	.L42
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	printHashTable
.L42:
	cmpb	$116, -21(%rbp)
	je	.L47
.L38:
	movq	stdin(%rip), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movb	%al, -21(%rbp)
	cmpb	$-1, -21(%rbp)
	jne	.L44
	jmp	.L43
.L47:
	nop
.L43:
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
	movl	$0, %eax
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L46
	call	__stack_chk_fail@PLT
.L46:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE15:
	.size	main, .-main
	.ident	"GCC: (GNU) 11.2.0"
	.section	.note.GNU-stack,"",@progbits
