#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define MAXIMO_CONTAS 10

#define VERMELHO "\x1b[38;2;250;040;040m"
#define AMARELO  "\x1b[38;2;250;250;070m"
#define AZUL     "\x1b[38;2;080;080;250m"
#define CINZA    "\x1b[38;2;080;080;080m"
#define PRETO    "\x1b[38;2;000;000;000m"
#define BRANCO   "\x1b[38;2;255;255;255m"

typedef struct
{
	int usuario;
	int senha;
	float saldo;
	int tipoConta;
	int tipoUsuario;
	int tipoBanco;
	int bloqueado;
	int ativa;
	int trocarSenha;
} Conta;

Conta contas[MAXIMO_CONTAS];

void menuPrincipal(void);
int pegarIndexConta(int usuario, int tipoBanco);
void conectar(void);
void criarConta(int gerente);
void mostrarInformacoesConta(int index, int mostrarSaldo, int mostrarSenha, int gerente, int limpar, int mensagemSair);
void menuInicialCliente(int index, int mensagemInicial, int subMenuAtivado);
void menuInicialGerente(int index, int mensagemInicial, int subMenuAtivado);
void trocarInformacao(int gerente, int subMenu, int index);
void depositar(int index);
void retirar(int index);
void transferir(int index, int situacaoInvertida);
void menuEmprestimo(int index);
void emprestimoValor(double juros, double maximo);
void pagarConta(int index, int taxa);
void trocarSenha(int gerente, int index);
int solicitarSenhaAtual(int index, int mensagemInicial, int mensagemSucesso);
void sair(int mostrarMensagem);

int main()
{
	setlocale(LC_CTYPE, "");
	
	contas[0].usuario = 123;
	contas[0].senha = 123;
	contas[0].tipoConta = 1;
	contas[0].saldo = 500.0;
	contas[0].tipoUsuario = 2;
	contas[0].tipoBanco = 1;
	contas[0].ativa = 1;
	
	contas[1].usuario = 1;
	contas[1].senha = 1;
	contas[1].tipoConta = 1;
	contas[1].saldo = 100.0;
	contas[1].tipoUsuario = 1;
	contas[1].tipoBanco = 1;
	contas[1].ativa = 1;
	
	contas[2].usuario = 2;
	contas[2].senha = 2;
	contas[2].tipoConta = 2;
	contas[2].saldo = 100.0;
	contas[2].tipoUsuario = 1;
	contas[2].tipoBanco = 2;
	contas[2].ativa = 1;
	
	menuPrincipal();
	
	return 0;
}

void menuPrincipal(void)
{
	int operacao = 0;
	
	system("cls");
	
	printf(AZUL " _____\n");
	printf("|  ___|\n");
	printf("| |__   ____   ____  ___   ____   ___\n");
	printf("|  __| / _  | / __/ / _ \\ | __ \\ / __|  \n");
	printf("| |   | (_| || (__ |  __/ | | | |\\__ \\  \n");
	printf("|_|    \\____| \\___\\ \\___| |_| |_||___/  \n" BRANCO);
	
	printf("\nBanco Virtual Estudantil\n");
	printf("01 - Conectar\n");
	printf("02 - Criar Conta\n");
	printf("03 - Sair\n");
	
	while (operacao < 1 || operacao > 3)
	{
		printf("\nDigite a operação deseja realizar: ");
		fflush(stdin);
		scanf("%i", &operacao);
		
		switch (operacao)
		{
			case 1:
				conectar();
			break;
			case 2:
				criarConta(0);
				menuPrincipal();
			break;
			case 3:
				exit(0);
			break;
			default:
				printf(VERMELHO "\nOperação inválida!" BRANCO);
			break;
		}
	}
}

int pegarIndexConta(int usuario, int tipoBanco)
{
	int index = -1;
	
	for (index = 0; index < MAXIMO_CONTAS; index++)
	{
		if (tipoBanco > 0 && tipoBanco < 100 && contas[index].usuario == usuario && contas[index].tipoBanco == tipoBanco)
		{
			return index;
		}
		else if (contas[index].usuario == usuario)
		{
			return index;
		}
	}
	
	return -1;
}

void conectar(void)
{
	int usuario = -1, indexConta = -1, senhaDigitada = -1;
	
	system("cls");
	printf(AMARELO "Digite zero para voltar ao menu anterior\n\n" BRANCO);
			
	while (usuario < 0 || (usuario != 0 && indexConta < 0))
	{
		printf("Digite o usuário: ");
		scanf("%i", &usuario);
		
		indexConta = pegarIndexConta(usuario, 0);
	
		if (usuario < 0 || (usuario != 0 && indexConta < 0))
			printf(VERMELHO "Usuário inválido!\n\n" BRANCO);
	}
	
	senhaDigitada = solicitarSenhaAtual(indexConta, 0, 0);
		
	if (usuario > 0 && senhaDigitada == 1)
	{	
		if (contas[indexConta].tipoUsuario != 2)
			menuInicialCliente(indexConta, 1, 0);
		else
			menuInicialGerente(indexConta, 1, 0);
	}
	
	if (senhaDigitada == 1)
		sair(0);	
		
	menuPrincipal();
}

