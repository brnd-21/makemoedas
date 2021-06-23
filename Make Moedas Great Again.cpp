#include <time.h>
#include <stdio.h>
#include <conio.h>
#include <fstream>
#include <iostream>
#include <locale.h>
#include <string.h>
#include <windows.h>
#define lista_moedas 500

using namespace std;

enum DOS_COLORS{
    BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN,
    LIGHT_GRAY, DARK_GRAY, LIGHT_BLUE, LIGHT_GREEN, LIGHT_CYAN,
    LIGHT_RED, LIGHT_MAGENTA, YELLOW, WHITE };
/*----------------------------------------------------------------------------*/

/*-----------------Cores das letras---------------------------------------------
Descrição: Procedimento para inserir cores de letras no programa
------------------------------------------------------------------------------*/
void textcolor (DOS_COLORS iColor){
    HANDLE hl = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
    BOOL b = GetConsoleScreenBufferInfo(hl, &bufferInfo);
    bufferInfo.wAttributes &= 0x00F0;
    SetConsoleTextAttribute (hl, bufferInfo.wAttributes |= iColor);
}

// Criando a estrutura do doador de sangue
typedef struct{
	int umcent, cinco, dez, vinte, cinqt, umreal;
}Lista_moedas;

// Variáveis Globais
int auto_inicia = 0, auto_sincroniza = 0, auto_soma = 0, controle_sincrnz = 0, contagem_moedas = 0;
float contagem_moedas_f = 0;

Lista_moedas moedas;

void sincronizar_moedas();

//  Função para inicia automaticamente o sistema
inicio_auto(){
	printf("Iniciando o sistema....");
	
	if(auto_inicia == 1){
		textcolor(CYAN);
		printf("\n(!) O Sistema foi levantado de forma automática, você pode desabilitar esta opção no menu de ferramentas.\n");
		textcolor(WHITE);
		sincronizar_moedas();
	}
	
}

// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);

    return buf;
}

// Função para atualizar o total de Moedas Contabilizadas
void atualiza(int caso){
	
	if(caso == 1){
		moedas.umcent = 0;
		moedas.cinco = 0;
		moedas.dez = 0;
		moedas.vinte = 0;
		moedas.cinqt = 0;
		moedas.umreal = 0;
	}

	contagem_moedas = 0;
	
	contagem_moedas+= moedas.umcent;
	contagem_moedas+= moedas.cinco;
	contagem_moedas+= moedas.dez;
	contagem_moedas+= moedas.vinte;
	contagem_moedas+= moedas.cinqt;
	contagem_moedas+= moedas.umreal;
	
	contagem_moedas_f = contagem_moedas;
}

//	Função para insersão de moedas
int inserir_moedas(){

	int quantidade, atualizado;
	char valor[5], confirma;

	do{
	atualizado = 0;

	printf("\nInforme a Quantidade: ");
	scanf("%d", &quantidade);
	fflush(stdin);

	printf("Informe o Valor Monetário da Unidade: ");
	gets(valor);
	fflush(stdin);

	if(auto_soma != 1){
		if(strcmp(valor, "0.01") == 0){
			moedas.umcent = quantidade;
			atualizado = 1;
		}else if(strcmp(valor, "0.05") == 0){
			moedas.cinco = quantidade;
			atualizado = 1;
		}else if(strcmp(valor, "0.10") == 0){
			moedas.dez = quantidade;
			atualizado = 1;
		}else if(strcmp(valor, "0.25") == 0){
			moedas.vinte = quantidade;
			atualizado = 1;
		}else if(strcmp(valor, "0.50") == 0){
			moedas.cinqt = quantidade;
			atualizado = 1;
		}else if(strcmp(valor, "1.00") == 0){	
			moedas.umreal = quantidade;
			atualizado = 1;
		}
	}else{
		if(strcmp(valor, "0.01") == 0){
			moedas.umcent += quantidade;
			atualizado = 1;
		}else if(strcmp(valor, "0.05") == 0){
			moedas.cinco += quantidade;
			atualizado = 1;
		}else if(strcmp(valor, "0.10") == 0){
			moedas.dez += quantidade;
			atualizado = 1;
		}else if(strcmp(valor, "0.25") == 0){
			moedas.vinte += quantidade;
			atualizado = 1;
		}else if(strcmp(valor, "0.50") == 0){
			moedas.cinqt += quantidade;
			atualizado = 1;
		}else if(strcmp(valor, "1.00") == 0){	
			moedas.umreal += quantidade;
			atualizado = 1;
		}
	}
	
	if(atualizado == 1){
		contagem_moedas += quantidade;
		printf("\nValor Atualizado com Sucesso!");
		
		textcolor(CYAN);
		if(auto_soma == 1){
			printf("\nA Nova Quantidade foi Somada ao montante anterior");
		}else{
			printf("\nA Nova Quantidade substituiu o anterior referente as moedas de %s", valor);
			printf("\nÉ Possível incluir novas moedas e somar elas automaticamente através do menu de ferramentas!");
		}
		textcolor(WHITE);
	}else{
		textcolor(RED);
		printf("\nValor Monetário Digitado não Reconhecido, tente novamente!\n\a");
		textcolor(WHITE);
	}
	
	printf("\nDeseja inserir mais moedas? (S, N): ");
	confirma = getchar();

	}while(confirma == 's' || confirma == 'S');
	
	textcolor(WHITE);
	system("PAUSE");
}

