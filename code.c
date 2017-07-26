
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct jogo {
	int     nrlin;      /// máximos do tabuleiro
	int     nrcol;
	int     lin;        /// jogadas
	int     col;
} jogo;

typedef struct linha {
	int dados;          /// 1linha, 2coluna, 3*, 4X
}matriz;

typedef struct guardar guardar, *pguardar;

struct guardar {
	int lin;
	int col;
	int nrjogada;
	pguardar prox;
};


void dimensaoTabuleiro(jogo *x)
{
	do {
		printf("\nNovo tabuleiro:\n");
		printf(" - Nr de linhas  (4 a 8) : ");
		scanf("%d", &x->nrlin);
		printf(" - Nr de colunas (6 a 10): ");
		scanf("%d", &x->nrcol);

		if (x->nrlin <4 || x->nrlin>8) {
			system("cls");
			printf("O nr de linhas deve estar compreendido entre 4 e 8! \n");
		}
		if (x->nrcol<6 || x->nrcol>10) {
			system("cls");
			printf("O nr de colunas deve estar compreendido entre 6 e 10! \n");
		}
		if (x->nrlin >= x->nrcol) {
			system("cls");
			printf("O nr de colunas deve ser superior ao nr de linhas! \n");
		}
	} while (x->nrlin<4 || x->nrlin>8 && x->nrcol<6 || x->nrcol>10 || x->nrlin >= x->nrcol);
	system("cls");
}

matriz** preencherTabuleiro(jogo dados, matriz **tabuleiro)
{
	int i, j;

	tabuleiro = (matriz **)malloc(sizeof(matriz *) * dados.nrlin + 1);  //reserva memoria para as linhas iniciais
																												// aloca todas as linhas na primeira coluna
	for (i = 0; i <= dados.nrlin; i++) {

		tabuleiro[i] = (matriz *)malloc(sizeof(matriz) * dados.nrcol + 1);  //reserva memoria para as colunas iniciais
																												// percorre a coluna alocada , alocando cada linha
		for (j = 0; j <= dados.nrcol; j++) {                        //preenche com valores as celulas da matriz
			if (i == 0) {
				tabuleiro[i][j].dados = 1;
			}
			else if (j == 0) {
				tabuleiro[i][j].dados = 2;
			}
			else {
				tabuleiro[i][j].dados = 3;
			}
		}
	}

	tabuleiro[0][0].dados = 0;
	tabuleiro[i - 1][j - 1].dados = 4;

	return tabuleiro;
}

void mostrarTabuleiro(jogo dados, matriz **tabuleiro)
{
	int i, j;

	printf("\n");

	for (i = 0; i <= (dados.nrlin); i++) {

		printf("  ");

		for (j = 0; j <= (dados.nrcol); j++) {

			if (tabuleiro[i][j].dados == 0)
				printf("  ");

			if (tabuleiro[i][j].dados == 1)
				printf("%2c", j + 64);

			if (tabuleiro[i][j].dados == 2)
				printf("%2d", i);

			if (tabuleiro[i][j].dados == 3)
				printf("%2c", '*');

			if (tabuleiro[i][j].dados == 4)
				printf("%2c", 'X');

		}
		printf("\n");
	}

}

void jogar(jogo *x, int jogador, matriz **tabuleiro)
{
	printf("\n    A jogada tem o formato: CL (Coluna Linha) \n");

	char jogada[3];

	do {
		printf("     - Jogada: ");
		scanf("%s", &jogada);

		x->lin = (int)jogada[1] - 48;
		x->col = (int)jogada[0] - 64;

		if (x->lin<1 || x->lin > x->nrlin || x->col<1 || x->col>x->nrcol) {
			printf("\nJogada invalida! Deve escolher um campo que integre o tabuleiro!\n");
			jogada[0] = '\0';
		}
		else if (tabuleiro[x->lin][x->col].dados == 0) {
			printf("\nJogada invalida! Deve escolher um campo com comida!\n");
			jogada[0] = '\0';
		}

	} while (x->lin<1 || x->lin>x->nrlin || x->col<1 || x->col>x->nrcol || tabuleiro[x->lin][x->col].dados == 0);

}

void jogadaIA(jogo *x, matriz **tabuleiro)
{
	do {
		x->lin = rand() % x->nrlin + 1;
		x->col = rand() % x->nrcol + 1;
	} while (tabuleiro[x->lin][x->col].dados == 0);

}