void criarConta(int gerente)
{
	int usuario = -1, senha = -1, senha1 = -1, tipoConta = -1, index = -1, tipoUsuario = -1, tipoBanco = -1, aceita = -1;
	float saldo = 0.0;
	
	system("cls");
	printf(AMARELO "Digite zero para voltar ao menu anterior\n\n" BRANCO);
	
	while(usuario < 0 || (index >= 0 && usuario > 0))
	{
		printf("Digite o usuário: ");
		scanf("%i", &usuario);
		
		index = pegarIndexConta(usuario, 0);
		
		if (usuario < 0)
			printf(VERMELHO "Usuário inválido!\n\n" BRANCO);
		else if (index >= 0 && usuario > 0)
			printf(VERMELHO "Já existe uma conta com esse usuário, por favor preencha os dados novamente!\n\n" BRANCO);
	}
	
	if (usuario > 0)
	{
		while(senha < 0 || (senha1 != senha && senha != 0))
		{
			printf("Digite a senha: ");
			scanf("%i", &senha);
			
			if (senha < 0)
				printf(VERMELHO "Senha inválida!\n\n" BRANCO);
			else if (senha > 0)
			{
				printf("Digite a senha novamente: ");
				scanf("%i", &senha1);
				
				if (senha1 < 0)
					printf(VERMELHO "Senha inválida!\n\n" BRANCO);
				else if (senha1 != senha)
					printf(VERMELHO "As senhas não são iguais!\n\n" BRANCO);
			}
		}
	}
	
	if (gerente > 0 && senha > 0)
	{
		while (tipoUsuario < 0 || tipoUsuario > 2)
		{
			printf("Digite o tipo do usuário (1-CLIENTE | 2-GERENTE): ");
			scanf("%i", &tipoUsuario);
			
			if (tipoUsuario < 0 || tipoUsuario > 2)
				printf(VERMELHO "\nTipo de usuário inválido!\n" BRANCO);
		}
	}
	else
		tipoUsuario = 1;
	
	if (tipoUsuario > 0 && tipoUsuario < 3)
	{
		while (tipoConta < 0 || tipoConta > 2)
		{
			printf("Digite o tipo de conta (1-CORRENTE | 2-POUPANÇA): ");
			scanf("%i", &tipoConta);
			
			if (tipoConta < 0 || tipoConta > 2)
				printf(VERMELHO "\nTipo de conta inválido!\n" BRANCO);
		}
	}
	
	if (tipoConta > 0 && tipoConta < 3)
	{
		while (tipoBanco < 0 || tipoBanco > 99)
		{
			printf("Digite o tipo do banco (01 até 99): ");
			scanf("%i", &tipoBanco);
			
			if (tipoBanco < 0 || tipoBanco > 99)
				printf(VERMELHO "\nTipo de banco inválido!\n" BRANCO);
		}
	}
	
	if ((gerente < 1 && tipoUsuario > 0 && tipoUsuario < 3) || (gerente > 0 && tipoConta > 0 && tipoConta < 3))
	{   
		for(index = 0; index < MAXIMO_CONTAS; index++)
		{ 	
			if (contas[index].usuario == 0)
			{ 
				contas[index].usuario = usuario;
				contas[index].senha = senha;
				contas[index].saldo = saldo;
				contas[index].tipoConta = tipoConta;
				contas[index].tipoBanco = tipoBanco;
				contas[index].tipoUsuario = tipoUsuario;
				
				if (tipoConta == 1)
					contas[index].ativa = 1;
				
				break;
			}
		}
		mostrarInformacoesConta(index, 1, 1, 0, 1, tipoConta == 1);
		
		if (tipoConta == 2)
		{
			printf(AZUL "\nPara ativar sua conta é necessário possuir R$ 100,00\n" BRANCO);
			while (aceita < 1 || aceita > 2)
			{
				printf("Deseja fazer uma transação (1-SIM | 2-NÃO): ");
				scanf("%i", &aceita);
				
				if (aceita < 1 || aceita > 2)
					printf(VERMELHO "Resposta inválida!\n\n" BRANCO);
			}
			
			if (aceita == 1)
			{
				aceita = -1;
				system("cls");
				
				printf("01 - Depositar\n");
				printf("02 - Transferir\n");
				printf("00 - Voltar\n");
				
				while ((aceita < 1 || aceita > 2) && aceita != 0)
				{
					printf("Digite a operação deseja realizar: ");
					scanf("%i", &aceita);
					
					if ((aceita < 1 || aceita > 2) && aceita != 0)
						printf(VERMELHO "Operação inválida!\n\n" BRANCO);
				}	
				
				switch (aceita)
				{
					case 1:
						depositar(index);
					break;
					case 2:
						transferir(index, 1);
					break;
					case 0:
					break;
				}
				
				if (contas[index].saldo > 100.0)
					contas[index].ativa = 1;
			}
		}
	}
}