// Função criadora das estatísticas
estastificada(){

	float porc_umcent, porc_cinco, porc_dez, porc_vinte, porc_cinqt, porc_umreal, valor = 0;

//	Calcular a porcentagem
	porc_umcent = (moedas.umcent / contagem_moedas_f) * 100;
	porc_cinco = (moedas.cinco / contagem_moedas_f) * 100;
	porc_dez = (moedas.dez / contagem_moedas_f) * 100;
	porc_vinte = (moedas.vinte / contagem_moedas_f) * 100;
	porc_cinqt = (moedas.cinqt / contagem_moedas_f) * 100;
	porc_umreal = (moedas.umreal / contagem_moedas_f) * 100;

//	Calculando o Valor em Reais
	valor = moedas.umcent * 0.01;
	valor += moedas.cinco * 0.05;
	valor += moedas.dez * 0.10;
	valor += moedas.vinte * 0.25;
	valor += moedas.cinqt * 0.50;
	valor += moedas.umreal * 1.00;

	textcolor(GREEN);
	printf("\nQuantidade | Porcentagem | Valor");
	textcolor(WHITE);
	printf("\n    %d 	        %.2f 	  R$0,01	", moedas.umcent, porc_umcent);
	printf("\n    %d 	        %.2f 	  R$0,05	", moedas.cinco, porc_cinco);
	printf("\n    %d 	        %.2f 	  R$0,10	", moedas.dez, porc_dez);
	printf("\n    %d 	        %.2f	  R$0,25	", moedas.vinte, porc_vinte);
	printf("\n    %d 	        %.2f	  R$0,50	", moedas.cinqt, porc_cinqt);
	printf("\n    %d 	        %.2f	  R$1,00\n", moedas.umreal, porc_umreal);

	printf("]------------------------------[\n");
	printf("      Valor Total: ");

	textcolor(CYAN);
	printf("R$%.2f \n\n", valor);
	textcolor(WHITE);

	system("PAUSE");
}

// Função para guardar os dados num arquivo externo
// Variavel "Local" <- 0 == Int Main, <- 1 == Excluir Doadores
exportar_moedas(int condicao_exporta, int local){

	textcolor(YELLOW);
	if( condicao_exporta <= 2 && local != 1)
		printf("\nIniciando a exportação para um arquivo externo...");

//	Criando o arquivo com condições & usando ponteiro
//  1 = Sobre-escrever | 2 = Auto Completar
	FILE * arquivo;
	if( condicao_exporta == 1 )
		arquivo = fopen("lista_moedas.txt", "w");
	else
		arquivo = fopen("lista_moedas.txt", "a");

//	Escrevendo no arquivo
	fprintf(arquivo,"%d %d %d %d %d %d\n", moedas.umcent, moedas.cinco, moedas.dez, moedas.vinte, moedas.cinqt, moedas.umreal);


//	Fechando o arquivo já escrito
	fclose(arquivo);
	if( condicao_exporta <= 2 && local != 1)
		printf("\nDados Exportados com Sucesso!\n\n");

	textcolor(WHITE);

	if(local != 1)
		system("PAUSE");
}

