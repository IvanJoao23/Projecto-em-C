#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <locale.h>
#include <stdbool.h>
#include<windows.h>
struct PESSOA {
	char nome [50];
	char numeroBilhete[14];
	char endereco[20];
	int codigoPessoa;
	int telefone; 	
};
typedef struct PESSOA PESSOA;

struct CONTA {
	int numeroDeConta, codigoCliente, tipoDeConta, estado;
	float saldo;
};
typedef struct CONTA CONTA;

int numeroDeClientes = 0;
int numeroDeContas = 0; 
PESSOA clientes [100];
CONTA contas[100]; 
FILE *ficheiro;


bool cadastroDeCliente (PESSOA p){
	p.codigoPessoa = numeroDeClientes + 1;
	clientes[numeroDeClientes++] = p;
	return true;
}

int procurarCliente (int codigo){
	int indice;
	for (indice = 0; indice < numeroDeClientes; indice++ ){
		PESSOA p = clientes[indice];
		
		if(p.codigoPessoa == codigo){
			return indice;
		}		
	}	
			return -1;
}


int procurarConta (int codigo){
	int indice;
	for (indice = 0; indice < numeroDeContas; indice++ ){
		contas[indice];
		
		if(contas[indice].codigoCliente == codigo){
			return indice;
		}		
	}	
			printf("Conta não encontada\n");
			return -1;
}

int procurarNumeroDeConta (int codigo){
	int indice;
	for (indice = 0; indice < numeroDeContas; indice++ ){
		contas[indice];
		
		if(contas[indice].numeroDeConta == codigo){
			return indice;
		}		
	}	
			printf("Conta não encontada\n");
			return -1;
}

bool aberturaDeConta(PESSOA p, int tipoDeConta){
	CONTA c;
	c.numeroDeConta = numeroDeContas + 1;
	c.codigoCliente = p.codigoPessoa;
	c.tipoDeConta = tipoDeConta;
	c.saldo = 0;
	c.estado = 1;
	contas[numeroDeContas] = c;
	numeroDeContas++;
	
	printf("Numero de conta: %d\n", c.numeroDeConta);
	printf("Codigo: %d\n", c.codigoCliente);
	printf("Tipo de conta: %d\n", c.tipoDeConta);
	printf("Saldo: %2f\n", c.saldo);
	printf("Estado %d\n", c.estado);
	return true;	
}


void listarClientes (){
	

	int contador;
	for (contador = 0; contador < numeroDeClientes; contador++){
			PESSOA p = clientes[contador];
			printf("\n--------------------------\n");
			printf("Código do Cliente: %d\n", p.codigoPessoa);
			printf("Nome : %s\n", p.nome);
			printf("BI: %s\n", p.numeroBilhete);
			printf("Telefone: %d\n", p.telefone);
			printf("Endereço: %s\n", p.endereco); 
			
	int indice = procurarConta(p.codigoPessoa);
	if(indice != -1){
		CONTA c = contas[indice];
		printf("Numero da conta: %d\n", c.numeroDeConta);
		printf("Codigo conta: %d\n", c.codigoCliente);
		printf("Saldo: %.2f\n", c.saldo);
		printf("Tipo de conta: %d\n", c.tipoDeConta);
		printf("Estado: %d\n", c.estado);
		printf("-------------------------\n");
	
		}
	}
	
}

void voltar(){
	char volta[2];
	printf("[CLIQUE EM QUALQUER TECLA PRA VOLTAR]");
	scanf("%1s", &volta);
}



bool depositarDinheiro (int numeroDeConta, float valor){
	int i;
	i = procurarNumeroDeConta(numeroDeConta);
	if(i != -1){
	 	contas[i].saldo += valor;
	 	return true;
	 	
	}
	
	return false;
}


