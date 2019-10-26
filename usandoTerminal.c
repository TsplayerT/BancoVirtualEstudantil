#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <locale.h>

#define DEBUG 1

char *concatenarPonteiros();
char *criarArquivoConfiguracao(char *nomeArquivo);

int main (int argc, char *argv[])
{
	setlocale(LC_CTYPE, "");
	//system("start C:\Fontes\netcorp.net");

    //printf("%i", existeDiretorio("C:\\Fontes\\netcorp.net"));
    //printf("%i", existeArquivo(ARQUIVO_CONFIGURACAO));
    
	char *nomeExecutavel = strrchr(argv[0], '\\');
	if (DEBUG == 1)
	{
		printf("diretorioExecutavel = %s\n", argv[0]);
		printf("nomeExecutavel = %s\n\n", nomeExecutavel ? ++nomeExecutavel : argv[0]);	
	}
    criarArquivo("asd");
	
	return 0;
}

int existeDiretorio(char *diretorio)
{
    struct stat buffer;
    return stat(diretorio, &buffer) == 0 && S_ISDIR(buffer.st_mode);
}

int existeArquivo(char *arquivo)
{
	FILE *file = fopen(arquivo,"r");
        
	if (file != NULL)
        fclose(file);
    
    return file != NULL;
}

char *concatenarPonteiros(char *ponteiro1, char *ponteiro2)
{
	int index = 0, indexFinal = 0;
	char *novoPonteiro = malloc((strlen(ponteiro1) + strlen(ponteiro2)) * sizeof (char));
	
	for (index = 0; index < strlen(ponteiro1); index++)
	{
		*(novoPonteiro + index) = *(ponteiro1 + index);
	}
	indexFinal = index;
	for (index = 0; index < strlen(ponteiro2); index++)
	{
		*(novoPonteiro + (indexFinal + index)) = *(ponteiro2 + index);
	}
	
	return novoPonteiro; 
}

void criarArquivo(char *nomeArquivo)
{
	if (DEBUG == 1)
		printf("criando arquivo %s\n", nomeArquivo);
		
	char *pastaExecutavel = "\\trabalhoCinema";
	char *nomeArquivoComBarra = concatenarPonteiros("\\", nomeArquivo);
	char *nomeArquivoComExtensao = concatenarPonteiros(nomeArquivoComBarra, ".config");
	char *diretorio = strcat(getenv("APPDATA"), pastaExecutavel);
	char *diretorioArquivo = strcat(diretorio, nomeArquivoComExtensao);
	
	if (DEBUG == 1)
	{
		printf("diretorio = %s\n", diretorio);
		printf("diretorioArquivo = %s\n", diretorioArquivo);
	}
	
	//como pegar apenas 1 caracter de um ponteiro
	//printf("%c\n", *(ARQUIVO_CONFIGURACAO + 1));
	
	if (DEBUG == 1)
		printf("verificando se existe o diretório\n");
	if (existeDiretorio(diretorio) == 0)
	{
		if (DEBUG == 1)
			printf("criando diretório!\n");
			
		char *comandoCriarDiretorio = concatenarPonteiros("mkdir ", diretorio);
		system(comandoCriarDiretorio);
		
		if (DEBUG == 1)
			printf("diretorio criado!\n");
	}
	
	if (DEBUG == 1)
		printf("verificando se existe o arquivo\n");
	if (existeArquivo(diretorioArquivo) == 0)
	{
		if (DEBUG == 1)
			printf("criando arquivo\n");
			
		char *comandoCriarArquivo = concatenarPonteiros("type NUL > ", diretorioArquivo);
		system(comandoCriarArquivo);
		
		if (DEBUG == 1)
			printf("arquivo criado!\n");
	}
}