void mostrarInformacoesConta(int index, int mostrarSaldo, int mostrarSenha, int gerente, int limpar, int mensagemSair)
{
	if (limpar > 0)
	{
		system("cls");
		printf(AMARELO "Digite zero para voltar ao menu anterior\n\n" BRANCO);
	}
		
	printf(AZUL "Conta número %03i\n\n" BRANCO, index + 1);
	printf("Usuário: %i\n", contas[index].usuario);
	
	if (mostrarSenha > 0)
		printf("Senha: %i\n", contas[index].senha);
	
	if (contas[index].tipoUsuario == 1)
	{
		if (contas[index].tipoConta == 1)
			printf("Tipo de conta: Corrente\n");
		else
			printf("Tipo de conta: Poupança\n");
			
		if (mostrarSaldo > 0)
			printf("Saldo: R$ %.2f\n", contas[index].saldo);
			
		printf("Tipo de banco: %i\n", contas[index].tipoBanco);
		
		if (contas[index].ativa > 0)
			printf("Estado: Ativa\n");
		else
			printf("Estado: Desativada\n");
			
		if (gerente > 0)
		{
			if (contas[index].bloqueado > 0)
				printf("Bloqueado: Sim\n");
			else
				printf("Bloqueado: Não\n");
				
			if (contas[index].trocarSenha > 0)
				printf("Necessário trocar de senha: Sim\n");
			else
				printf("Necessário trocar de senha: Não\n");
		}
	}
	
	if (mensagemSair > 0)
		sair(0);
}

void menuInicialCliente(int index, int mensagemInicial, int subMenuAtivado)
{
	int operacao = -1, subMenu = -1, reabrirMenu = 1;
	
	system("cls");
	if (subMenuAtivado > 0)
		printf(AMARELO "Digite zero para voltar ao menu anterior\n\n" BRANCO);
	if (mensagemInicial > 0)
		printf(AZUL "Bem vindo cliente %i!\n\n" BRANCO, contas[index].usuario);

	if (subMenuAtivado > 0)
	{
		printf(CINZA "01 - Deposito\n" BRANCO);
		printf(CINZA "02 - Retirada\n" BRANCO);
		printf(CINZA "03 - Transferir\n" BRANCO);
		printf(CINZA "04 - Calcular Emprestimo\n" BRANCO);
		printf(CINZA "05 - Pagamento de Contas\n" BRANCO);
		printf("\t06 - Agua, Luz e Gás\n");
		printf("\t07 - Outros\n");
		printf(CINZA "08 - Informações da Conta e Saldo\n" BRANCO);
		printf(CINZA "09 - Trocar senha\n" BRANCO);
	}
	else
	{
		printf("01 - Deposito\n");
		if (contas[index].saldo > 0)
		{
			printf("02 - Retirada\n");
			printf("03 - Transferir\n");
		}
		else
		{
			printf(CINZA "02 - Retirada\n" BRANCO);
			printf(CINZA "03 - Transferir\n" BRANCO);
		}
		printf("04 - Calcular Emprestimo\n");
		if (contas[index].saldo > 0)
			printf("05 - Pagamento de Contas\n");
		else
			printf(CINZA "05 - Pagamento de Contas\n" BRANCO);
		printf("08 - Informações da Conta e Saldo\n");
		printf("09 - Trocar senha\n");
	}
	printf("00 - Sair\n\n");
	
	while ((operacao >= 1 || operacao <= 7) && subMenuAtivado <= 0)
	{
		printf("Digite a operação deseja realizar: ");
		scanf("%i", &operacao);
		
		switch (operacao)
		{
			case 1:
				depositar(index);
			break;
			case 2:
				if (contas[index].saldo > 0)
					retirar(index);
				else
				{
					printf(VERMELHO "Saldo insuficiente para realizar essa operação!\n\n" BRANCO);	
					reabrirMenu = 0;
				}
			break;
			case 3:
				if (contas[index].saldo > 0)
					transferir(index, 0);
				else
				{
					printf(VERMELHO "Saldo insuficiente para realizar essa operação!\n\n" BRANCO);	
					reabrirMenu = 0;
				}
			break;
			case 4:
				menuEmprestimo(index);
			break;
			case 5:
			{
				if (contas[index].saldo > 0)
				{
					menuInicialCliente(index, mensagemInicial, 1);
				
					while ((subMenu < 6 || subMenu > 7) && subMenu != 0)
					{
						printf("Digite a operação deseja realizar: ");
						scanf("%i", &subMenu);
						
						switch (subMenu)
						{
							case 6:
								pagarConta(index, 0);
							break;
							case 7:
								pagarConta(index, 15);
							break;
							case 0:
								menuInicialCliente(index, 0, 0);
							break;
							default:
								printf(VERMELHO "Operação inválida!\n\n" BRANCO);
							break;
						}
					}
				}
				else
				{
					printf(VERMELHO "Saldo insuficiente para realizar essa operação!\n\n" BRANCO);	
					reabrirMenu = 0;
				}
			}
			break;
			case 8:
				mostrarInformacoesConta(index, 1, 0, 0, 1, 1);
			break;
			case 9:
				trocarSenha(0, index);
			break;
			case 0:
				menuPrincipal();
			break;
			default:
				printf(VERMELHO "Operação inválida!\n\n" BRANCO);
				reabrirMenu = 0;
			break;
		}
		
		if (reabrirMenu == 1)
			menuInicialCliente(index, 0, 0);

		reabrirMenu = 1;
	}
}

