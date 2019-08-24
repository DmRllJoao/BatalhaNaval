#include <stdio.h> 				
#include <stdlib.h>				
#include <time.h>				
#include <stdbool.h>

//Variáveis globais

//termos para auxiliar na tabela
#define MAX 10 //tamanho do tabuleiro 10x10
#define AGUA 'A' //Campo água
#define DESCONHECIDO 'D'//Campo desconhecido

#define EMBARCACAO1X1 '1'
//Para diferenciar o trio da embarcação 1x2,usei I para facilitar o reconhecimento.
#define EMBARCACAO1X2 '2'
#define EMBARCACAO1X2I '3'
#define EMBARCACAO1X3 '4'
#define EMBARCACAO1X4 '5'
#define EMBARCACAOT 'T'


//DECLARAÇÃO DE CORES 
#define NONE "\033[0m"
#define BLACKCOLOR "\033[35m" //não é mais preto
#define REDCOLOR "\033[31m"
#define BLUECOLOR "\033[34m"
#define BLACKBG "\033[40m"
#define BLUEBG	"\033[44m"
#define YELLOWCOLOR 

int i,j,v,h,direcao,rotacao; //Declaração de i e j para auxiliar em for,v e h para escolhas de coordenadas,assim como direção(de todos os barcos exceto o T) e rotação(do barco T)
int inserido = 0,verificador = 0; //Total de barcos inseridos e verificação de sobreposição de barcos
int cont1x1 = 0,cont1x2 = 0,cont1x3 = 0,cont1x4 = 0,contT = 0; //Contadores para não exceder o total de barcos
char tabuleiroJogador[MAX][MAX]; //tabuleiro do jogador para inserir barcos
char tabuleiroIA[MAX][MAX]; //tabuleiro da IA para inserir barcos
char tabuleiroJogador2[MAX][MAX]; //tabuleiro do jogador para jogar
char tabuleiroIA2[MAX][MAX]; //tabuleiro da IA para jogar
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

//Declaração de funções 
void iniciaTabuleiro();						
void imprimeTabuleiro(char M[MAX][MAX]);	
void insereEmbarcacao1x1(char M[MAX][MAX]);	
void insereEmbarcacao1x2(char M[MAX][MAX]);
void insereEmbarcacao1x3(char M[MAX][MAX]);
void insereEmbarcacao1x4(char M[MAX][MAX]);
void insereEmbarcacaoT(char M[MAX][MAX]);
void zerarContadores();
void autoInsere(char M[MAX][MAX]);

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
void zerarContadores() //Zerar os contadores dos barcos
{
	cont1x1 = 0;
	cont1x2 = 0;
	cont1x3 = 0;
	cont1x4 = 0;
	contT = 0;
	inserido = 0;
}
void iniciaTabuleiro() //Iniciar o tabuleiro
{
	for(i = 0;i<MAX;i++){
		for(j = 0;j<MAX;j++){
			tabuleiroJogador[i][j] = AGUA; 
			tabuleiroIA[i][j] = AGUA;
			tabuleiroJogador2[i][j] = DESCONHECIDO;
			tabuleiroIA2[i][j] = DESCONHECIDO;
		}
	}
}

void imprimeTabuleiro(char M[MAX][MAX]) // //Impressão dos tabuleiros
{
	if(M == tabuleiroJogador)
	{
		printf("\n/ JOGADOR /");
		printf("\n - - - - - - - - - - - - - - - - - - - - - - - - - -");
	}
	else
		printf("\n/ COMPUTADOR /");
		printf("\n - - - - - - - - - - - - - - - - - - - - - - - - - +");
	for(i = 0;i < MAX;i++)
	{
		printf("\n");
		for(j = 0;j < MAX;j++){
			printf("%s  |%s%c%s%s|%s",BLUEBG,BLACKBG,M[i][j],NONE,BLUEBG,NONE);
		}
	}
	printf("\n - - - - - - - - - - - - - - - - - - - - - - - - - +");
}

void insereEmbarcacao1x1(char M[MAX][MAX])//inserção de barcos 1x1
{
	if(cont1x1 < 3)
	{				
		printf("\n%sEntre com a coordenada vertical da embarcação 1x1 : %s",BLACKCOLOR,NONE);
		scanf("%d",&v);
		printf("\n%sEntre com a coordenada horizontal da embarcação 1x1 : %s",BLACKCOLOR,NONE);
		scanf("%d",&h);

		//OS INDICES SERÃO SUBTRAIDOS POR 1 PARA COINCIDIR COM A SINTAXE
		if((v > 10 || v < 1 ) || (h < 1 || h > 9))
		{
			printf("\n%sErro ao inserir a embarcação.%s\n",REDCOLOR,NONE); //erro,caso exceda o tabuleiro
		}
		else
		{
			if((M[h-1][v-1] == EMBARCACAO1X1 || M[h-1][v-1] == EMBARCACAO1X2) || (M[h-1][v-1] == EMBARCACAO1X3 || M[h-1][v-1] == EMBARCACAO1X4) || (M[h-1][v-1] == EMBARCACAOT || M[h-1][v-1] == EMBARCACAO1X2I)) //Verificação para não sobrepor barcos
				printf("\n%sJá existe uma embarcação alocado nas coordenadas inseridas%s",REDCOLOR,NONE);
			else
			{
				M[h-1][v-1] = EMBARCACAO1X1;
				cont1x1 ++;
			}
		}
	}
	else 
		printf("\n%sMáximo de embarcações 1x1 colocados%s\n",REDCOLOR,NONE);
}