pguardar guardarJogada(jogo x, int jogador, pguardar jogadas, int nrjogada)
{
	// Guarda os valores de cada jogada numa lista ligada

	pguardar novo = malloc(sizeof(guardar));
	pguardar aux;

	if (!novo) {
		printf("Erro a reservar memoria\n");
		return jogadas;
	}

	novo->col = x.col;
	novo->lin = x.lin;
	novo->nrjogada = nrjogada;
	novo->prox = NULL;

	if (jogadas == NULL)
		jogadas = novo;
	else {
		aux = jogadas;
		while (aux->prox != NULL)
			aux = aux->prox;
		aux->prox = novo;
	}

	return jogadas;
}

void atualizarTabuleiro(jogo x, matriz **tabuleiro)
{
	int i, j;

	for (i = 1; i <= (x.col); i++) {
		for (j = 1; j <= (x.lin); j++) {
			tabuleiro[j][i].dados = 0;
		}
	}
}

void mostrarJogadas(pguardar jogadas)
{
	system("cls");
	printf("Jogadas realizadas:\n");

	if (!jogadas)
        printf("\n  Ainda nao foram realizadas jogadas!\n\n");

	while (jogadas) {
		printf(" Jogada %d: %c%d\n", jogadas->nrjogada, jogadas->col + 64, jogadas->lin);
		jogadas = jogadas->prox;
	}
	system("pause");
}

int menuDoJogo(jogo x, matriz **tabuleiro, int opcao, int jogador)
{
    while (opcao<1 || opcao>4) {
        printf("\nJogador %d: \n 1 - Realizar jogada\n 2 - Ver jogadas\n 3 - Guardar jogo e sair\n 4 - Render-se\n  Escolha: ", jogador);
        scanf("%d", &opcao);
        if (opcao<1 || opcao>4) {
            printf("\n\nA escolha deve ser de 1 a 4!\n");
            opcao = 0;
            system("pause");
            system("cls");
            mostrarTabuleiro(x, tabuleiro);
        }
    }
    return opcao;
}

int trocarJogador(int jogador)
{
	if (jogador == 1)
		jogador = 2;
	else
		jogador = 1;

	return jogador;
}

void guardarBin(jogo x, int nrjogadas, pguardar jogadas, int modoJogo)
{
	pguardar aux;

	FILE *f;
	f = fopen("jogoGuardado.dat", "wb");

	if (!f) {
		printf("\n\nErro ao criar o ficheiro");
		system("pause");
		return;
	}

	nrjogadas--;

	fwrite(&x.nrlin, sizeof(int), 1, f);
	fwrite(&x.nrcol, sizeof(int), 1, f);
	fwrite(&nrjogadas, sizeof(int), 1, f);
	fwrite(&modoJogo, sizeof(int), 1, f);


	while (jogadas) {
		fwrite(&jogadas->col, sizeof(int), 1, f);
		fwrite(&jogadas->lin, sizeof(int), 1, f);
		fwrite(&jogadas->nrjogada, sizeof(int), 1, f);

		aux = jogadas;
		jogadas = jogadas->prox;
		free(aux);
	}

	fclose(f);

	printf("\n\nJogo guardado com sucesso!\n");
	system("pause");
	system("cls");
}

void imprimirTXT(jogo dados, pguardar jogadas) // por implementar
{
	FILE *f;
	f = fopen("ultimoJogo.txt", "a");		// Append

	if (!f) {
		printf("\n\nErro ao escrever no ficheiro");
		system("pause");
		return;
	}

	int i, j, jogador=1, impressao=1;

	pguardar aux = jogadas;
	matriz **tabuleiro = NULL;
	tabuleiro = preencherTabuleiro(dados, tabuleiro);

	while (aux) {

		if (impressao == 1) {
			dados.col = 0;
			dados.lin = 0;
			aux->nrjogada = 1;
			atualizarTabuleiro(dados, tabuleiro);
			fprintf(f, "  Tabuleiro inicial:\n");

		}
		else {
			dados.col = aux->col;
			dados.lin = aux->lin;
			atualizarTabuleiro(dados, tabuleiro);
			fprintf(f, "  Jogada %d:\nJogador %d: %c%d\n", aux->nrjogada, jogador, dados.col + 64, dados.lin);
			aux = aux->prox;

		}


		for (i = 0; i <= (dados.nrlin); i++) {

			fprintf(f, "  ");

			for (j = 0; j <= (dados.nrcol); j++) {

				if (tabuleiro[i][j].dados == 0)
					fprintf(f, "  ");

				if (tabuleiro[i][j].dados == 1)
					fprintf(f, "%2c", j + 64);

				if (tabuleiro[i][j].dados == 2)
					fprintf(f, "%2d", i);

				if (tabuleiro[i][j].dados == 3)
					fprintf(f, "%2c", '*');

				if (tabuleiro[i][j].dados == 4)
					fprintf(f, "%2c", 'X');

			}
			fprintf(f, "\n");
		}

		fprintf(f, "\n\n");

		jogador = trocarJogador(jogador);


		impressao++;
	}

	fprintf(f, "Ganhou o jogador %d", jogador);

	fclose(f);

}