void menuInicialGerente(int index, int mensagemInicial, int subMenuAtivado)
{
	int operacao = -1, subMenu = -1, reabrirMenu = 1, auxiliar = -1, indexAuxiliar = -1;
	
	system("cls");
	if (subMenuAtivado > 0)
		printf(AMARELO "Digite zero para voltar ao menu anterior\n\n" BRANCO);
	if (mensagemInicial > 0)
		printf(AZUL "Bem vindo gerente %i!\n\n" BRANCO, contas[index].usuario);
	if (subMenuAtivado > 0)
	{
		printf(CINZA "01 - Verificar informações de conta\n" BRANCO);
		printf(CINZA "02 - Alterar dados\n" BRANCO);
		if (subMenuAtivado == 1)
		{
			printf("\t04 - Todas\n");
			printf("\t05 - Específico\n");
		}
		else if (subMenuAtivado == 2)
		{
			printf("\t06 - Tipo de banco\n");
			printf("\t07 - Tipo de conta\n");
			printf("\t08 - Bloqueio / desbloqueio de conta\n");
			printf("\t09 - Ativar / desativar conta\n");
			printf("\t10 - Trocar senha de conta\n");
		}
		printf(CINZA "03 - Criar nova conta\n" BRANCO);
	}
	else
	{
		printf("01 - Verificar informações de conta\n");
		printf("02 - Alterar dados\n");
		printf("03 - Criar nova conta\n");
	}
	printf("00 - Sair\n\n");
	
	while ((operacao >= 1 || operacao <= 3) && subMenuAtivado <= 0)
	{
		printf("Digite a operação deseja realizar: ");
		scanf("%i", &operacao);
		
		switch (operacao)
		{
			case 1:
				menuInicialGerente(index, 0, operacao);
				
				while ((subMenu < 4  || subMenu > 5) && subMenu != 0)
				{
					printf("Digite a operação deseja realizar: ");
					scanf("%i", &subMenu);
					
					switch (subMenu)
					{
						case 4:
							system("cls");
							printf(AMARELO "Digite zero para voltar ao menu anterior\n\n" BRANCO);
							
							for (auxiliar = 0; auxiliar < MAXIMO_CONTAS; auxiliar++)
							{
								if (contas[auxiliar].usuario > 0 && contas[auxiliar].tipoUsuario != 2)
								{
									mostrarInformacoesConta(auxiliar, 1, 0, 1, 0, 0);	
									printf(AMARELO "\n--------------------------------------\n" BRANCO);
								}
							}
							sair(0);
						break;
						case 5:
							while ((auxiliar < 0 || indexAuxiliar < 0 || contas[indexAuxiliar].tipoUsuario > 1) && auxiliar != 0)
							{
								printf("Usuário: ");
								scanf("%i", &auxiliar);
								
								if (auxiliar < 0)
									printf(VERMELHO "Usuário inválido!\n\n"  BRANCO);
								else if (auxiliar != 0)
								{
									indexAuxiliar = pegarIndexConta(auxiliar, 0);
									
									if (indexAuxiliar < 0)
										printf(VERMELHO "Esse usuário não existe!\n\n" BRANCO);
									else if (contas[indexAuxiliar].tipoUsuario > 1)
										printf(AZUL "Não é permitido acessar de conta de gerente!\n\n" BRANCO);
									else
										mostrarInformacoesConta(indexAuxiliar, 1, 0, 1, 1, 1);
								}
							}
						break;
						case 0:
							menuInicialGerente(index, 0, 0);
						break;
						default:
							printf(VERMELHO "Operação inválida!\n\n" BRANCO);
						break;
					}
				}
			break;
			case 2:
				menuInicialGerente(index, 0, operacao);
				
				while ((subMenu < 6 || subMenu > 10) && subMenu != 0)
				{
					printf("Digite a operação deseja realizar: ");
					scanf("%i", &subMenu);
					
					if (subMenu > 5 && subMenu < 11)
					{
						system("cls");
						
						while ((auxiliar < 0 || indexAuxiliar < 0 || contas[indexAuxiliar].tipoUsuario > 1) && auxiliar != 0)
						{
							printf("Usuário: ");
							scanf("%i", &auxiliar);
							
							if (auxiliar < 0)
								printf(VERMELHO "Usuário inválido!\n\n" BRANCO);
							else
							{
								indexAuxiliar = pegarIndexConta(auxiliar, 0);
								
								if (indexAuxiliar < 0)
									printf(VERMELHO "Esse usuário não existe!\n\n" BRANCO);
								else if (contas[indexAuxiliar].tipoUsuario > 1)
									printf(AZUL "Não é permitido acessar de conta de gerente!\n\n" AZUL);
								else
									trocarInformacao(1, subMenu, indexAuxiliar);
							}
						}
					}
					else if (subMenu == 0)
						menuInicialGerente(index, 0, 0);
					else
						printf(VERMELHO "Operação inválida!\n\n" BRANCO);
				}
			break;
			case 3:
				criarConta(1);
			break;
			case 0:
				menuPrincipal();
			break;
			default:
				printf(VERMELHO "Operação inválida!\n\n" BRANCO);
				reabrirMenu = 0;
			break;
		}
		
		if (reabrirMenu == 1)
			menuInicialGerente(index, 0, 0);

		reabrirMenu = 1;
	}
}

