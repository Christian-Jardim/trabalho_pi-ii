#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEMINST "meminst.mem" //arquivo memoria de instruções
#define MEMDADOS "memdados.dat" //arquivo memoria de dados
#define INSTRUCAO 16 //instrução com 16 bits




//STRUCTS e ENUMS
typedef enum{
    Tipo_R,
    Tipo_J,
    Tipo_I,
    Tipo_OUTROS
} Tipo_Instrucao;

typedef struct {
    int regis[8];
}Reg;

typedef struct {
    int opcode;
    int rs[4];
    int rt[3];
    int rd[3];
    int funct[3];
    int imm[6];
    int addr[7];
    Tipo_Instrucao instrucao;
}Deco;




//NOMES DAS FUNÇÕES
int contarlinhas(const char *arquivo);
char **alocMemInstr(int n);
void liberaMem(char **pmem);
void carregaMemInst(const char *arquivo, char **pmem, int n);
void printMemory(char **pmem, int n);
void printReg(Reg reg);
int binario_para_inteiro(const char *instrucao, int inicio, int tamanho);
void menu();




//PROGRAMA PRINCIPAL
int main() {
    
    menu();
    
    return 0;
}




//MENU
void menu(){
    
    Reg reg;
    Deco dec;
    char **meminst = NULL, instrucao[16];
    int op, nlinhas;
    
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

	switch (op) {
    case 1:
        //conta número de linhas do arquivo lido
        nlinhas = contarlinhas(MEMINST);
        //aloca memoria para memoria de instruções
        meminst = alocMemInstr(nlinhas);
        //carrega memoria com os dados do arquivo lido
        carregaMemInst(MEMINST, meminst, nlinhas);
		break;
	
    case 2:
        printf("Em desenvolvimento.");
		break;
	
    case 3:
        //conta número de linhas do arquivo lido
        nlinhas = contarlinhas(MEMINST);
        //imprime memória de instruções
        printMemory(meminst, nlinhas);
		break;

	case 4:
        printReg(reg);
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
		liberaMem(meminst);
		printf("VOCÊ SAIU!!!");
		break;
		} 
		
	}while(op != 11);
}

void printReg(Reg reg) {
  for(int i=0; i<8; i++){  
		printf("REGISTRADOR [%d] - %d\n", i, reg.regis[i]);
	}
}




//FUNÇÕES IMPLEMENTADAS
int contarlinhas(const char *arquivo)
{
    char c;
    int contador=0;
    // abre o arquivo em modo leitura
    FILE *arq = fopen (arquivo, "r");
    if (!arq)
    {
        perror ("Erro ao abrir arquivo");
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
        return NULL;
    }
    for (int i = 0; i < n; i++)
    {
        pmem[i] = (char *) malloc(sizeof(char) * INSTRUCAO + 1);
        if (pmem[i] == NULL)
        {
            printf("Erro de alocação!");
            return NULL;
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

void carregaMemInst(const char *arquivo, char **pmem, int n)
{
    // abre o arquivo em modo leitura
    FILE *arq = fopen (arquivo, "r");
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



int binario_para_inteiro(const char *instrucao, int inicio, int tamanho) {
    
    int valor=0;
    char binario[tamanho + 1];
    
    strncpy(binario, &instrucao[inicio], tamanho);
    
    char *resto_string;
    valor = strtol(binario, &resto_string, 2);
    
    return valor;
}