bool levantarDinheiro (int numeroDeConta, float valor){
	
	int i = procurarNumeroDeConta(numeroDeConta);
	if (i != -1){
		if(contas[i].saldo >= valor){
			
			contas[i].saldo -= valor;
			printf("Valor retirado: %.2f\n", valor);
			printf("Saldo: %2f\n", contas[i].saldo);	
		    return true;
		
		}else{
			
			printf("\nSaldo Insuficiente\n");
				
		}
	}
	return false;
}

 float consultarSaldo(int numeroDeConta){
 	int i;
 	i = procurarNumeroDeConta(numeroDeConta);
	return contas[i].saldo;	
 }
 
 bool transferirDinheiro (int contaAEnviar, int contaAReceber, float Valor){
 	int cEnviar = procurarNumeroDeConta(contaAEnviar);
 	int cReceber= procurarNumeroDeConta(contaAReceber);
 	
 	if (cEnviar != -1 && cReceber != -1){
		if(contas[cEnviar].saldo >= Valor){
			
			int i = procurarCliente(contas[cReceber].codigoCliente);
				
		
					contas[cEnviar].saldo -= Valor;
					contas[cReceber].saldo += Valor;
			
					printf ("Saldo Actual no conta nº%d: %.2f\n", contas[cEnviar].numeroDeConta, contas[cEnviar].saldo);
					printf ("Saldo Actual no conta nº%d: %.2f\n", contas[cReceber].numeroDeConta, contas[cReceber].saldo);		
		}else{
			
			printf ("Saldo insuficiente! ");
		}	
	 }
 		
 return false; 	
 }

bool actualizarDados(PESSOA p, int codigoCliente){
	
	int i = procurarCliente(codigoCliente);
	if ( i != -1){
				
		p.codigoPessoa = codigoCliente;
		clientes[i] = p;
		
		return true; 
	}
	return false;
}


void SalvarDados(){
    ficheiro= fopen("bancoDeDados.txt","w");
      int n;
    if(ficheiro == NULL){
        printf("Impossivel escrever\n");
    }
  
    for(n = 0; n < numeroDeClientes; n++){


        fprintf(ficheiro,"%d,%s,%d,%s,%s,",clientes[n].codigoPessoa,clientes[n].nome,clientes[n].telefone,clientes[n].numeroBilhete,clientes[n].endereco);
		int i = procurarConta(clientes[n].codigoPessoa);
		if (i != -1){
			fprintf(ficheiro,"%d,%d,%f,%d,%d" ,contas[i].numeroDeConta,contas[i].codigoCliente,contas[i].saldo,contas[i].tipoDeConta,contas[i].estado);
			
		}
		fprintf(ficheiro, "\n");
    }
    fclose(ficheiro);
}