void insereEmbarcacao1x2(char M[MAX][MAX])//inserção de barcos 1x2
{	
	verificador = 0;
	if(cont1x2 < 2)
	{
		printf("\n%sEntre com a direção que quer inserir a embarcação 1x2 [1 - horizontal/2 - vertical] : %s",BLACKCOLOR,NONE);
		scanf("%d",&direcao);
		switch(direcao)
		{
			case 1 : //direção horizontal
				printf("%s\nEntre com a coordenada vertical da embarcação 1x2 : %s",BLACKCOLOR,NONE);
				scanf("%d",&v);
				printf("%s\nEntre com a coordenada horizontal da embarcação 1x2 : %s",BLACKCOLOR,NONE);
				scanf("%d",&h);
				//Verificação,caso coordenadas exceda o tabuleiro
				if((v > 10 || v < 1 ) || (h < 1 || h > 9))
				{
					printf("\n%sErro ao inserir a embarcação.%s\n",REDCOLOR,NONE); //erro,caso exceda o tabuleiro
					break;
				}
				else
				{	
					for(i = 0;i < 2;i++)
					{
					//OS INDICES SERÃO SUBTRAIDOS POR 1 PARA COINCIDIR COM A SINTAXE
						if((M[h-1][v-1+i] == EMBARCACAO1X1 || M[h-1][v-1+i] == EMBARCACAO1X2) || (M[h-1][v-1+i] == EMBARCACAO1X3 || M[h-1][v-1+i] == EMBARCACAO1X4) || (M[h-1][v-1+i] == EMBARCACAOT || M[h-1][v-1+i] == EMBARCACAO1X2)) //Verificação para não sobrepor barcos
							verificador++;
					}
					if(verificador == 0)
					{
						if(cont1x2 == 0)
						{
							for(i = 0;i < 2;i++)
							M[h-1][v-1+i] = EMBARCACAO1X2;
							cont1x2++;
						}
						else if(cont1x2 == 1)
						{
							for(i = 0;i < 2;i++)
							M[h-1][v-1+i] = EMBARCACAO1X2I;
							cont1x2++;
						}
					}
					else
						printf("\n%sJá existe uma embarcação alocado nas coordenadas inseridas.%s\n",REDCOLOR,NONE);
				}
				break;

			case 2 : //direção vertical
				printf("\n%sEntre com a coordenada vertical da embarcação 1x2 : %s",BLACKCOLOR,NONE);
				scanf("%d",&v);
				printf("\n%sEntre com a coordenada horizontal da embarcação 1x2 : %s",BLACKCOLOR,NONE);
				scanf("%d",&h);

				if((v > 9 || v < 1 ) || (h < 1 ||h > 10)) //ERRO PARA NÃO EXCEDER O TABULEIRO
				{
					printf("\n%sErro ao inserir a embarcação.%s\n",REDCOLOR,NONE);
					break;
				}
				else
				{
					for(i = 0;i < 2;i++)
					{							
								//OS INDICES SERÃO SUBTRAIDOS POR 1 PARA COINCIDIR COM A SINTAXE	
						if((M[h-1+i][v-1] == EMBARCACAO1X1  || M[h-1+i][v-1] == EMBARCACAO1X2) || (M[h-1+i][v-1] == EMBARCACAO1X3 || M[h-1+i][v-1] == EMBARCACAO1X4) || (M[h-1+i][v-1] == EMBARCACAOT || M[h-1+i][v-1] == EMBARCACAO1X2I))
							verificador++;//Verificação para não sobrepor barcos
					}
					if(verificador == 0)
					{
						if(cont1x2 == 0)
						{
							for(i =0;i < 2;i++)
							M[h-1+i][v-1] = EMBARCACAO1X2;
							cont1x2++;						
						}
						else if(cont1x2 == 1)
						{
							for(i =0;i < 2;i++)
							M[h-1+i][v-1] = EMBARCACAO1X2I;
							cont1x2++;
						}
					}
					else
						printf("\n%sJá existe uma embarcação alocada nas coordenadas inseridas%s\n",REDCOLOR,NONE);
				}
				break;
			default :
				printf("\n%sErro ao inserir a embarcação.%s\n",REDCOLOR,NONE);
		}
	}
		else
				printf("\n%sMáximo de embarcações 1x2 inseridas%s\n",REDCOLOR,NONE);
}
void insereEmbarcacao1x3(char M[MAX][MAX])//Inserção de barcos 1x3
{
	verificador = 0;
	if(cont1x3 < 1)
	{
		printf("\n%sEntre com a direção que quer inserir a embarcação 1x3 [1 - HORIZONTAL/2 - VERTICAL] : %s",BLACKCOLOR,NONE);
		scanf("%d",&direcao);
		switch(direcao)
		{
			case 1 : //direção horizontal
				printf("%s\nEntre com a coordenada vertical da embarcação 1x3 : %s",BLACKCOLOR,NONE);
				scanf("%d",&v);
				printf("%s\nEntre com a coordenada horizontal da embarcação 1x3 : %s",BLACKCOLOR,NONE);
				scanf("%d",&h);

				if((v > 10 || v < 1 ) || (h < 1 || h > 8))
				{
					printf("\n%sErro ao inserir a embarcação.%s\n",REDCOLOR,NONE); //erro,caso exceda o tabuleiro
					break;
				}
				else
				{	
					for(i = 0;i < 3;i++)
					{
						//OS INDICES SERÃO SUBTRAIDOS POR 1 PARA COINCIDIR COM A SINTAXE 
						if((M[h-1][v-1+i] == EMBARCACAO1X1 || M[h-1][v-1+i] == EMBARCACAO1X2) || (M[h-1][v-1+i] == EMBARCACAO1X3 || M[h-1][v-1+i] == EMBARCACAO1X4 )|| (M[h-1][v-1+i] == EMBARCACAOT || M[h-1][v-1+i] == EMBARCACAO1X2)) //Verificação para não sobrepor barcos
							verificador++;//Verificação para não sobrepor barcos
					}
					if(verificador == 0)
					{
						for(i = 0;i < 3;i++)
						M[h-1][v-1+i] = EMBARCACAO1X3;
						cont1x3++;
					}
					else
						printf("\n%sJá existe uma embarcação alocada nas coordenadas inseridas.%s\n",REDCOLOR,NONE);
				}
				break;

				case 2 : //direção vertical
					printf("\n%sEntre com a coordenada vertical da embarcação 1x3 : %s",BLACKCOLOR,NONE);
					scanf("%d",&v);
					printf("\n%sEntre com a coordenada horizontal da embarcação 1x3 : %s",BLACKCOLOR,NONE);
					scanf("%d",&h);

					if((v > 8 || v < 1 ) || (h < 1 ||h > 10)) //ERRO PARA NÃO EXCEDER O TABULEIRO
					{
						printf("\n%sErro ao inserir a embarcação.%s\n",REDCOLOR,NONE);
						break;
					}
					else
					{
						for(i = 0;i < 3;i++)
						{					
							//OS INDICES SERÃO SUBTRAIDOS POR 1 PARA COINCIDIR COM A SINTAXE			
							if((M[h-1+i][v-1] == EMBARCACAO1X1  || M[h-1+i][v-1] == EMBARCACAO1X2) || (M[h-1+i][v-1] == EMBARCACAO1X3 || M[h-1+i][v-1] == EMBARCACAO1X4) || (M[h-1+i][v-1] == EMBARCACAOT || M[h-1+i][v-1] == EMBARCACAO1X2I))
								verificador++;//Verificação para não sobrepor barcos
						}
						if(verificador == 0)
						{
							for(i = 0;i < 3;i++)
							{
								M[h-1+i][v-1] = EMBARCACAO1X3;
								cont1x3++;
							}
						}
						else 
							printf("\n%sJá existe uma embarcação alocada nas coordenadas inseridas%s\n",REDCOLOR,NONE);
					}
					break;
				default :
					printf("\n%sErro ao inserir a embarcação.%s\n",REDCOLOR,NONE);
		}
	}
	else
		printf("\n%sMáximo de embarcações 1x3 inseridas%s\n",REDCOLOR,NONE);
}
void insereEmbarcacao1x4(char M[MAX][MAX])
{
	verificador = 0;
	if(cont1x4 < 1)
	{
		printf("\n%sEntre com a direção que quer inserir a embarcação 1x4 [1 - HORIZONTAL/2 - VERTICAL] : %s",BLACKCOLOR,NONE);
		scanf("%d",&direcao);
		switch(direcao)
		{
			case 1 : //direção horizontal
				printf("%s\nEntre com a coordenada vertical da embarcação 1x4 : %s",BLACKCOLOR,NONE);
				scanf("%d",&v);
				printf("%s\nEntre com a coordenada horizontal da embarcação 1x4 : %s",BLACKCOLOR,NONE);
				scanf("%d",&h);

				if((v > 10 || v < 1 ) || (h < 1 || h > 7))
				{
					printf("\n%sErro ao inserir a embarcação.%s\n",REDCOLOR,NONE); //erro,caso exceda o tabuleiro
					break;
				}
				else
				{	
					for(i = 0;i < 4;i++)
					{
						//OS INDICES SERÃO SUBTRAIDOS POR 1 PARA COINCIDIR COM A SINTAXE 
						if((M[h-1][v-1+i] == EMBARCACAO1X1 || M[h-1][v-1+i] == EMBARCACAO1X2) || (M[h-1][v-1+i] == EMBARCACAO1X3 || M[h-1][v-1+i] == EMBARCACAO1X4) || (M[h-1][v-1+i] == EMBARCACAOT || M[h-1][v-1+i] == EMBARCACAO1X2I)) //Verificação para não sobrepor barcos
						verificador++;//Verificação para não sobrepor barcos
					}
					if(verificador == 0)
					{
						for(i = 0;i < 4;i++)
						{
							M[h-1][v-1+i] = EMBARCACAO1X4;
							cont1x4++;
						}
					}
					else
						printf("\n%sJá existe uma embarcação alocada nas coordenadas inseridas.%s\n",REDCOLOR,NONE);
				}
				break;
			case 2 : //direção vertical
				printf("\n%sEntre com a coordenada vertical da embarcação 1x4 : %s",BLACKCOLOR,NONE);
				scanf("%d",&v);
				printf("\n%sEntre com a coordenada horizontal da embarcação 1x4 : %s",BLACKCOLOR,NONE);
				scanf("%d",&h);

				if((v > 7 || v < 1 ) || (h < 1 ||h > 10)) //ERRO PARA NÃO EXCEDER O TABULEIRO
					printf("\n%sErro ao inserir a embarcação.%s\n",REDCOLOR,NONE);
				else
				{
					for(i = 0;i < 4;i++)
					{			
					//OS INDICES SERÃO SUBTRAIDOS POR 1 PARA COINCIDIR COM A SINTAXE			
					if((M[h-1+i][v-1] == EMBARCACAO1X1  || M[h-1+i][v-1] == EMBARCACAO1X2) || (M[h-1+i][v-1] == EMBARCACAO1X3 || M[h-1+i][v-1] == EMBARCACAO1X4) || (M[h-1+i][v-1] == EMBARCACAOT  || M[h-1+i][v-1] == EMBARCACAO1X2I))
						verificador++;//Verificação para não sobrepor barcos//Verificação para não sobrepor barcos
					}	
					if(verificador == 0)
					{
						for(i = 0;i < 4;i++)
						{
							M[h-1+i][v-1] = EMBARCACAO1X4;
							cont1x4++;
						}
					}
					else 
						printf("\n%sJá existe uma embarcação alocada nas coordenadas inseridas%s\n",REDCOLOR,NONE);
				}
				break;
			default :
					printf("\n%sErro ao inserir a embarcação.%s\n",REDCOLOR,NONE);
			
		}
	}
	else
		printf("\n%sMáximo de embarcações 1x4 inseridas%s\n",REDCOLOR,NONE);
}
void insereEmbarcacaoT(char M[MAX][MAX])
{ 
	verificador = 0;
	if(contT < 1)
	{
		printf("\n%sEntre com a rotação que quer inserir a embarcação T [1 - 0°/2 - 90°/3 - 180°/4 - 270°] : %s",BLACKCOLOR,NONE);
		scanf("%d",&rotacao);
		switch(rotacao)
		{
			case 1 : //rotação 0°
				printf("\n%sA referência da embarcação é o ponto de interseção do T%s\n",BLACKCOLOR,NONE);
				printf("%s\nEntre com a coordenada vertical da embarcação T : %s",BLACKCOLOR,NONE);
				scanf("%d",&v);
				printf("%s\nEntre com a coordenada horizontal da embarcação T : %s",BLACKCOLOR,NONE);
				scanf("%d",&h);

				if((v > 10 || v < 3 ) || (h < 2 || h > 9))//VERIFICANDO SE EXCEDE O TABULEIRO
				{
					printf("\n%sErro ao inserir a embarcação.%s\n",REDCOLOR,NONE); //erro,caso exceda o tabuleiro
					break;
				}
				else
				{	
					//OS INDICES SERÃO SUBTRAIDOS POR 1 PARA COINCIDIR COM A SINTAXE 
					if((M[h-1][v-1+1] == EMBARCACAO1X1 || M[h-1][v-1+1] == EMBARCACAO1X2) || (M[h-1][v-1+1] == EMBARCACAO1X3 || M[h-1][v-1+1] == EMBARCACAO1X4) || (M[h-1][v-1+1] == EMBARCACAOT || M[h-1][v-1+1] == EMBARCACAO1X2I)) //Verificação para não sobrepor barcos
						verificador++;

					if((M[h-1][v-1+2] == EMBARCACAO1X1 || M[h-1][v-1+2] == EMBARCACAO1X2) || (M[h-1][v-1+2] == EMBARCACAO1X3 || M[h-1][v-1+2] == EMBARCACAO1X4) || (M[h-1][v-1+2] == EMBARCACAOT || M[h-1][v-1+2] == EMBARCACAO1X2I)) //Verificação para não sobrepor barcos
						verificador++;

					if((M[h-1][v-1] == EMBARCACAO1X1 || M[h-1][v-1] == EMBARCACAO1X2) || (M[h-1][v-1] == EMBARCACAO1X3 || M[h-1][v-1] == EMBARCACAO1X4) ||(M[h-1][v-1] == EMBARCACAOT || M[h-1][v-1] == EMBARCACAO1X2I)) //Verificação para não sobrepor barcos
						verificador++;

					if((M[h-1+1][v-1] == EMBARCACAO1X1 || M[h-1+1][v-1] == EMBARCACAO1X2) || (M[h-1+1][v-1] == EMBARCACAO1X3 || M[h-1+1][v-1] == EMBARCACAO1X4) || (M[h-1+1][v-1] == EMBARCACAOT || M[h-1+1][v-1] == EMBARCACAO1X2I)) //Verificação para não sobrepor barcos
						verificador++;
	
					if((M[h-1-1][v-1] == EMBARCACAO1X1 || M[h-1-1][v-1] == EMBARCACAO1X2) || (M[h-1-1][v-1] == EMBARCACAO1X3 || M[h-1-1][v-1] == EMBARCACAO1X4) || (M[h-1-1][v-1] == EMBARCACAOT || M[h-1-1][v-1] == EMBARCACAO1X2I)) //Verificação para não sobrepor barcos
						verificador++;
					if(verificador == 0)
					{
								
						M[h-1][v-1] = EMBARCACAOT;
						M[h-1+1][v-1] = EMBARCACAOT;
						M[h-1+2][v-1] = EMBARCACAOT;	
						M[h-1][v-1+1] = EMBARCACAOT;
						M[h-1][v-1-1] = EMBARCACAOT;
						contT++;
					}
					else
						printf("\n%sJá existe uma embarcação alocada nas coordenadas inseridas.%s\n",REDCOLOR,NONE);
				}
				break;
			case 2 : //rotação 90°
				printf("\n%sA referência da embarcação é o ponto de interseção do T%s\n",BLACKCOLOR,NONE);
				printf("%s\nEntre com a coordenada vertical da embarcação T : %s",BLACKCOLOR,NONE);
				scanf("%d",&v);
				printf("%s\nEntre com a coordenada horizontal da embarcação T : %s",BLACKCOLOR,NONE);
				scanf("%d",&h);

				if((v > 9 || v < 2 ) || (h < 1 || h > 8))//VERIFICANDO SE EXCEDE O TABULEIRO
				{
					printf("\n%sErro ao inserir a embarcação.%s\n",REDCOLOR,NONE); //erro,caso exceda o tabuleiro
					break;
				}
				else
				{	
					//OS INDICES SERÃO SUBTRAIDOS POR 1 PARA COINCIDIR COM A SINTAXE
					if((M[h-1+1][v-1] == EMBARCACAO1X1 || M[h-1+1][v-1] == EMBARCACAO1X2) || (M[h-1+1][v-1] == EMBARCACAO1X3 || M[h-1+1][v-1] == EMBARCACAO1X4) || (M[h-1+1][v-1] == EMBARCACAOT || M[h-1+1][v-1] == EMBARCACAO1X2I)) //Verificação para não sobrepor barcos
						verificador++;

					if((M[h-1-1][v-1] == EMBARCACAO1X1 || M[h-1-1][v-1] == EMBARCACAO1X2) ||( M[h-1-1][v-1] == EMBARCACAO1X3 || M[h-1-1][v-1] == EMBARCACAO1X4) || (M[h-1-1][v-1] == EMBARCACAOT || M[h-1-1][v-1] == EMBARCACAO1X2I)) //Verificação para não sobrepor barcos
						verificador++;

					if((M[h-1][v-1] == EMBARCACAO1X1 || M[h-1][v-1] == EMBARCACAO1X2) || (M[h-1][v-1] == EMBARCACAO1X3 || M[h-1][v-1] == EMBARCACAO1X4) || (M[h-1][v-1] == EMBARCACAOT || M[h-1][v-1] == EMBARCACAO1X2I)) //Verificação para não sobrepor barcos
						verificador++;

					if((M[h-1][v-1+1] == EMBARCACAO1X1 || M[h-1][v-1+1] == EMBARCACAO1X2) || (M[h-1][v-1+1] == EMBARCACAO1X3 || M[h-1][v-1+1] == EMBARCACAO1X4) || (M[h-1][v-1+1] == EMBARCACAOT || M[h-1][v-1+1] == EMBARCACAO1X2I)) //Verificação para não sobrepor barcos
						verificador++;

					if((M[h-1][v-1+2] == EMBARCACAO1X1 || M[h-1][v-1+2] == EMBARCACAO1X2) ||( M[h-1][v-1+2] == EMBARCACAO1X3 || M[h-1][v-1+2] == EMBARCACAO1X4) || (M[h-1][v-1+2] == EMBARCACAOT || M[h-1][v-1+2] == EMBARCACAO1X2I)) //Verificação para não sobrepor barcos
						verificador++;
					if(verificador == 0)
					{
								
						M[h-1][v-1] = EMBARCACAOT;
						M[h-1+1][v-1] = EMBARCACAOT;
						M[h-1-1][v-1] = EMBARCACAOT;	
						M[h-1][v-1+1] = EMBARCACAOT;
						M[h-1][v-1+2] = EMBARCACAOT;
						contT++;
					}
					else
						printf("\n%sJá existe uma embarcação alocada nas coordenadas inseridas.%s\n",REDCOLOR,NONE);
				}
				break;
			case 3 : //rotação 180°
				printf("\n%sA referência da embarcação é o ponto de interseção do T%s\n",BLACKCOLOR,NONE);
				printf("%s\nEntre com a coordenada vertical da embarcação T : %s",BLACKCOLOR,NONE);
				scanf("%d",&v);
				printf("%s\nEntre com a coordenada horizontal da embarcação T : %s",BLACKCOLOR,NONE);
				scanf("%d",&h);

				if((v > 10 || v < 3 ) || (h < 2 || h > 9 ))//VERIFICANDO SE EXCEDE O TABULEIRO
				{
					printf("\n%sErro ao inserir a embarcação.%s\n",REDCOLOR,NONE); //erro,caso exceda o tabuleiro
					break;
				}
				else
				{	
					//OS INDICES SERÃO SUBTRAIDOS POR 1 PARA COINCIDIR COM A SINTAXE
					if((M[h-1][v-1+1] == EMBARCACAO1X1 || M[h-1][v-1+1] == EMBARCACAO1X2) || (M[h-1][v-1+1] == EMBARCACAO1X3 || M[h-1][v-1+1] == EMBARCACAO1X4) || (M[h-1][v-1+1] == EMBARCACAOT || M[h-1][v-1+1] == EMBARCACAO1X2I)) //Verificação para não sobrepor barcos
						verificador++;//Verificação para não sobrepor barcos

					if((M[h-1][v-1-1] == EMBARCACAO1X1 || M[h-1][v-1-1] == EMBARCACAO1X2) ||( M[h-1][v-1-1] == EMBARCACAO1X3 || M[h-1][v-1-1] == EMBARCACAO1X4) || (M[h-1][v-1-1] == EMBARCACAOT || M[h-1][v-1-1] == EMBARCACAO1X2I)) //Verificação para não sobrepor barcos
						verificador++;	//Verificação para não sobrepor barcos

					if((M[h-1][v-1] == EMBARCACAO1X1 || M[h-1][v-1] == EMBARCACAO1X2) || (M[h-1][v-1] == EMBARCACAO1X3 || M[h-1][v-1] == EMBARCACAO1X4) || (M[h-1][v-1] == EMBARCACAOT  || M[h-1][v-1] == EMBARCACAO1X2I)) //Verificação para não sobrepor barcos
						verificador++;//Verificação para não sobrepor barcos

					if((M[h-1-1][v-1] == EMBARCACAO1X1 || M[h-1-1][v-1] == EMBARCACAO1X2) || (M[h-1-1][v-1] == EMBARCACAO1X3 || M[h-1-1][v-1] == EMBARCACAO1X4) || (M[h-1-1][v-1] == EMBARCACAOT|| M[h-1-1][v-1] == EMBARCACAO1X2I))//Verificação para não sobrepor barcos
						verificador++;//Verificação para não sobrepor barcos

					if((M[h-1-2][v-1] == EMBARCACAO1X1 || M[h-1-2][v-1] == EMBARCACAO1X2) ||(M[h-1-2][v-1] == EMBARCACAO1X3 || M[h-1-2][v-1] == EMBARCACAO1X4) || (M[h-1-2][v-1] == EMBARCACAOT || M[h-1-2][v-1] == EMBARCACAO1X2I)) //Verificação para não sobrepor barcos
						verificador++;//Verificação para não sobrepor barcos

					if(verificador == 0)
					{
								
						M[h-1][v-1] = EMBARCACAOT;
						M[h-1-1][v-1] = EMBARCACAOT;
						M[h-1-2][v-1] = EMBARCACAOT;	
						M[h-1][v-1+1] = EMBARCACAOT;
						M[h-1][v-1-1] = EMBARCACAOT;
						contT++;
					}
					else
						printf("\n%sJá existe uma embarcação alocada nas coordenadas inseridas.%s\n",REDCOLOR,NONE);
				}
				break;

			case 4 : //rotação 270°
				printf("\n%sA referência da embarcação é o ponto de interseção do T%s\n",BLACKCOLOR,NONE);
				printf("%s\nEntre com a coordenada vertical da embarcação T : %s",BLACKCOLOR,NONE);
				scanf("%d",&v);
				printf("%s\nEntre com a coordenada horizontal da embarcação T : %s",BLACKCOLOR,NONE);
				scanf("%d",&h);
				if((v > 9 || v < 2 ) || (h < 3 || h > 10))//VERIFICANDO SE EXCEDE O TABULEIRO
				{
					printf("\n%sErro ao inserir a embarcação.%s\n",REDCOLOR,NONE); //erro,caso exceda o tabuleiro
					break;
				}
				else
				{
					if((M[h-1+1][v-1] == EMBARCACAO1X1 || M[h-1+1][v-1] == EMBARCACAO1X2) || (M[h-1+1][v-1] == EMBARCACAO1X3 || M[h-1+1][v-1] == EMBARCACAO1X4) || (M[h-1+1][v-1] == EMBARCACAOT || M[h-1+1][v-1] == EMBARCACAO1X2I)) //Verificação para não sobrepor barcos
						verificador++;//Verificação para não sobrepor barcos

					if((M[h-1-1][v-1] == EMBARCACAO1X1 || M[h-1-1][v-1] == EMBARCACAO1X2) ||( M[h-1-1][v-1] == EMBARCACAO1X3 || M[h-1-1][v-1] == EMBARCACAO1X4) || (M[h-1-1][v-1] == EMBARCACAOT || M[h-1-1][v-1] == EMBARCACAO1X2I)) //Verificação para não sobrepor barcos
						verificador++;	//Verificação para não sobrepor barcos

					if((M[h-1][v-1] == EMBARCACAO1X1 || M[h-1][v-1] == EMBARCACAO1X2) || (M[h-1][v-1] == EMBARCACAO1X3 || M[h-1][v-1] == EMBARCACAO1X4) || (M[h-1][v-1] == EMBARCACAOT || M[h-1][v-1] == EMBARCACAO1X2I)) //Verificação para não sobrepor barcos
						verificador++;//Verificação para não sobrepor barcos

					if((M[h-1][v-1-1] == EMBARCACAO1X1 || M[h-1][v-1-1] == EMBARCACAO1X2) || (M[h-1][v-1-1] == EMBARCACAO1X3 || M[h-1][v-1-1] == EMBARCACAO1X4) || (M[h-1][v-1-1] == EMBARCACAOT || M[h-1][v-1-1] == EMBARCACAO1X2I))  //Verificação para não sobrepor barcos
						verificador++;//Verificação para não sobrepor barcos

					if((M[h-1][v-1-2] == EMBARCACAO1X1 || M[h-1][v-1-2] == EMBARCACAO1X2) ||( M[h-1][v-1-2] == EMBARCACAO1X3 || M[h-1][v-1-2] == EMBARCACAO1X4) ||(M[h-1][v-1-2] == EMBARCACAOT || M[h-1][v-1-2] == EMBARCACAO1X2I)) //Verificação para não sobrepor barcos
						verificador++;//Verificação para não sobrepor barcos
	
					if(verificador == 0)
					{
								
						M[h-1][v-1] = EMBARCACAOT;
						M[h-1+1][v-1] = EMBARCACAOT;
						M[h-1-1][v-1] = EMBARCACAOT;	
						M[h-1][v-1-1] = EMBARCACAOT;
						M[h-1][v-1-2] = EMBARCACAOT;
						contT++;
					}
					else
						printf("\n%sJá existe uma embarcação alocada nas coordenadas inseridas.%s\n",REDCOLOR,NONE);
				}
				break;		
			default :
					printf("\n%sErro ao inserir a embarcação.%s\n",REDCOLOR,NONE);	
		}
	}
	else 
		printf("\n%sMáximo de embarcações T inseridas%s\n",REDCOLOR,NONE);
}
		
