programa
{
	funcao inteiro mostrarMenu()
	{
		inteiro num
		escreva("Bem Vindo! O que deseja realizar:\n 1.Criacao de senha \n 2.Verificacao de credito bancario \n 3.Fim \n")
		leia(num)

		retorne num
	}
	
	funcao escolherMenu(inteiro num)
	{
		escolha (num)
		{
			caso 1:
				inteiro num1, verificador
				escreva("Digite um numero: ")
				leia(num1)
				se(num1>=0 e num1<=9)
				{
					verificador= num1%3
					escreva("O numero digitado eh: ", num1, ". E seu digito verificador eh:", verificador,"\n\n") 
				}
			pare
			caso 2:
				real mensalidade, credito
				inteiro dps
				escreva("Digite o valor da mensalidade: ")
				leia(mensalidade)
				escreva("Digite as reprovas: ")
				leia(dps)
				se(dps<=3)
				{
				escreva ("O seu percentual de credito aprovado eh de 30% ")
				credito = mensalidade * 0.7
				escreva("Seu credito eh:", credito, "\n\n")
				}
				senao se (dps>3)
				{
				escreva("O seu percentual de credito aprovado eh de  20% ")
				credito = mensalidade * 0.8
				escreva("Seu credito eh: ", credito, "\n\n")
				}
			pare
			caso 3:
				limpa()
			pare
			caso contrario:
				escreva("Numero Digitado inválido\n\n")
				num = mostrarMenu()
			pare
		}
	}
	
	funcao inicio()
	{	
		inteiro n
		faca
		{	
			n = mostrarMenu()
			se (n != 1 ou n != 2 ou n != 3)
			{
				escolherMenu(n)
			}
		} enquanto (n!=3)
	}
	
}
/* $$$ Portugol Studio $$$ 
 * 
 * Esta seção do arquivo guarda informações do Portugol Studio.
 * Você pode apagá-la se estiver utilizando outro editor.
 * 
 * @POSICAO-CURSOR = 1121; 
 * @PONTOS-DE-PARADA = ;
 * @SIMBOLOS-INSPECIONADOS = ;
 * @FILTRO-ARVORE-TIPOS-DE-DADO = inteiro, real, logico, cadeia, caracter, vazio;
 * @FILTRO-ARVORE-TIPOS-DE-SIMBOLO = variavel, vetor, matriz, funcao;
 */