void CarregarBackup(){
    PESSOA p;
	CONTA c;
     ficheiro = fopen("bancoDeDados.txt", "r");
	 char linhas[1000];
    if (ficheiro == NULL){
        printf("Houve um erro ao abrir o ficheiro.");
    }else if (ficheiro != NULL){
    
	}
		while(fscanf(ficheiro, "%[^\n]\n", &linhas) == 1){
			
			char *quebras = strtok(linhas, ",");
			char *linha_quebrada[10];		
			int search = 0;
			while (quebras != NULL) {
				linha_quebrada[search] = quebras;
				quebras = strtok(NULL, ",");
				
				search++;
			}			
		    sscanf(linha_quebrada[0], "%d", &p.codigoPessoa);
			strcpy(p.nome, linha_quebrada[1]);			
			strcpy(p.numeroBilhete, linha_quebrada[2]);
			sscanf(linha_quebrada[3], "%d", &p.telefone);
			strcpy(p.endereco, linha_quebrada[4]);
			clientes[numeroDeClientes] = p;
			
		
			numeroDeClientes++;
			
			if (search >= 5){
				continue;
			}else{
				sscanf(linha_quebrada[5], "%d", &c.numeroDeConta);
				sscanf(linha_quebrada[6], "%d", &c.codigoCliente);
				sscanf(linha_quebrada[7], "%f", &c.saldo);
				sscanf(linha_quebrada[8], "%d", &c.tipoDeConta);
				sscanf(linha_quebrada[9], "%d", &c.estado);
				contas[numeroDeContas] = c;
				numeroDeContas++;
			}
		}
		fclose(ficheiro);
}


 int main() {
 	setlocale(LC_ALL, "Portuguese");
 	
	CarregarBackup();
	
	int opcao;
  	bool resposta;
	
 while (opcao != 9) {
	   	printf("----------------------\n ");	
		printf("MENU\n");
		printf("----------------------\n ");
		printf("[1]CADASTRAR\n ");
		printf("[2]LISTAR CLIENTES\n ");
		printf("[3]ABERTURA DE CONTA\n ");
		printf("[4]DEPOSITAR DINHEIRO\n ");
		printf("[5]LEVANTAR DINHEIRO\n ");	
		printf("[6]CONSULTAR \n ");
		printf("[7]TRANSFERIR DINHEIRO\n ");
		printf("[8]ACTUALIZAR DADOS\n ");
		printf("[9]TERMINAR SESSAO\n ");
		printf("OPCAO: ");
		scanf("%d", &opcao);
	
		switch (opcao){
		
		case 1:
			{
			system("cls");
			PESSOA p;
			printf("Digite o seu nome: ");
			scanf("%49s",&p.nome);

			printf("Digite o nº de BI/NIF: ");
			scanf("%14s", &p.numeroBilhete);

			printf("Digite o seu nº de telefone: ");
			scanf("%d", &p.telefone);

			printf("Digite o seu endereço: ");
			scanf("%19s", &p.endereco);
	
			resposta = cadastroDeCliente(p);
			}
			break;
		case 2: 
			{ 
			system("cls");
			listarClientes();
			}	
			break;
		case 3:
			{
			system("cls");
			int codigoCliente, indice;
			printf("Digite o código cliente: ");
			scanf("%d", &codigoCliente);
			
			indice = procurarCliente(codigoCliente);
		
			if (indice != -1){
				int tipoDeConta;
				printf("[0] CONTA PARTICULAR\n[1] CONTA EMPRESA\n");
				scanf("%d", &tipoDeConta);
				resposta = aberturaDeConta(clientes[indice], tipoDeConta);
				
				}else{
					resposta = false;
				}
			}
			break;
		case 4:
			{
			system("cls");
			int numeroDeConta;
			printf("Digite o numero de conta: ");
			scanf("%d", &numeroDeConta);
			
			float montante;
			printf("Digite o montante: ");
			scanf("%f", &montante);
			
			resposta = depositarDinheiro(numeroDeConta, montante);
			}
			break;
		case 5:
			{
				system("cls");
				int numeroDeConta;
				printf("Digite o número de conta: ");
				scanf("%d", &numeroDeConta);
				
				float montante;
				printf("Digite o montante: ");
				scanf("%f", &montante);
				
				resposta = levantarDinheiro(numeroDeConta, montante);
			}
			break;
		case 6:
			{
				system("cls");
				printf("Digite o número de conta: ");
				int numeroDeConta;
				scanf("%d", &numeroDeConta);
				float saldo = consultarSaldo(numeroDeConta);
				printf("Saldo: %.2f", saldo);
				
			}
			
			break;
	
		case 7:
			{
				system("cls");	
				int contaAEnviar, contaAReceber;
				float valor;
				printf("Digite o numero de conta a enviar: ");
				scanf ("%d", &contaAEnviar);
				printf("Digite o numero de conta a receber: ");
				scanf("%d", &contaAReceber); 
				
				printf("Digite o valor: ");
				scanf("%f", &valor);
				
				transferirDinheiro(contaAEnviar, contaAReceber, valor); 	
			}
			
			break;	
			
		case 8:
			{
				system("cls");
				int codigoCliente;
				printf("Digite o código cliente: ");
				scanf("%d", &codigoCliente);
				
				int i = procurarCliente(codigoCliente);
				
				if (i != -1){
					PESSOA p;
					printf("Digite o nome: ");
					scanf("%49s", &p.nome);
					printf("Digite o nº do BI/NIF: ");
					scanf("%14s", &p.numeroBilhete);
					printf("Digite o nº de telefone: ");
					scanf("%d", &p.telefone);
					printf("Digite o endereço: ");
					scanf("%19s", &p.endereco);
					
					resposta = actualizarDados(p, codigoCliente);
										
					}
					break;						
				}
			}
				
				if (resposta == true){
			printf("\n([OPERAÇAO REALIZADA COM SUCESSO!]\n");
			//SalvarDados();
			
		}else{
			printf("\nOPERAÇAO NÃO REALIZADA!\n");	
		}
	

			}
	return 0;	
}