void autoInsere(char M[MAX][MAX])
{

	while(inserido < 8) //Só para quando tiver 8 barcos
	{
		verificador = 0;
		if(cont1x1 < 3)
		{				
			v = rand()%10 + 1;
			h = rand()%10 + 1;

			//OS INDICES SERÃO SUBTRAIDOS POR 1 PARA COINCIDIR COM A SINTAXE
			if((M[h-1][v-1] == EMBARCACAO1X1 || M[h-1][v-1] == EMBARCACAO1X2) || (M[h-1][v-1] == EMBARCACAO1X3 || M[h-1][v-1] == EMBARCACAO1X4)|| (M[h-1][v-1] == EMBARCACAOT || M[h-1][v-1] == EMBARCACAO1X2I)) //Verificação para não sobrepor barcos
				verificador++;
			else
			{
				if(verificador == 0){
					M[h-1][v-1] = EMBARCACAO1X1;
					cont1x1++;
					inserido++;
				}
			}
		}
		if(cont1x2 < 2)
		{
			verificador = 0;
			direcao = rand()%2 + 1;
			switch(direcao)
			{
				case 1 : //direção horizontal

					v = rand()%10 + 1;
					h = rand()%10 + 1;

				//Verificação,caso coordenadas exceda o tabuleiro
					if((v > 10 || v < 1 ) || (h < 1 || h > 9)) //erro,caso exceda o tabuleiro
						verificador++;
					else
					{	
						for(i = 0;i < 2;i++)
						{
					//OS INDICES SERÃO SUBTRAIDOS POR 1 PARA COINCIDIR COM A SINTAXE
							if((M[h-1][v-1+i] == EMBARCACAO1X1 || M[h-1][v-1+i] == EMBARCACAO1X2) || (M[h-1][v-1+i] == EMBARCACAO1X3 || M[h-1][v-1+i] == EMBARCACAO1X4) || (M[h-1][v-1+i] == EMBARCACAOT || M[h-1][v-1+i] == EMBARCACAO1X2I))//Verificação para não sobrepor barcos
								verificador++;
						}
						if(verificador == 0)
						{
							if(cont1x2 == 0)
							{
								for(i = 0;i < 2;i++)
								{
									M[h-1][v-1+i] = EMBARCACAO1X2;
									cont1x2++;
									inserido++;
								}
							}
							if(cont1x2 == 1)
							{
								for(i = 0;i < 2;i++)
								{
									M[h-1][v-1+i] = EMBARCACAO1X2I;
									cont1x2++;
									inserido++;
								}
							}
					
						}
						break;
					}
					

				case 2 : //direção vertical
				
					v = rand()%10 + 1;
					h = rand()%10 + 1;

					if((v > 9 || v < 1 ) || (h < 1 ||h > 10)) //ERRO PARA NÃO EXCEDER O TABULEIRO
						verificador++;
				
					else
					{
						for(i = 0;i < 2;i++)
						{							
								//OS INDICES SERÃO SUBTRAIDOS POR 1 PARA COINCIDIR COM A SINTAXE	
							if((M[h-1+i][v-1] == EMBARCACAO1X1  || M[h-1+i][v-1] == EMBARCACAO1X2) || (M[h-1+i][v-1] == EMBARCACAO1X3 || M[h-1+i][v-1] == EMBARCACAO1X4) || (M[h-1+i][v-1] == EMBARCACAOT || M[h-1+i][v-1] == EMBARCACAO1X2))
								verificador++;//Verificação para não sobrepor barcos
						}
						if(verificador == 0)
						{
							if(cont1x2 == 0)
							{
								for(i =0;i < 2;i++)
								{
									M[h-1+i][v-1] = EMBARCACAO1X2;
									cont1x2++;	
									inserido++;	
								}				
							}
							if(cont1x2 == 1)
							{
								for(i =0;i < 2;i++)
								{
									M[h-1+i][v-1] = EMBARCACAO1X2I;
									cont1x2++;
									inserido++;
								}
							}
						}
					}
			}	
		}
		if(cont1x3 < 1)
		{
			verificador = 0;
			direcao = rand()%10 + 1;
			switch(direcao)
			{
				case 1 : //direção horizontal

					v = rand()%10 + 1;
					h = rand()%10 + 1;

					if((v > 10 || v < 1 ) || (h < 1 || h > 8)) //erro,caso exceda o tabuleiro
						verificador++;


					for(i = 0;i < 3;i++)
					{
							//OS INDICES SERÃO SUBTRAIDOS POR 1 PARA COINCIDIR COM A SINTAXE 
						if((M[h-1][v-1+i] == EMBARCACAO1X1 || M[h-1][v-1+i] == EMBARCACAO1X2) || (M[h-1][v-1+i] == EMBARCACAO1X3 || M[h-1][v-1+i] == EMBARCACAO1X4 )|| (M[h-1][v-1+i] == EMBARCACAOT || M[h-1][v-1+i] == EMBARCACAO1X2I))//Verificação para não sobrepor barcos
							verificador++;//Verificação para não sobrepor barcos
					}
					if(verificador == 0)
					{
						for(i = 0;i < 3;i++)
						{
							M[h-1][v-1+i] = EMBARCACAO1X3;
							cont1x3++;
							inserido++;
						}
					}
					break;

				case 2 : //direção vertical

					v = rand()%10 + 1;
					h = rand()%10 + 1;

					if((v > 8 || v < 1 ) || (h < 1 ||h > 10)) //ERRO PARA NÃO EXCEDER O TABULEIRO						
						verificador++;
		
					
					for(i = 0;i < 3;i++)
					{					
							//OS INDICES SERÃO SUBTRAIDOS POR 1 PARA COINCIDIR COM A SINTAXE			
						if((M[h-1+i][v-1] == EMBARCACAO1X1  || M[h-1+i][v-1] == EMBARCACAO1X2) || (M[h-1+i][v-1] == EMBARCACAO1X3 || M[h-1+i][v-1] == EMBARCACAO1X4) || (M[h-1+i][v-1] == EMBARCACAOT || M[h-1+i][v-1] == EMBARCACAO1X2I))
							verificador++;//Verificação para não sobrepor barcos
					}
					if(verificador == 0)
					{
						for(i = 0;i < 3;i++)
						{
							M[h-1+i][v-1] = EMBARCACAO1X3;
							cont1x3++;
							inserido++;
						}
					}
				}
		}
		if(cont1x4 < 1)
		{
			verificador = 0;
			direcao = rand()%10 + 1;

			switch(direcao)
			{
				case 1 : //direção horizontal
					v = rand()%10 + 1;
					h = rand()%10 + 1;

					if((v > 9 || v < 1 ) || (h < 1 || h > 7))//erro,caso exceda o tabuleiro
						verificador++;

					else
					{	
						for(i = 0;i < 4;i++)
						{
							//OS INDICES SERÃO SUBTRAIDOS POR 1 PARA COINCIDIR COM A SINTAXE 
							if((M[h-1][v-1+i] == EMBARCACAO1X1 || M[h-1][v-1+i] == EMBARCACAO1X2) || (M[h-1][v-1+i] == EMBARCACAO1X3 || M[h-1][v-1+i] == EMBARCACAO1X4) || (M[h-1][v-1+i] == EMBARCACAOT || M[h-1][v-1+i] == EMBARCACAO1X2I)) //Verificação para não sobrepor barcos
								verificador++;//Verificação para não sobrepor barcos
						}
						if(verificador == 0)
						{
							for(i = 0;i < 4;i++)
							{
								M[h-1][v-1+i] = EMBARCACAO1X4;
								cont1x4++;
								inserido++;
							}
						}
					}
					break;
				case 2 : //direção vertical

					v = rand()%10 + 1;
					h = rand()%10 + 1;

					if((v > 7 || v < 1 ) || (h < 1 ||h > 9)) //ERRO PARA NÃO EXCEDER O TABULEIRO
						verificador++;
					else
					{
						for(i = 0;i < 4;i++)
						{			
						//OS INDICES SERÃO SUBTRAIDOS POR 1 PARA COINCIDIR COM A SINTAXE			
							if((M[h-1+i][v-1] == EMBARCACAO1X1  || M[h-1+i][v-1] == EMBARCACAO1X2) || (M[h-1+i][v-1] == EMBARCACAO1X3 || M[h-1+i][v-1] == EMBARCACAO1X4) || (M[h-1+i][v-1] == EMBARCACAOT || M[h-1+i][v-1] == EMBARCACAO1X2I))
								verificador++;//Verificação para não sobrepor barcos//Verificação para não sobrepor barcos
						}	
						if(verificador == 0)
						{
							for(i = 0;i < 4;i++)
							{
								M[h-1+i][v-1] = EMBARCACAO1X4;
								cont1x4++;
								inserido++;
							}
						}
					}
					break;
			}
		}
		if(contT < 1)
		{
			verificador = 0;
			rotacao = rand()%4 + 1;
			switch(rotacao)
			{
				case 1 : //rotação 0°

					v = rand()%10 + 1;
					h = rand()%10 + 1;

					if((v > 9 || v < 3 ) || (h < 2 || h > 9))//VERIFICANDO SE EXCEDE O TABULEIRO
						break;
					else
					{	
						//OS INDICES SERÃO SUBTRAIDOS POR 1 PARA COINCIDIR COM A SINTAXE 
						if((M[h-1][v-1+1] == EMBARCACAO1X1 || M[h-1][v-1+1] == EMBARCACAO1X2) || (M[h-1][v-1+1] == EMBARCACAO1X3 || M[h-1][v-1+1] == EMBARCACAO1X4) || (M[h-1][v-1+1] == EMBARCACAOT || M[h-1][v-1+1] == EMBARCACAO1X2I)) //Verificação para não sobrepor barcos
							verificador++;

						if((M[h-1][v-1+2] == EMBARCACAO1X1 || M[h-1][v-1+2] == EMBARCACAO1X2) || (M[h-1][v-1+2] == EMBARCACAO1X3 || M[h-1][v-1+2] == EMBARCACAO1X4) || (M[h-1][v-1+2] == EMBARCACAOT || M[h-1][v-1+2] == EMBARCACAO1X2I)) //Verificação para não sobrepor barcos
							verificador++;

						if((M[h-1][v-1] == EMBARCACAO1X1 || M[h-1][v-1] == EMBARCACAO1X2) || (M[h-1][v-1] == EMBARCACAO1X3 || M[h-1][v-1] == EMBARCACAO1X4) ||(M[h-1][v-1] == EMBARCACAOT || M[h-1][v-1] == EMBARCACAO1X2I)) //Verificação para não sobrepor barcos
							verificador++;

						if((M[h-1+1][v-1] == EMBARCACAO1X1 || M[h-1+1][v-1] == EMBARCACAO1X2) || (M[h-1+1][v-1] == EMBARCACAO1X3 || M[h-1+1][v-1] == EMBARCACAO1X4) || (M[h-1+1][v-1] == EMBARCACAOT || M[h-1+1][v-1] == EMBARCACAO1X2I)) //Verificação para não sobrepor barcos
							verificador++;
		
						if((M[h-1-1][v-1] == EMBARCACAO1X1 || M[h-1-1][v-1] == EMBARCACAO1X2) || (M[h-1-1][v-1] == EMBARCACAO1X3 || M[h-1-1][v-1] == EMBARCACAO1X4) || (M[h-1-1][v-1] == EMBARCACAOT || M[h-1-1][v-1] == EMBARCACAO1X2I)) //Verificação para não sobrepor barcos
							verificador++;
						if(verificador == 0)
						{
									
							M[h-1][v-1] = EMBARCACAOT;
							M[h-1+1][v-1] = EMBARCACAOT;
							M[h-1+2][v-1] = EMBARCACAOT;	
							M[h-1][v-1+1] = EMBARCACAOT;
							M[h-1][v-1-1] = EMBARCACAOT;
							contT++;
							inserido++;
						}
					}
					break;
				case 2 : //rotação 90°

					v = rand()%10 + 1;
					h = rand()%10 + 1;

					if((v > 9 || v < 2 ) || (h < 1 || h > 8))//VERIFICANDO SE EXCEDE O TABULEIRO	
						break;	
						
					else
					{	
						//OS INDICES SERÃO SUBTRAIDOS POR 1 PARA COINCIDIR COM A SINTAXE
						//OS INDICES SERÃO SUBTRAIDOS POR 1 PARA COINCIDIR COM A SINTAXE
						if((M[h-1+1][v-1] == EMBARCACAO1X1 || M[h-1+1][v-1] == EMBARCACAO1X2) || (M[h-1+1][v-1] == EMBARCACAO1X3 || M[h-1+1][v-1] == EMBARCACAO1X4) || (M[h-1+1][v-1] == EMBARCACAOT || M[h-1+1][v-1] == EMBARCACAO1X2I)) //Verificação para não sobrepor barcos
							verificador++;

						if((M[h-1-1][v-1] == EMBARCACAO1X1 || M[h-1-1][v-1] == EMBARCACAO1X2) ||( M[h-1-1][v-1] == EMBARCACAO1X3 || M[h-1-1][v-1] == EMBARCACAO1X4) || (M[h-1-1][v-1] == EMBARCACAOT || M[h-1-1][v-1] == EMBARCACAO1X2I)) //Verificação para não sobrepor barcos
							verificador++;

						if((M[h-1][v-1] == EMBARCACAO1X1 || M[h-1][v-1] == EMBARCACAO1X2) || (M[h-1][v-1] == EMBARCACAO1X3 || M[h-1][v-1] == EMBARCACAO1X4) || (M[h-1][v-1] == EMBARCACAOT || M[h-1][v-1] == EMBARCACAO1X2I)) //Verificação para não sobrepor barcos
							verificador++;

						if((M[h-1][v-1+1] == EMBARCACAO1X1 || M[h-1][v-1+1] == EMBARCACAO1X2) || (M[h-1][v-1+1] == EMBARCACAO1X3 || M[h-1][v-1+1] == EMBARCACAO1X4) || (M[h-1][v-1+1] == EMBARCACAOT || M[h-1][v-1+1] == EMBARCACAO1X2I)) //Verificação para não sobrepor barcos
							verificador++;

						if((M[h-1][v-1+2] == EMBARCACAO1X1 || M[h-1][v-1+2] == EMBARCACAO1X2) ||( M[h-1][v-1+2] == EMBARCACAO1X3 || M[h-1][v-1+2] == EMBARCACAO1X4) || (M[h-1][v-1+2] == EMBARCACAOT || M[h-1][v-1+2] == EMBARCACAO1X2I)) //Verificação para não sobrepor barcos
							verificador++;
						if(verificador == 0)
						{
									
							M[h-1][v-1] = EMBARCACAOT;
							M[h-1+1][v-1] = EMBARCACAOT;
							M[h-1-1][v-1] = EMBARCACAOT;	
							M[h-1][v-1+1] = EMBARCACAOT;
							M[h-1][v-1+2] = EMBARCACAOT;
							contT++;
							inserido++;
						}
						break;
					}
				
				case 3 :

					v = rand()%10 + 1;
					h = rand()%10 + 1;

					if((v > 9 || v < 3 ) || (h < 2 || h > 9 ))//VERIFICANDO SE EXCEDE O TABULEIRO
						break;
			
					else
					{	
						//OS INDICES SERÃO SUBTRAIDOS POR 1 PARA COINCIDIR COM A SINTAXE
						if((M[h-1][v-1+1] == EMBARCACAO1X1 || M[h-1][v-1+1] == EMBARCACAO1X2) || (M[h-1][v-1+1] == EMBARCACAO1X3 || M[h-1][v-1+1] == EMBARCACAO1X4) || (M[h-1][v-1+1] == EMBARCACAOT || M[h-1][v-1+1] == EMBARCACAO1X2I)) //Verificação para não sobrepor barcos
							verificador++;//Verificação para não sobrepor barcos

						if((M[h-1][v-1-1] == EMBARCACAO1X1 || M[h-1][v-1-1] == EMBARCACAO1X2) ||( M[h-1][v-1-1] == EMBARCACAO1X3 || M[h-1][v-1-1] == EMBARCACAO1X4) || (M[h-1][v-1-1] == EMBARCACAOT || M[h-1][v-1-1] == EMBARCACAO1X2I)) //Verificação para não sobrepor barcos
							verificador++;	//Verificação para não sobrepor barcos

						if((M[h-1][v-1] == EMBARCACAO1X1 || M[h-1][v-1] == EMBARCACAO1X2) || (M[h-1][v-1] == EMBARCACAO1X3 || M[h-1][v-1] == EMBARCACAO1X4) || (M[h-1][v-1] == EMBARCACAOT  || M[h-1][v-1] == EMBARCACAO1X2I)) //Verificação para não sobrepor barcos
							verificador++;//Verificação para não sobrepor barcos

						if((M[h-1-1][v-1] == EMBARCACAO1X1 || M[h-1-1][v-1] == EMBARCACAO1X2) || (M[h-1-1][v-1] == EMBARCACAO1X3 || M[h-1-1][v-1] == EMBARCACAO1X4) || (M[h-1-1][v-1] == EMBARCACAOT|| M[h-1-1][v-1] == EMBARCACAO1X2I))//Verificação para não sobrepor barcos
							verificador++;//Verificação para não sobrepor barcos

						if((M[h-1-2][v-1] == EMBARCACAO1X1 || M[h-1-2][v-1] == EMBARCACAO1X2) ||(M[h-1-2][v-1] == EMBARCACAO1X3 || M[h-1-2][v-1] == EMBARCACAO1X4) || (M[h-1-2][v-1] == EMBARCACAOT || M[h-1-2][v-1] == EMBARCACAO1X2I)) //Verificação para não sobrepor barcos
							verificador++;//Verificação para não sobrepor barcos

						if(verificador == 0)
						{
									
							M[h-1][v-1] = EMBARCACAOT;
							M[h-1-1][v-1] = EMBARCACAOT;
							M[h-1-2][v-1] = EMBARCACAOT;	
							M[h-1][v-1+1] = EMBARCACAOT;
							M[h-1][v-1-1] = EMBARCACAOT;
							contT++;
							inserido++;
						}
						break;
					}
					
				case 4 : //rotação 270°

					v = rand()%10 + 1;
					h = rand()%10 + 1;

					if((v > 9 || v < 2 ) || (h < 3 || h > 9))//VERIFICANDO SE EXCEDE O TABULEIRO
						break;
					
					else
					{
						if((M[h-1+1][v-1] == EMBARCACAO1X1 || M[h-1+1][v-1] == EMBARCACAO1X2) || (M[h-1+1][v-1] == EMBARCACAO1X3 || M[h-1+1][v-1] == EMBARCACAO1X4) || (M[h-1+1][v-1] == EMBARCACAOT || M[h-1+1][v-1] == EMBARCACAO1X2I)) //Verificação para não sobrepor barcos
							verificador++;//Verificação para não sobrepor barcos

						if((M[h-1-1][v-1] == EMBARCACAO1X1 || M[h-1-1][v-1] == EMBARCACAO1X2) ||( M[h-1-1][v-1] == EMBARCACAO1X3 || M[h-1-1][v-1] == EMBARCACAO1X4) || (M[h-1-1][v-1] == EMBARCACAOT || M[h-1-1][v-1] == EMBARCACAO1X2I)) //Verificação para não sobrepor barcos
							verificador++;	//Verificação para não sobrepor barcos

						if((M[h-1][v-1] == EMBARCACAO1X1 || M[h-1][v-1] == EMBARCACAO1X2) || (M[h-1][v-1] == EMBARCACAO1X3 || M[h-1][v-1] == EMBARCACAO1X4) || (M[h-1][v-1] == EMBARCACAOT || M[h-1][v-1] == EMBARCACAO1X2I)) //Verificação para não sobrepor barcos
							verificador++;//Verificação para não sobrepor barcos

						if((M[h-1][v-1-1] == EMBARCACAO1X1 || M[h-1][v-1-1] == EMBARCACAO1X2) || (M[h-1][v-1-1] == EMBARCACAO1X3 || M[h-1][v-1-1] == EMBARCACAO1X4) || (M[h-1][v-1-1] == EMBARCACAOT || M[h-1][v-1-1] == EMBARCACAO1X2I))  //Verificação para não sobrepor barcos
							verificador++;//Verificação para não sobrepor barcos

						if((M[h-1][v-1-2] == EMBARCACAO1X1 || M[h-1][v-1-2] == EMBARCACAO1X2) ||( M[h-1][v-1-2] == EMBARCACAO1X3 || M[h-1][v-1-2] == EMBARCACAO1X4) ||(M[h-1][v-1-2] == EMBARCACAOT || M[h-1][v-1-2] == EMBARCACAO1X2I)) //Verificação para não sobrepor barcos
							verificador++;//Verificação para não sobrepor barcos
		
						if(verificador == 0)
						{
									
							M[h-1][v-1] = EMBARCACAOT;
							M[h-1+1][v-1] = EMBARCACAOT;
							M[h-1-1][v-1] = EMBARCACAOT;	
							M[h-1][v-1-1] = EMBARCACAOT;
							M[h-1][v-1-2] = EMBARCACAOT;
							contT++;
							inserido++;
						}
					}
					break;	

			}
		}	
	}
}



