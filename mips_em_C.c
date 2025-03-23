#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEMINST "meminst.mem" //arquivo memoria de instruções
#define MEMDADOS "memdados.dat" //arquivo memoria de dados
#define INSTRUCAO 16 //instrução com 16 bits

//Funções
int contarlinhas(FILE* arq);
char **alocMemInstr(int n);
void liberaMem(char **pmem);
void carregaMemInst(FILE* arq, char **pmem, int n);
void printMemory(char **pmem, int n);

struct decodificacao
{
    char opcode[4];
    char rs[3];
    char rt[3];
    char rd[3];
    char funct[3];
    char imm[6];
    char addr[7];
};


int main()
{
    FILE* arquivo;
    struct decodificacao dec;
    char **meminst = NULL, instrucao[16];
    int op, nlinhas, opcode;

do {
	printf("\n *** MENU *** \n");
	printf("1 - Carregar memoria de instrucoes\n");
	printf("2 - Carregar memoria de dados\n");
	printf("3 - Imprimir memorias\n");
	printf("4 - Imprimir banco de registradores\n");
	printf("5 - Imprimir todo o simulador\n");
	printf("6 - Salvar .asm\n");
	printf("7 - Salvar .dat\n");
	printf("8 - Executar programa\n");
	printf("9 - Executar instrucao\n");
	printf("10 - Volta uma instrucao\n");
	printf("11 - Sair\n\n");
    printf("Escolher opção: ");
	scanf("%d", &op);

	do {
		if (op < 1 || op > 11) {
			printf("\nOpção inválida, digite novamente: ");
			scanf("%d", &op);
		}
	} while(op < 1 || op > 11);

	switch (op) 
    {
    case 1:
        // abre o arquivo em modo leitura
        arquivo = fopen (MEMINST, "r") ;
        if (!arquivo)
        {
            perror ("Erro ao abrir arquivo") ;
            exit (1) ;
        }

        nlinhas = contarlinhas(arquivo);
        rewind(arquivo);

        meminst = alocMemInstr(nlinhas);
        carregaMemInst(arquivo, meminst, nlinhas);

        // Fecha o arquivo
        fclose(arquivo);
		break;
	
    case 2:

        //teste para decodificação
        strcpy(instrucao, meminst[0]);
        printf("%s", instrucao);
        
        opcode = strtol(strncpy(dec.opcode, instrucao, 4), NULL, 2);
        printf("%d\n", opcode);

        printf("Em desenvolvimento.");
		break;
	
    case 3:
        nlinhas = contarlinhas(arquivo);
        //imprime memória de instruções
        printMemory(meminst, nlinhas);
		break;

	case 4:
        printf("Em desenvolvimento.");
        break;

	case 5:
        printf("Em desenvolvimento.");
        break;

	case 6:
        printf("Em desenvolvimento.");
		break;

	case 7:
        printf("Em desenvolvimento.");
		break;

	case 8:
        printf("Em desenvolvimento.");
		break;

	case 9:
        printf("Em desenvolvimento.");
		break;

	case 10:
        printf("Em desenvolvimento.");
		break;

	case 11:
		return 0;
		break;
	}
    } while(op != 11);

    liberaMem(meminst);

    return 0;
}

int contarlinhas(FILE* arq)
{
    char c;
    int contador=0;
    // abre o arquivo em modo leitura
    arq = fopen (MEMINST, "r") ;
    if (!arq)
    {
        perror ("Erro ao abrir arquivo") ;
        exit (1) ;
    }
    // Percorre o arquivo e conta as quebras de linha
    while (fread(&c, sizeof(char), 1, arq) == 1)
    {
        if (c == '\n') {
            contador++;
        }
    }
    fclose(arq);
    return contador;
}

char **alocMemInstr(int n)
{
    char **pmem;
    pmem = (char **) malloc(sizeof(char *) * n);
    if (pmem == NULL)
    {
        printf("Erro de alocação!");
        return 1;
    }
    for (int i = 0; i < n; i++)
    {
        pmem[i] = (char *) malloc(sizeof(char) * INSTRUCAO + 1);
        if (pmem[i] == NULL)
        {
            printf("Erro de alocação!");
            return 1;
        }
    }
    return pmem;
}

void liberaMem(char **pmem)
{
    for (int i = 0; i < 16; i++)
    {
        free(pmem[i]);
    }
    free(pmem);
}

void carregaMemInst(FILE* arq, char **pmem, int n)
{
    // abre o arquivo em modo leitura
    arq = fopen (MEMINST, "r");
    if (!arq)
    {
        perror ("Erro ao abrir arquivo") ;
        exit (1) ;
    }
    for (int i = 0; i < n; i++)
    {
        fgets(pmem[i], sizeof(char) * INSTRUCAO + 2, arq);
    }
    fclose(arq);
}

void printMemory(char **pmem, int n)
{
    if (pmem == NULL || *pmem == NULL)
    {
        printf("Memória vazia ou não alocada!");
        return;
    }
    for (int i = 0; i < n; i++)
    {
        printf("%s", pmem[i]);
    }
}