void freeWilly(jogo dados, matriz **tabuleiro, pguardar jogadas)																// por implementar
{
	int i;

	pguardar aux;

	for (i = 0; i < dados.nrcol; i++) {
		free(tabuleiro[i]);
	}

	free(*tabuleiro);

	while (jogadas) {
		aux = jogadas;
		jogadas = jogadas->prox;
		free(aux);
	}

}

//--------------------------------- fim das funcoes que nao chamam outras


//--------------------------------- Novo Jogo

void jogoIA()
{

	jogo x;
	matriz **tabuleiro = NULL;
	pguardar jogadas = NULL;

	int vencedor=0, nrjogada=1, opcao=0, jogador=1, jogou=0, desistir=0;

    dimensaoTabuleiro(&x);
    tabuleiro = preencherTabuleiro(x, tabuleiro);

    while (vencedor == 0) {																				// trocar condicao ?

        if (nrjogada > 1)
            printf("Jogada do computador: %c%d\n", x.col + 64, x.lin);

        mostrarTabuleiro(x, tabuleiro);

        opcao = menuDoJogo(x, tabuleiro, opcao, jogador);

        if (opcao == 1) {
            jogar(&x, jogador, tabuleiro);
            jogadas = guardarJogada(x, jogador, jogadas, nrjogada);
            atualizarTabuleiro(x, tabuleiro);
            nrjogada++;
            jogou++;
        }

        if (opcao == 2)
            mostrarJogadas(jogadas);

        if (opcao == 3) {
			guardarBin(x, nrjogada, jogadas, 1);
            break;
        }

        if (opcao == 4) {
            while (desistir < 1 || desistir > 2) {
                printf("Tem mesmo a certeza que quer desistir?\n Insira 1 se Sim, 2 se Nao.\n");
                scanf("%d", &desistir);
            }
            if (desistir == 1) {
                printf("\n\nO computador ganhou o jogo!\n\n");
				imprimirTXT(x, jogadas);																	// por implementar
                system("pause");
                break;
            }
        }

        if (x.lin == x.nrlin && x.col == x.nrcol) {
            printf("\n\n O jogador comeu o veneno! O computador ganhou!\n");
			imprimirTXT(x, jogadas);																	// por implementar
            break;
        }

        /// jogada da IA após a jogada do utilizador
        if (jogou == 1) {
            printf("\n\nO computador vai realizar a sua jogada...\n");
            jogadaIA(&x, tabuleiro);

			jogador = trocarJogador(jogador);
            jogadas = guardarJogada(x, jogador, jogadas, nrjogada);
            jogador = trocarJogador(jogador);

			atualizarTabuleiro(x, tabuleiro);
            nrjogada++;
            jogou--;
            if (x.lin == x.nrlin && x.col == x.nrcol) {
                printf("\n\nO computador comeu o veneno! O jogador ganhou!\n");
				imprimirTXT(x, jogadas);																// por implementar
				system("pause");
                break;
            }
        }

        system("cls");

        opcao = 0;
    }

//	freeWilly(x, tabuleiro, jogadas);

}