void trocarInformacao(int gerente, int subMenu, int index)
{
	int auxiliar = -1, trocado = -1, perguntarSair = 1;
	
	if (gerente > 0)
	{
		switch (subMenu)
		{
			case 6:
				while (auxiliar < 0 || auxiliar > 99)
				{
					printf("Tipo de banco (01 até 99): ");
					scanf("%i", &auxiliar);
					
					if (auxiliar < 0 || auxiliar > 99)
						printf(VERMELHO "Não existe esse tipo de banco!\n" BRANCO);
					else if (auxiliar != 0)
						contas[index].tipoBanco = auxiliar;
				}
			break;
			case 7:
				while (auxiliar < 0 || auxiliar > 2)
				{
					printf("Tipo de conta (1-CORRENTE | 2-POUPANÇA): ");
					scanf("%i", &auxiliar);
					
					if (auxiliar < 0 || auxiliar > 2)
						printf(VERMELHO "Tipo de conta inválido!\n" BRANCO);
					else if (auxiliar != 0)
						contas[index].tipoConta = auxiliar;
				}
			break;
			case 8:
				trocado = contas[index].bloqueado;
				
				while (auxiliar < 0 || auxiliar > 2)
				{
					printf("Bloquear (1-SIM | 2-NÃO): ");
					scanf("%i", &auxiliar);
					
					if (auxiliar < 0 || auxiliar > 2)
						printf(VERMELHO "Valor inválido!\n" BRANCO);
				}
				
				if (trocado != contas[index].bloqueado)
				{
					perguntarSair = 0;
					trocarSenha(1, index);
				}
				contas[index].bloqueado = auxiliar == 1;
				
			break;
			case 9:
				while (auxiliar < 0 || auxiliar > 2)
				{
					printf("Ativar (1-SIM | 2-NÃO): ");
					scanf("%i", &auxiliar);
					
					if (auxiliar < 0 || auxiliar > 2)
						printf(VERMELHO "Valor inválido!\n" BRANCO);
					else if (auxiliar != 0)
						contas[index].ativa = auxiliar == 1;
				}
			break;
			case 10:
				perguntarSair = 0;
				trocarSenha(1, index);
			break;
		}
		
		if(perguntarSair > 0)
		{
			printf(AZUL "Operação realizada com sucesso!\n" BRANCO);
			sair(0);
		}
	}
}

