#include <stdio.h>
#include <stdlib.h>

int main() {
	int op;
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
		scanf("%i", &op);
		
		do {
			if (op < 1 || op > 11) {
				printf("\nOpcao invalida, digite novamente: ");
				scanf("%i", &op);
			}
		} while(op < 1 || op > 11);

		switch (op) {
		case 1:
			
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		case 8:
			break;
		case 9:
			break;
		case 10:
			break;
		case 11:
			return 0;
			break;
		}
	} while(op != 11);

}