// Função para pegar os dados do arquivo externo
void sincronizar_moedas(){

	int contador_registro = 0, controle = 0;

	textcolor(YELLOW);
	printf("\nUm Momento, estamos sincronizando com o arquivo externo...\n");
	FILE * arquivo;
	arquivo = fopen("lista_moedas.txt", "r");

//	Inserindo os dados do arquivo externo nas váriaveis do sistema
	fscanf(arquivo,"%d %d %d %d %d %d", &moedas.umcent, &moedas.cinco, &moedas.dez, &moedas.vinte, &moedas.cinqt, &moedas.umreal);

	atualiza(0);

	contador_registro = contagem_moedas;

	printf("\n%d Novo(s) registro(s) disponível(is)", contador_registro);
	printf("\nDados Sincronizados com Sucesso!\n");		

	textcolor(WHITE);

	controle_sincrnz = 1;

//	Fechando o arquivo utilizado na importação
	fclose(arquivo);
	system("PAUSE");
}

// Função para limpar as Moedas
void limpa_arquivo(){

	textcolor(YELLOW);
	printf("\nLimpando a Base de Moedas...\n");
	FILE * arquivo;
	arquivo = fopen("lista_moedas.txt", "w");

//	Inserindo os dados do arquivo externo nas váriaveis do sistema
	fprintf(arquivo,"%d %d %d %d %d %d\n", 0, 0, 0, 0, 0, 0);
	
	atualiza(1);
	
	printf("\nLimpamos todo o cache e o arquivo externo\n");

	textcolor(WHITE);

//	Fechando o arquivo utilizado na importação
	fclose(arquivo);
	system("PAUSE");
}

void gerarRelatorio(){
		
	char dataDia[12];
	
	
	textcolor(YELLOW);
	printf("\nGerando um Relatório para Hoje, \n");
	std::cout << currentDateTime() << std::endl;
	
	FILE * arquivo;
	arquivo = fopen("Relatorio.txt", "a");
	
//	Inserindo os dados do arquivo externo nas váriaveis do sistema
	fprintf(arquivo, "\nEstatísticas\n\n");
	
	fprintf(arquivo,"1 Centavo: %d\n5 Centavos: %d\n10 Centavos: %d\n25 Centavos: %d\n50 Centavos: %d\n1 Real: %d\n", moedas.umcent, moedas.cinco, moedas.dez, moedas.vinte, moedas.cinqt, moedas.umreal);
	
	fprintf(arquivo,"\n]----------------------[");
	
	printf("\nRelatório criado e pronto para Visualização\n");

	textcolor(WHITE);

//	Fechando o arquivo utilizado na importação
	fclose(arquivo);
	system("PAUSE");	
}