void depositar(int index)
{
	float valor = -1.0;
	
	system("cls");
	printf(AMARELO "Digite zero para voltar ao menu anterior\n\n" BRANCO);
	
	while(valor < 0)
	{
		printf("Valor: ");
		scanf("%f", &valor);
		
		if (valor < 0)
			printf(VERMELHO "Não é possível depositar valores menores de R$ 0,00\n\n" BRANCO);
	}
	
	if (valor != 0)
	{
		printf(AZUL "Operação realizada com sucesso!\n" BRANCO);
		contas[index].saldo += valor;
		sair(0);
	}
}

void retirar(int index)
{
	float valor = -1.0;
	
	system("cls");
	printf(AMARELO "Digite zero para voltar ao menu anterior\n\n" BRANCO);
	
	while (valor < 0 || contas[index].saldo < valor)
	{
		printf("Valor: ");
		scanf("%f", &valor);
		
		 if (valor < 0)
			printf(VERMELHO "Não é possível retirar valores menores de R$ 0,00\n\n" BRANCO);
		else if (contas[index].saldo < valor)
			printf(VERMELHO "A conta não possui o valor de R$ %.2f\n\n" BRANCO, valor);
	}

	printf("\n");
	if (valor > 0 && solicitarSenhaAtual(index, 0, 1) == 1)
		contas[index].saldo -= valor;
}

void transferir(int index, int situacaoInvertida)
{
	int usuarioDestino = -1, indexDestino = -1, tipoBancoDestino = -1, aceita = -1, usuarioAlvo = -1;
	float valor = -1.0, valorAntigo = -1.0;
	
	system("cls");
	printf(AMARELO "Digite zero para voltar ao menu anterior\n\n" BRANCO);
	
	while (usuarioDestino < 0 || valor < 0 || tipoBancoDestino < 0)
	{
		while(tipoBancoDestino < 0 || tipoBancoDestino > 99)
		{
			printf("Banco do destinatário (01 até 99): ");
			scanf("%i", &tipoBancoDestino);
			
			if (tipoBancoDestino < 0 || tipoBancoDestino > 99)
				printf(VERMELHO "Não existe esse tipo de banco!\n\n" BRANCO);
		}
		
		if (tipoBancoDestino > 0)
		{
			while((usuarioDestino == contas[index].usuario || indexDestino < 0) && usuarioDestino != 0)
			{
				printf("Usuario de destino: ");
				scanf("%i", &usuarioDestino);
				
				if (usuarioDestino < 0)
					printf(VERMELHO "Usuário inválido!\n\n" BRANCO);
				else if (usuarioDestino > 0)
				{
					indexDestino = pegarIndexConta(usuarioDestino, tipoBancoDestino);
					
					if (situacaoInvertida > 0)
					{
						valorAntigo = usuarioDestino;
						usuarioDestino = contas[index].usuario;
						contas[index].usuario = valorAntigo;
						
						aceita = indexDestino;
						indexDestino = index;
						index = aceita;
					}
						
					if (usuarioDestino == contas[index].usuario)
						printf(VERMELHO "Você não pode transferir para você mesmo!\n\n" BRANCO);
					else if (indexDestino == -1)
						printf(VERMELHO "Esse usuário não existe!\n\n" BRANCO);
					
					if (situacaoInvertida > 0)
					{
						valorAntigo = usuarioDestino;
						usuarioDestino = contas[index].usuario;
						contas[index].usuario = valorAntigo;
						
						valorAntigo = usuarioDestino;
						usuarioDestino = contas[index].usuario;
						contas[index].usuario = valorAntigo;
					}
				}
			}
		}
		else
		{
			usuarioDestino = 0;
			valor = 0;
		}
		
		if (usuarioDestino > 0 && contas[index].tipoBanco != contas[indexDestino].tipoBanco)
		{
			printf(AZUL "Para esse tipo de banco será cobrado uma taxa de 5%%\n\n" BRANCO);
			
			while (aceita < 1 || aceita > 2)
			{
				printf("Deseja continuar (1-SIM | 2-NÃO): ");
				scanf("%i", &aceita);
				
				if (aceita < 1 || aceita > 2)
					printf(VERMELHO "Resposta inválida\n" BRANCO);
			}
		}
		else
			aceita = 1;
		
		if (usuarioDestino > 0 && aceita == 1)
		{
			while (valor < 0 || contas[index].saldo < valor)
			{
				printf("Valor: ");
				scanf("%f", &valor);
				
				if (contas[index].tipoBanco != contas[indexDestino].tipoBanco)
				{
					valorAntigo = valor;
					valor *= 1.05;
				}
				
				if (valor < 0)
					printf(VERMELHO "Não é possível retirar valores menores de R$ 0,00\n\n" BRANCO);
				else if (contas[index].saldo < valor)
					printf(VERMELHO "A conta não possui o valor de R$ %.2f\n\n" BRANCO, valor);
			}
		}
	}
	
	if (usuarioDestino > 0 && valor > 0 && solicitarSenhaAtual(index, 1, 1) == 1)
	{
		contas[index].saldo -= valor;
		
		if (contas[index].tipoBanco != contas[indexDestino].tipoBanco)
			valor = valorAntigo;
			
		contas[indexDestino].saldo += valor;
	}
}

