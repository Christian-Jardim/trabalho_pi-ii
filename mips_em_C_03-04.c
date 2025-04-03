/*	0000/000 => ADD
	0000/010 => SUB
	0000/100 => AND
	0000/101 => OR
	0100	 => AADi
	1011	 => LW
	1111	 => SW
	1000	 => BEQ
	0010	 => J		*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEMINST "meminst.mem" //arquivo memoria de instrucoeses
#define MEMDADOS "memdados.dat" //arquivo memoria de dados

//STRUCTS e ENUMS
typedef enum {
	Tipo_R=0,
	Tipo_I=1,
	Tipo_J=2,
	Tipo_OUTROS=3
} Tipo_Instrucao;

struct instrucao
{
	char opcode[5];
	char rs[4];
	char rt[4];
	char rd[4];
	char funct[4];
	char imm[7];
	char addr[8];
};

typedef struct {
	int opcode;
	int rs;
	int rt;
	int rd;
	int funct;
	int imm;
	int addr;
	Tipo_Instrucao tipo;
} Deco;

//NOMES DAS FUNCOES
int contarlinhas(const char *arquivo);
int binarioParaDecimal(const char *bin);
void carregaMemInst(const char *arquivo, char mem[256][17]);
void printMemory(char mem[256][17], struct instrucao *inst, Deco *dec);
void printReg(int *reg);
void menu();
void progULA(Deco *inst, int *reg);
void copiarBits(const char *instrucao, char *destino, int inicio, int tamanho);
void decodificarInstrucao(const char *bin, struct instrucao *inst, Deco *dec);
void printInstrucao(Deco *dec);

//PROGRAMA PRINCIPAL
int main() 
{
	menu();

	return 0;
}

//MENU
void menu() 
{
	Deco dec;
	char meminst[256][17] = {{'\0'}};
	char memdado[256][17] = {{'\0'}};
	struct instrucao instrucao;
	int op, nlinhas, resul, registrador[8] = {0}, pc = 0;
	
	do {
		printf("\n\n *** MENU *** \n");
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
		printf("Sua escolha: ");
		scanf("%d", &op);

		switch (op) {
		case 1:
			//carrega memoria com os dados do arquivo lido
			carregaMemInst(MEMINST, meminst);
			break;

		case 2:
			printf("Em desenvolvimento.");
			break;

		case 3:
			//imprime memoria de instrucoes
			printMemory(meminst, &instrucao, &dec);
			break;

		case 4:
			printReg(registrador);
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
			printf("Em desenvolvimento.\n\n");
			
			decodificarInstrucao(meminst[pc], &instrucao, &dec);
			printInstrucao(&dec);
			progULA(&dec, registrador);
			if(dec->opckde == 7) {

			}

			pc++;
			
			break;

		case 10:
			printf("Em desenvolvimento.");
			break;

		case 11:
			printf("VOCE SAIU!!!");
			break;
		}

	} while(op != 11);
}

//FUNCOES IMPLEMENTADAS
void printReg(int *reg) {
	for(int i=0; i<8; i++) {
		printf("REGISTRADOR [%d] - %d\n", i, reg[i]);
	}
}

int contarlinhas(const char *arquivo)
{
	char c;
	int contador=1;
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

void carregaMemInst(const char *arquivo, char mem[256][17])
{
    // abre o arquivo em modo leitura
	FILE *arq = fopen (arquivo, "r");
	if (!arq)
	{
		perror ("Erro ao abrir arquivo") ;
		exit (1) ;
	}
	int i = 0;
	char linha[20]; // Buffer para leitura
	while (i < 256 && fgets(linha, sizeof(linha), arq)) {
        // Remover quebras de linha e caracteres extras
        linha[strcspn(linha, "\r\n")] = '\0';

        // Ignorar linhas vazias
        if (strlen(linha) == 0) {
            continue;
        }

        strncpy(mem[i], linha, 16); // Copia até 16 caracteres
        mem[i][16] = '\0'; // Garante terminação de string
        i++; // Avança corretamente para a próxima posição
    }
	fclose(arq);
}

void printMemory(char mem[256][17], struct instrucao *inst, Deco *dec)
{
    for (int i = 0; i < 256; i++)
    {
        if (mem[i][0] == '\0')
            continue;
        printf("\nIntrucao: %s\n", mem[i]);
        decodificarInstrucao(mem[i], inst, dec);
        printInstrucao(dec);
    }
}

void progULA(Deco *dec, int *reg)
{
	if (dec->opcode == 11)
	{
		reg[dec->rt] = dec->imm;
	}
	else if (dec->opcode == 4)
	{
		reg[dec->rt] = reg[dec->rs] + dec->imm;
	}
	else if (dec->opcode == 0 && dec->funct == 0)
	{
		reg[dec->rd] = reg[dec->rs] + reg[dec->rt];
	}
	else if (dec->opcode == 0 && dec->funct == 2)
	{
		reg[dec->rd] = reg[dec->rs] - reg[dec->rt];
	}
  else if (dec->opcode == 0 && dec->funct == 4)
	{
		reg[dec->rd] = reg[dec->rs] & reg[dec->rt];
  }
  else if (dec->opcode == 0 && dec->funct == 5)
	{
		reg[dec->rd] = reg[dec->rs] | reg[dec->rt];
  }
}

// copia os bits da instrução para cada campo da struct instrucao
void copiarBits(const char *instrucao, char *destino, int inicio, int tamanho)
{
    strncpy(destino, instrucao + inicio, tamanho); // Copia os bits desejados
    destino[tamanho] = '\0';  // Adiciona o terminador de string
}

// decodifica a instrucao e armazena os valores na struct do tipo Deco ja no formato int
void decodificarInstrucao(const char *bin, struct instrucao *inst, Deco *dec)
{
  copiarBits(bin, inst->opcode, 0, 4);    // Copia os 4 bits do opcode (4 bits)
  dec->opcode = binarioParaDecimal(inst->opcode);
	copiarBits(bin, inst->rs, 4, 3);        // Copia os 3 bits do rs
  dec->rs = binarioParaDecimal(inst->rs);
	copiarBits(bin, inst->rt, 7, 3);        // Copia os 3 bits do rt
  dec->rt = binarioParaDecimal(inst->rt);
	copiarBits(bin, inst->rd, 10, 3);       // Copia os 3 bits do rd
  dec->rd = binarioParaDecimal(inst->rd);
	copiarBits(bin, inst->funct, 13, 3);    // Copia os 3 bits do funct
  dec->funct = binarioParaDecimal(inst->funct);
	copiarBits(bin, inst->imm, 10, 6);      // Copia os 6 bits do imm
  dec->imm = binarioParaDecimal(inst->imm);
	copiarBits(bin, inst->addr, 9, 7);     // Copia os 7 bits do addr
	dec->addr = binarioParaDecimal(inst->addr);
}

// Função para imprimir a instrução
void printInstrucao(Deco *dec)
{
    printf("Opcode: %d  ", dec->opcode);
    printf("rs: %d  ", dec->rs);
    printf("rt: %d  ", dec->rt);
    printf("rd: %d  ", dec->rd);
    printf("funct: %d  ", dec->funct);
    printf("imm: %d  ", dec->imm);
    printf("addr: %d", dec->addr);
}

// converte de binario para decimal
int binarioParaDecimal(const char *bin)
{
    return (int)strtol(bin, NULL, 2);
}