void jogoPVP()
{
	jogo x;
	matriz **tabuleiro = NULL;
	pguardar jogadas = NULL;

	int vencedor = 0, nrjogada = 1, opcao = 0, jogador = 1, jogou = 0, desistir = 0;

	dimensaoTabuleiro(&x);
	tabuleiro = preencherTabuleiro(x, tabuleiro);

	while (vencedor == 0) {																				// trocar condicao ?

		mostrarTabuleiro(x, tabuleiro);

		opcao = menuDoJogo(x, tabuleiro, opcao, jogador);

		if (opcao == 1) {
			jogar(&x, jogador, tabuleiro);
			jogadas = guardarJogada(x, jogador, jogadas, nrjogada);
			atualizarTabuleiro(x, tabuleiro);
			nrjogada++;
			jogou++;
		}

		if (opcao == 2)
			mostrarJogadas(jogadas);

		if (opcao == 3) {
			guardarBin(x, nrjogada, jogadas, 2);
			break;
		}

		if (opcao == 4) {
			while (desistir < 1 || desistir > 2) {
				printf("Tem mesmo a certeza que quer desistir?\n Insira 1 se Sim, 2 se Nao.\n");
				scanf("%d", &desistir);
			}
			if (desistir == 1) {
				printf("\n\n  Ganhou o jogador %d! Parabens!\n\n", jogador);
				imprimirTXT(x, jogadas);																	// por implementar
				system("pause");
				break;
			}
		}

		if (x.lin == x.nrlin && x.col == x.nrcol) {
			printf("\n\n  O jogador %d comeu o veneno!\n", jogador);
			jogador = trocarJogador(jogador);
			printf("  Ganhou o jogador %d! Parabens!\n", jogador);
			imprimirTXT(x, jogadas);																 // por implementar
			break;
		}

		system("cls");

		jogador = trocarJogador(jogador);
		opcao = 0;
	}

	//	freeWilly(x, tabuleiro, jogadas);

}

int escolhaJogo(int escolha)
{
	while (escolha < 1 || escolha>3) {
		printf("\nNovo jogo:\n 1 - Jogador vs. IA\n 2 - Jogador vs. Jogador\n 3 - Voltar ao Menu\n  Escolha: ");
		scanf("%d", &escolha);
		if (escolha < 1 || escolha>3) {
			printf("\n\nA escolha deve ser de 1 a 3!\n");
			system("pause");
		}
        system("cls");
    }
    return escolha;
}

void menuNovoJogo()
{
    int escolha=0;
    escolha = escolhaJogo(escolha);

    if(escolha == 1)
        jogoIA();

	if (escolha == 2)
		jogoPVP();

}

//--------------------------------- Carregar Jogo

void continuarjogoIA(jogo x, matriz **tabuleiro, int jogadas, int jogador, int nrjogada)
{
	int vencedor = 0, opcao = 0, jogou = 0, desistir = 0;

	while (vencedor == 0) {																				// trocar condicao ?

		if (nrjogada > 1)
			printf("Jogada do computador: %c%d\n", x.col + 64, x.lin);

		mostrarTabuleiro(x, tabuleiro);

		opcao = menuDoJogo(x, tabuleiro, opcao, jogador);

		if (opcao == 1) {
			jogar(&x, jogador, tabuleiro);
			jogadas = guardarJogada(x, jogador, jogadas, nrjogada);
			atualizarTabuleiro(x, tabuleiro);
			nrjogada++;
			jogou++;
		}

		if (opcao == 2)
			mostrarJogadas(jogadas);

		if (opcao == 3) {
			guardarBin(x, nrjogada, jogadas, 1);
			break;
		}

		if (opcao == 4) {
			while (desistir < 1 || desistir > 2) {
				printf("Tem mesmo a certeza que quer desistir?\n Insira 1 se Sim, 2 se Nao.\n");
				scanf("%d", &desistir);
			}
			if (desistir == 1) {
				printf("\n\nO computador ganhou o jogo!\n\n");
				system("pause");
				imprimirTXT(x, jogadas);																	// por implementar
				break;
			}
		}

		if (x.lin == x.nrlin && x.col == x.nrcol) {
			printf("\n\n O jogador comeu o veneno! O computador ganhou!\n");
			imprimirTXT(x, jogadas);																	// por implementar
			break;
		}

		/// jogada da IA após a jogada do utilizador
		if (jogou == 1) {
			printf("\n\nO computador vai realizar a sua jogada...\n");
			jogadaIA(&x, tabuleiro);

			jogador = trocarJogador(jogador);
			jogadas = guardarJogada(x, jogador, jogadas, nrjogada);
			jogador = trocarJogador(jogador);

			atualizarTabuleiro(x, tabuleiro);
			nrjogada++;
			jogou--;
			if (x.lin == x.nrlin && x.col == x.nrcol) {
				printf("\n\nO computador comeu o veneno! O jogador ganhou!\n");
				imprimirTXT(x, jogadas);																// por implementar
				system("pause");
				break;
			}
		}

		system("cls");

		opcao = 0;
	}
}

