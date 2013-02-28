.global maiorContexto
.global numContexto
.global mostraContexto
.global numPrio

#maior Contexto
maiorContexto:
	pushl %ebp
	movl %esp, %ebp

	movl 8(%ebp), %ebx #ptr struct
	movl 12(%ebp), %ecx #tam struct
	movl 16(%ebp), %eax #pos

	addl $8, %ebx #adiciona 8 ao ptr da struct para ir para o atributo

	imull %ecx #adiciona a posicao ao ptr para avancar
	addl %eax, %ebx

	movl $32, %ecx #coloca 32 no ecx que sera o valor do int, que ira percorrer no ciclo
	movl (%ebx), %esi
	movl $0, %eax #valor de retorno
	movl $1, %edi #valor que sera o numero do contexto

ciclo:	
	movl %esi, %edx
	andl $1, %edx #mascara para se obter so o numero menos significativo
	cmpl $1, %edx 
	jne naoIgual
	movl %edi, %eax #se o numero menos significativo for 1, o valor do contexto ira para o retorno

naoIgual:
	incl %edi #incrementa o valor do contexto
	rorl %esi #roda o valor que esta em esi
	loop ciclo

	movl %ebp, %esp
	popl %ebp

	ret

#Numero de contextos
numContexto:
	pushl %ebp
	movl %esp, %ebp

	movl $0, %edx
	movl 8(%ebp), %ebx #ptr struct
	movl 12(%ebp), %ecx #tam struct
	movl 16(%ebp), %eax #pos

	imull %ecx #valor a avancar = tam*pos
	addl %eax, %ebx #posicao na struct

	addl $8, %ebx #avancar para o atributo correto

	movl $32, %ecx #coloca 32 no ecx que sera o valor do int, que ira percorrer no ciclo
	movl (%ebx), %esi
	movl $0, %eax #valor que sera o numero de contextos

cic:
	
	movl %esi, %edx
	andl $1, %edx #mascara para obter o numero menos significativo
	cmpl $1, %edx
	jne naoIg
	incl %eax #incrementa o retorno se o valor menos significativo é 1

naoIg:
	incl %edi #incrementa o valor do contexto
	rorl %esi #roda o valor que esta em esi
	loop cic

	movl %ebp, %esp
	popl %ebp

	ret

#mostra os contextos
mostraContexto:
	pushl %ebp
	movl %esp, %ebp

	movl $0, %edx
	movl 8(%ebp), %ebx #ptr struct
	movl 12(%ebp), %ecx #tam struct
	movl 16(%ebp), %eax #pos
	movl 20(%ebp), %edi #ptr vect contextos

	imull %ecx #valor a avancar = tam*pos
	addl %eax, %ebx #posicao na struct

	addl $8, %ebx #avancar para o atributo correto

	movl $32, %ecx #coloca 32 no ecx que sera o valor do int, que ira percorrer no ciclo
	movl (%ebx), %esi
	movl $0, %eax #valor do contexto

cic2:
	incl %eax	
	movl %esi, %edx
	andl $1, %edx #obter o numero menos significativo
	cmpl $1, %edx
	jne notEq
	movl %eax, (%edi) #copia o valor do contexto para a estrutura caso o numero menos significativo seja 1
	addl $4, %edi #incrementa o vetor de contextos

notEq:
	rorl %esi #roda o valor que esta em esi
	loop cic2

	movl %ebp, %esp
	popl %ebp

	ret

#numero de prioridades
numPrio:
	pushl %ebp
	movl %esp, %ebp

	movl $0, %eax
	movl 8(%ebp), %ebx #ptr struct
	movl 12(%ebp), %edi #tamanho struct
	movl 16(%ebp), %ecx #tam array
	movl 20(%ebp), %edx #prioridade

	addl $4, %ebx #percorrer só as prioridades

ciclo2:
	movl (%ebx), %esi #valor armazenado na estrutura
	cmpl %edx, %esi
	jne notEquals
	incl %eax #incrementa o numero de prioridades caso o valor de prioridade na struct seja igual ao passado por parametro

notEquals:
	addl %edi, %ebx #avanca uma posicao na struct
	loop ciclo2

	movl %ebp, %esp
	popl %ebp

	ret