// Função para recursos extras
opcoes_extras(){

	int decisao;
	char opcao;
	FILE * arquivo;
	arquivo = fopen("configurações.txt", "w");

	do{
		system("CLS");

//		Lista com as opções que estão ativadas
		printf("\nFunções ligadas( ");
		textcolor(CYAN);

		if(auto_inicia == 1)
			printf("Inicio automático do sistema");
		textcolor(CYAN);

		if(auto_sincroniza == 1 ){
			textcolor(WHITE);
			printf(" | ");
			textcolor(CYAN);
		}

		if(auto_sincroniza == 1)
			printf("Sincronizar Exclusões com o arquivo externo");
		textcolor(WHITE);
		
		if(auto_soma == 1){
			textcolor(WHITE);
			printf(" | ");
			textcolor(CYAN);
		}
		
		if(auto_soma == 1)
			printf("Somar Novas entradas automaticamente.");
		textcolor(WHITE);
		
		printf(" )\n");

		printf("\n1 - Levantar os dados de forma Automática toda vez que o Sistema Iniciar.");
		printf("\n2 - Sincronizar as moedas com o arquivo externo automaticamente.\n");
		printf("\n3 - Somar as Novas entradas automaticamente.\n");
		
		scanf("%d", &decisao);
		fflush(stdin);
	
		textcolor(YELLOW);
		switch(decisao){
			case 1:
				if(auto_inicia == 0){
					auto_inicia = 1;
					printf("\nOk, agora o sistema irá se levantar automaticamente.\n");
				}else{
					auto_inicia = 0;
					printf("\nBlz, estamos desabilitando esta função!\n");
				}
			break;
			case 2:
				if(auto_sincroniza == 0){
					auto_sincroniza = 1;
					printf("\nTudo certo, iremos sincronizar automaticamente o arquivo para você.");
				}else{
					auto_sincroniza = 0;
					printf("\nOk, desabilitando a função ;)");
				}
			break;
			case 3:
				if(auto_soma == 0){
					auto_soma = 1;
					printf("\nCerto, iremos somar as novas entradas.");
				}else{
					auto_soma = 0;
					printf("\nOk, função desabilitada.");
				}
			break;
			default:
				textcolor(LIGHT_RED);
				printf("Opção inválida!");
			break;
		}
		textcolor(WHITE);
	
		printf("\nDeseja ativar ou desativar outro recurso?(s, n): ");
		opcao = getchar();
	
	}while(opcao == 's' || opcao == 'S');
	
	fprintf(arquivo, "%d %d %d", auto_inicia, auto_sincroniza, auto_soma);
	fclose(arquivo);
	system("PAUSE");
}

int main(){
// 	Colorindo as letras
	textcolor(WHITE);

	setlocale(LC_CTYPE, "ptb");
	int opcoes;

//	Verificando as configurações para o funcionamento do sistema
	FILE * arquivo;
	arquivo = fopen("configurações.txt", "r");
	fscanf(arquivo,"%d %d %d", &auto_inicia, &auto_sincroniza, &auto_soma);
	inicio_auto();

	do{
		atualiza(0);
		system("CLS");
		printf("Moedas Contabilizadas: ");
		textcolor(LIGHT_GREEN);
		printf("%d\n", contagem_moedas);
		textcolor(WHITE);
	
		printf("\nInforme a operação\n1 - Inserir Moeda\n2 - Estatísticas\n3 - Salvar num Arquivo Externo ( ");
		textcolor(LIGHT_CYAN);
		printf("Backup_");
		textcolor(WHITE);
		printf(" )\n4 - Limpar Banco de Moedas\n5 - Ferramentas Extras\n6 - Gerar Relatório\n7 - Sair\n\n");
		scanf("%d", &opcoes);
		getchar();
		
		printf("]------------------------------[");
	switch(opcoes){
		case 1:
			inserir_moedas();
		break;
		case 2:
			if( contagem_moedas != 0 )
				estastificada();
			else{
				textcolor(LIGHT_RED);
				printf("\nAinda não existem Moedas Registradas para Consultar as Estatísticas\n");
				textcolor(WHITE);
				system("PAUSE");
			}
		break;
		case 3:
			if( contagem_moedas != 0 ){
				exportar_moedas(1, 0);
			}else{
				textcolor(LIGHT_RED);
				printf("\nAinda não existem Moedas Registradas para fazer uma Exportação!\n");
				textcolor(WHITE);
				system("PAUSE");
			}
		break;
		case 4:
			if( contagem_moedas != 0 ){
				char decisao;
				textcolor(LIGHT_RED);
				printf("\nDeseja Realmente Limpar seu cache? Também iremos limpar seu arquivo externo (!)\n");
				decisao = getchar();

				if(decisao == 's' || decisao == 'S'){
					limpa_arquivo();					
				}
			}else{
				textcolor(LIGHT_RED);
				printf("\nAinda não existem Moedas Registradas para Consultar as Estatísticas\n");
				textcolor(WHITE);
				system("PAUSE");
			}
			textcolor(WHITE);
		break;
		case 5:
			opcoes_extras();
		break;
		case 6:
			gerarRelatorio();
		break;
		default:
			textcolor(YELLOW);
			printf("\n      Encerrando Sessão...");
			textcolor(WHITE);
		break;
	}
	
	}while(opcoes < 7);
}