void menuEmprestimo(int index)
{
	int operacao = -1;
	double juros = 0.0, maximo = 0.0;
	
	system("cls");
	printf(AMARELO "Digite zero para voltar ao menu anterior\n\n" BRANCO);
	
	if (contas[index].tipoConta == 1)
	{
		printf("01 - Básico\n");
		printf("02 - Simples\n");
		printf("03 - Composto\n\n");
	}
	else
	{
		printf("01 - Facilitado\n");
		printf("02 - Complementar\n\n");
	}
	
	while (operacao < 0 || operacao > 3)
	{
		printf("Digite a operação deseja realizar: ");
		scanf("%i", &operacao);
		
		if (operacao != 0)
		{
			if (contas[index].tipoConta == 1)
			{
				switch (operacao)
				{
					case 1:
						juros = 5.0;
						maximo = 500.0;
					break;
					case 2:
						juros = 20.0;
						maximo = 2000.0;
					break;
					case 3:
						juros = 110.0;
						maximo = 10000.0;
					break;
					default:
						printf(VERMELHO "Operação inválida!\n\n" BRANCO);
					break;
				}
			}
			else
			{
				switch (operacao)
				{
					case 1:
						juros = 1.2;
						maximo = 2000.0;
					break;
					case 2:
						juros = 5.0;
						maximo = 20000.0;
					break;
					default:
						printf(VERMELHO "Operação inválida!\n\n" BRANCO);
					break;
				}
			}
		}
	}
	
	if (operacao >= 1 && operacao <= 2 + contas[index].tipoConta == 1)
	{
		printf(AZUL "\nEssa opção tem um limite de empréstimo de R$ %.2f e tem um juros de %.1f%%\n" BRANCO, maximo, juros);
		emprestimoValor(juros, maximo);
	}
}

void emprestimoValor(double juros, double maximo)
{
	int meses = -1;
	float valor = - 1.0, valorTotal = 0.0;
	
	while (valor < 0 || valor > maximo)
	{
		printf("Valor: ");
		scanf("%f", &valor);
		
		 if (valor < 0)
			printf(VERMELHO "O valor não pode ser menor que R$ 0,00\n\n" BRANCO);
		else if (valor > maximo)
			printf(AZUL "O máximo disponível nessa opção é de R$ %.2f\n\n" BRANCO, maximo);
	}
	
	if (valor != 0)
	{
		while (meses < 0)
		{
			printf("Prazo(mês): ");
			scanf("%i", &meses);
			
			if(meses < 1) 
				printf(VERMELHO "Não é possível fazer um emprestimo com parcelas menores que 1!\n\n" BRANCO);	
		}
	}
	
	if (valor != 0 && meses != 0)
	{
		valorTotal = valor * ((juros / 100) + 1);
		
		printf("Valor mensal a pagar é de R$ %.2f\n", valorTotal / meses);
		printf("Valor total a pagar é de R$ %.2f\n", valorTotal);
		sair(1);
	}
}

void pagarConta(int index, int taxa)
{
	float valor = -1.0;
	
	system("cls");
	printf(AMARELO "Digite zero para voltar ao menu anterior\n\n" BRANCO);
	if (taxa > 0)
		printf(AZUL"Taxa para fazer a transação é de R$ %i,00\n\n" BRANCO, taxa);
	
	while (valor < 0 || contas[index].saldo < valor + taxa)
	{
		printf("Valor da conta: ");
		scanf("%f", &valor);
		
		if (valor < 0)
			printf(VERMELHO "O valor da conta não pode ser menor que R$ 0,00\n\n" BRANCO);
		else if (contas[index].saldo < valor + taxa)
			printf(VERMELHO "Seu saldo é insuficiente para pagar essa conta!\n\n" BRANCO);
		else if (valor != 0 && solicitarSenhaAtual(index, 1, 1) == 1)
		{
			contas[index].saldo -= valor + taxa;
		}
	}
}