//FUNÇÃO MAIN
int main()
{
	srand(time(NULL));
	int escolha;
	iniciaTabuleiro();
	while(inserido < 8) 
	{
		printf("\nEscolha o navio que deseja inserir ou a opção automática de inserção : [1- 1x1/ 2 - 1x2/3 - 1x3/ 4 - 1x4/ 5 - T /6 - Automático] :"); 
		scanf("%d",&escolha);
		switch(escolha)
		{
			case 1 :
				insereEmbarcacao1x1(tabuleiroJogador);
				inserido++;
				break;
			case 2 :
				insereEmbarcacao1x2(tabuleiroJogador);
				inserido++;
				break;
			case 3 :
				insereEmbarcacao1x3(tabuleiroJogador);
				inserido++;
				break;
			case 4 :
				insereEmbarcacao1x4(tabuleiroJogador);
				inserido++;
				break;
			case 5 : 
				insereEmbarcacaoT(tabuleiroJogador);
				inserido++;
				break;
			case 6 : 
				autoInsere(tabuleiroJogador); //NÃO CONSEGUI FAZER A INSERÇÃO AUTOMÁTICA :(
				break;
			default :
				printf("\n%sOpção inválida.%s",REDCOLOR,NONE);
		}	
	}
	zerarContadores();
	autoInsere(tabuleiroIA);
	imprimeTabuleiro(tabuleiroJogador);	
	imprimeTabuleiro(tabuleiroIA);
	
}