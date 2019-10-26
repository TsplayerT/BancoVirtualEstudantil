#include <stdio.h>
#include<locale.h>


int main()
{
	setlocale(LC_ALL,"Portuguese");
	int menu1,menu2;
	int senha=1203,s=2;
	int senha1,senha2,senha3;

	do
	{
		printf("\nDigite a operação deseja realizar: \n1.Conectar\n2.Criar Senha\n3.Sair\n");
		scanf("%i", &menu1);
		
		while (menu1<3 && menu1>=1)
		{
			switch(menu1)
			{
				case 1:
					do
					{
						printf("\nDigite a senha (4 digitos): ");
						scanf("%i", &senha1);
						if(senha1!=senha)
						{
							printf("\nSenha incorreta, restam %i tentativas antes de ser bloqueada!",s);
							s--;
						}
						printf("\nSenha bloqueada, dirija-se a agência mais perto para realizar o desbloqueio!");
					}
					while (s!=-1);
					if(senha1==senha)
					printf("Bem-vindo!");
					menu1=0;
					break;
				case 2:
					printf("\nDigite a senha (4 digitos) a ser cadastrada: ");
					scanf("%i", &senha2);
					printf("\nDigite a senha (4 digitos) novamente: ");
					scanf("%i", &senha3);
					if(senha2 != senha3)
					{
						printf("\nAs senhas digitadas não coincidem, favor digite a mesma senha nos campos para ser válidada! ");
						menu1=2;
					}
					else if (senha2==senha3)
					{
						senha=senha3;
						printf("\nSua senha atual é:%i", senha);
						menu1=0;
					}
					
					break;	
			}
		}
		
	
	}
	while(menu1 != 3);
	return 0;
}