void trocarSenha(int gerente, int index)
{
	int senhaNova1 = -1, senhaNova2 = 0;
	
	if (gerente > 0 || contas[index].trocarSenha > 0 || solicitarSenhaAtual(index, 1, 0) == 1)
	{
		if (gerente < 1)
		{
			system("cls");
			printf(AMARELO "Digite zero para voltar ao menu anterior\n\n" BRANCO);
		}
		
		if (contas[index].trocarSenha > 0)
				printf(VERMELHO "Essa senha é provisória e precisa ser trocada!\n" BRANCO);
		else if (contas[index].bloqueado > 0)
				printf(AZUL "\nÉ necessário trocar a senha da conta desbloqueada\n" BRANCO);
		
		while((senhaNova1 == contas[index].senha || senhaNova1 != senhaNova2) && senhaNova1 != 0)
		{
			printf("Digite a nova senha: ");
			scanf("%i", &senhaNova1);
			
			if (senhaNova1 == contas[index].senha)
				printf(VERMELHO "A nova senha não pode ser igual a senha atual!\n\n" BRANCO);
			else if (senhaNova1 < 0)
				printf(VERMELHO "Senha inválida!\n\n" BRANCO);
			else if (senhaNova1 > 0)
			{
				printf("\nDigite a nova senha novamente: ");
				scanf("%i", &senhaNova2);
				
		 	    if (senhaNova1 == senhaNova2)
		 	    {
					contas[index].senha = senhaNova1;
		 	    	contas[index].trocarSenha = 0;
					
					if (gerente > 0)
		 	    		contas[index].trocarSenha = 1;
		 	    		
		 	    	break;
				}
				else
					printf(VERMELHO "As senhas digitadas não são iguais!\n\n" BRANCO);
			}
		}
	}
	
	if (gerente > 0 || senhaNova1 == senhaNova2 && senhaNova2 > 0)
	{
		printf(AZUL "Operação realizada com sucesso!\n" BRANCO);
		sair(0);
	}
}

int solicitarSenhaAtual(int index, int mensagemInicial, int mensagemSucesso)
{
	int senhaAtual = -1, tentativas = 3;
	
	if (mensagemInicial > 0)
	{
		system("cls");
		printf(AMARELO "Digite zero para voltar ao menu anterior\n\n" BRANCO);	
	}
	
	if (contas[index].ativa < 1 || contas[index].bloqueado > 0)
		tentativas = 1;
	
	while(senhaAtual != 0 && tentativas > 0 && contas[index].senha != senhaAtual)
	{	
		fflush(stdin);
		printf("Digite sua senha atual: ");
		printf(PRETO);
		scanf("%i", &senhaAtual);
		printf(BRANCO);
		
		tentativas--;
		
		if (senhaAtual != 0 && contas[index].senha != senhaAtual)
		{
			if (contas[index].ativa > 0 && contas[index].bloqueado < 1)
				printf(VERMELHO "Senha inválida!\n" BRANCO);
			else
				tentativas = -1;
			
			if (tentativas > 0)
				printf(AZUL "Restam %i tentativas antes de bloquear\n\n" BRANCO, tentativas);	
			else if (tentativas == 0)
			{
				senhaAtual = 0;
				contas[index].bloqueado = 1;
				printf(VERMELHO "A conta foi bloqueada, por favor procure um gerente!\n" BRANCO);
				sair(mensagemInicial);
				menuPrincipal();
			}
		}
	}
	
	if (contas[index].ativa < 1)
		printf(VERMELHO "Está conta está desativada, por favor procure um gerente!\n" BRANCO);
	else if (contas[index].bloqueado > 0)
		printf(VERMELHO "Está conta está bloqueada, por favor procure um gerente!\n" BRANCO);
	
	if (contas[index].senha == senhaAtual)
	{
		if (contas[index].trocarSenha > 0)
		{
			tentativas = -1;
			trocarSenha(0, index);
			senhaAtual = contas[index].senha;
		}
		else if (mensagemSucesso > 0)
		{
			printf(AZUL "Operação realizada com sucesso!\n" BRANCO);
			sair(0);
		}
	}
	
	if (contas[index].bloqueado > 0 || contas[index].ativa < 1)
		sair(0);
	else if (tentativas >= 0)
		system("cls");
		
	if (contas[index].trocarSenha > 0 || contas[index].bloqueado > 0 || contas[index].ativa < 1 || senhaAtual == 0)
		return 0;
	else if (contas[index].senha == senhaAtual)
		return 1;
	else
		return -1;
}

void sair(int mostrarMensagem)
{
	int saida = -1;
	
	if (mostrarMensagem > 0)
		printf(AMARELO "\nDigite zero para voltar ao menu anterior\n" BRANCO);
	else
		printf("\n");
	
	while (saida != 0)
	{
		scanf("%i", &saida);
		
		if (saida != 0)
			printf(VERMELHO "Valor digitado inválido!\n\n" BRANCO);
	}
}