void continuarjogoPVP(jogo x, matriz **tabuleiro, int jogadas, int jogador, int nrjogada)
{
	int vencedor = 0, opcao = 0, jogou = 0, desistir = 0;

	while (vencedor == 0) {																				// trocar condicao ?

		mostrarTabuleiro(x, tabuleiro);

		opcao = menuDoJogo(x, tabuleiro, opcao, jogador);

		if (opcao == 1) {
			jogar(&x, jogador, tabuleiro);
			jogadas = guardarJogada(x, jogador, jogadas, nrjogada);
			atualizarTabuleiro(x, tabuleiro);
			nrjogada++;
			jogou++;
		}

		if (opcao == 2)
			mostrarJogadas(jogadas);

		if (opcao == 3) {
			guardarBin(x, nrjogada, jogadas, 2);
			break;
		}

		if (opcao == 4) {
			while (desistir < 1 || desistir > 2) {
				printf("Tem mesmo a certeza que quer desistir?\n Insira 1 se Sim, 2 se Nao.\n");
				scanf("%d", &desistir);
			}
			if (desistir == 1) {
				printf("\n\n  Ganhou o jogador %d! Parabens!\n\n", jogador);
				imprimirTXT(x, jogadas);																	// por implementar
				system("pause");
				break;
			}
		}

		if (x.lin == x.nrlin && x.col == x.nrcol) {
			printf("\n\n  O jogador %d comeu o veneno!\n", jogador);
			jogador = trocarJogador(jogador);
			printf("  Ganhou o jogador %d! Parabens!\n", jogador);
			imprimirTXT(x, jogadas);																 // por implementar
			break;
		}

		system("cls");

		jogador = trocarJogador(jogador);
		opcao = 0;
	}
}

void carregarBin()
{
	jogo x;
	matriz **tabuleiro = NULL;
	pguardar jogadas = NULL;
	pguardar jogadaCarregada;

	int i, nrjogadas, nrjogada=1, jogador=1, modoJogo;

	FILE *f;
	f = fopen("jogoGuardado.dat", "rb");

	if (!f) {
		printf("\n\nErro ao abrir o ficheiro\n");
		system("pause");
		return;
	}

	fread(&x.nrlin, sizeof(int), 1, f);
	fread(&x.nrcol, sizeof(int), 1, f);
	fread(&nrjogadas, sizeof(int), 1, f);
	fread(&modoJogo, sizeof(int), 1, f);

	tabuleiro = preencherTabuleiro(x, tabuleiro);

	for (i = 0; i < nrjogadas; i++) {
		fread(&x.col, sizeof(int), 1, f);
		fread(&x.lin, sizeof(int), 1, f);
		fread(&nrjogada, sizeof(int), 1, f);

		jogadas = guardarJogada(x, jogador, jogadas, nrjogada);
		atualizarTabuleiro(x, tabuleiro);

		jogador = trocarJogador(jogador);
		nrjogada++;
	}

	fclose(f);

	printf("\n  Jogo carregado com sucesso!\n");
	system("pause");
	system("cls");

	if (modoJogo == 1)
		continuarjogoIA(x, tabuleiro, jogadas, jogador, nrjogada);

	if (modoJogo == 1)
		continuarjogoPVP(x, tabuleiro, jogadas, jogador, nrjogada);

	//	freeWilly(x, tabuleiro, jogadas);


}



//--------------------------------- main

int menuPrincipal(int menu)
{
    if (menu == 0) {
        printf("Bem vindo ao Jogo do Comilao! \n 1 - Novo Jogo\n 2 - Carregar Jogo \n 3 - Sair\n  Escolha: ");
        scanf("%d", &menu);
		if (menu < 1 || menu>3) {
			printf("\n\nA escolha deve ser de 1 a 3!\n");
			system("pause");
		}
        system("cls");
    }
    return menu;
}

void main()
{
    srand(time(NULL));

	int menu=0;

	while (menu == 0) {
        menu = menuPrincipal(menu);

		if (menu == 1)
			menuNovoJogo();

		if (menu == 2)
			carregarBin();
	}
}
