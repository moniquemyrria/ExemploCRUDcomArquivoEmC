
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef struct Funcionario{
	char nome[20], endereco[20];
	int idade;
	float salario;
}Funcionario;

void cadastrar();
void menuCrud();
void listar();
void alterar();
void excluir();
int verificaNomeExistente(char nome[20]);

FILE *pFuncionario;

int main(){
	menuCrud();
}

void cadastrar(){
	char nome[20];
	int op;
	
	system("cls");
	printf("\n\n\t--------------------------------------------------\n\t\t\tCADASTRO DE FUNCIONARIOS\n\t--------------------------------------------------\n\n");
	printf("\n Informe os dados do Funcionario.\n\n Nome: ");
	fflush(stdin);
	gets(nome);
	if ((verificaNomeExistente(nome))==0){
		Funcionario func;
		pFuncionario = fopen("Funcionarios.txt","ab+");
		strcpy(func.nome,strupr(nome));
		printf(" Endereco: ");
		fflush(stdin);
		gets(func.endereco);
		printf(" Idade: ");
		scanf("%d",&func.idade);
		printf(" Salario R$: ");
		scanf("%f",&func.salario);
		if (fwrite(&func,sizeof(Funcionario),1,pFuncionario) !=1){
			printf("\n Nao foi possivel cadastrar o registro!\n");
		}else{
			printf("\n Novo Funcionario cadastrado com sucesso!\n ");
			fclose(pFuncionario);
		}
	}
	else{
		printf("\n Este Funcionario ja esta cadastrado na base de dados!\n ");	
	}
	fclose(pFuncionario);
	getch();
	system("cls");
}

void listar(){
	system("cls");
	Funcionario auxfunc;
	int cont = 0;
	pFuncionario = fopen("Funcionarios.txt","rb");
	if(pFuncionario!=NULL){
		printf("\n\n\t--------------------------------------------------\n\t\t\tLISTAGEM DE FUNCIONARIOS\n\t--------------------------------------------------\n\n");
		
		rewind(pFuncionario);
		while(!feof(pFuncionario)){
			fread(&auxfunc,sizeof(Funcionario),1,pFuncionario);
			if(!feof(pFuncionario)){
				cont++;
				printf(" [%i]\n Nome: %s\n Endereco: %s\n Idade: %d\n Valor Salario R$: %.2f\n\n",cont,auxfunc.nome,auxfunc.endereco,auxfunc.idade,auxfunc.salario);
			}
		}
	}else{
		printf(" Erro ao tentar abrir arquivo\n");
	}
	
	if (cont == 0){
		printf("\n\t  Nao ha funcionarios cadastrados para listar...\n");
	}
	fclose(pFuncionario);
	getch();
	system("cls");
}


void alterar(){
	
	Funcionario auxfunc, funcAlterado;
	int cont=-1;
	char nomePesquisa[20];
	system("cls");
	
	printf("\n\n\t--------------------------------------------------\n\t\t\tALTERAR FUNCIONARIO\n\t--------------------------------------------------\n\n");
	printf("\n Dados da Pesquisa...\n Informe o NOME do Funcionario que deseja alterar:\n ");
	fflush(stdin);
	gets(nomePesquisa);
	if(verificaNomeExistente(strupr(nomePesquisa)) == 1){
		pFuncionario = fopen("Funcionarios.txt","rb+");
		rewind(pFuncionario);
		while(!feof(pFuncionario)){
			fread(&auxfunc,sizeof(Funcionario),1,pFuncionario);
			if(!feof(pFuncionario)){
				cont++;
				if(strcmp(nomePesquisa,auxfunc.nome)==0){
					printf("\n Dados do Funcionario localizado:\n");
					printf(" Nome: %s\n Endereco: %s\n Idade: %d\n Valor Salario R$: %.2f\n\n",auxfunc.nome,auxfunc.endereco,auxfunc.idade,auxfunc.salario);
					printf("\n Informe os dados para alteracao do Funcionario.\n");
					printf(" Nome: ");
					fflush(stdin);
					gets(nomePesquisa);
					fclose(pFuncionario);
					if((verificaNomeExistente(strupr(nomePesquisa))== 0) || ((verificaNomeExistente(strupr(nomePesquisa)) == 1) && (strcmp(auxfunc.nome,strupr(nomePesquisa)) == 0))){
						pFuncionario = fopen("Funcionarios.txt","rb+");
						strcpy(funcAlterado.nome,strupr(strupr(nomePesquisa)));
						printf(" Endereco: ");
						fflush(stdin);
						gets(funcAlterado.endereco);
						printf(" Idade: ");
						scanf("%d",&funcAlterado.idade);
						printf(" Valor Salario R$: ");
						scanf("%f",&funcAlterado.salario);
						fseek(pFuncionario,cont*sizeof(Funcionario),SEEK_SET);
						fwrite(&funcAlterado,sizeof(Funcionario),1,pFuncionario);
						printf("\n Dados do Funcionario alterado com sucesso!\n");		
						fclose(pFuncionario);
						break;
					}
					
					if ((verificaNomeExistente(nomePesquisa) == 1) && (strcmp(auxfunc.nome,nomePesquisa) != 0)){
						printf("\n Nao foi possivel alterar os dados do Funcionario.\n Voce esta tentando inserir um nome que ja existe na base de dados.\n ");
						fclose(pFuncionario);
						break;		
					}
				}
			}
		}
	}else{
		printf("\n Funcionario nao localizado!\n ");		
	}
	
	fclose(pFuncionario);
	getch();
	system("cls");
}

void excluir(){
	char nomePesquisa[20];
	Funcionario funcExcluir;
	FILE *pExcluir;
	system("cls");
	printf("\n\n\t--------------------------------------------------\n\t\t\tENCLUIR FUNCIONARIO\n\t--------------------------------------------------\n\n");
	printf("\n Dados da Pesquisa...\n Informe o NOME do Funcionario que deseja excluir:\n ");
	fflush(stdin);
	gets(nomePesquisa);
	if(verificaNomeExistente(strupr(nomePesquisa))== 1){
		fclose(pFuncionario);
		pFuncionario = fopen("Funcionarios.txt","rb+");
		pExcluir = fopen("pExcluir.txt","wb+");
		rewind(pFuncionario);
		while(!feof(pFuncionario)){
			fread(&funcExcluir,sizeof(Funcionario),1,pFuncionario);
			
			if(!feof(pFuncionario)){
				if(strcmp(funcExcluir.nome,strupr(nomePesquisa))==0){
					printf("\n Funcionario Localizado!\n Registro excluido com sucesso!\n ");
				}else{
					fwrite(&funcExcluir,sizeof(Funcionario),1,pExcluir);
				}
			}
		}
		fclose(pFuncionario);
		fclose(pExcluir);
		remove("Funcionarios.txt");
		rename("pExcluir.txt","Funcionarios.txt");
	}else{
		printf("\n Funcionario nao localizado!\n ");		
	}
	getch();
	system("cls");
}

int verificaNomeExistente(char nome[20]){
	Funcionario aux;

	int verificador = 0; // 1 - Ja existe cadastrado / 0 - Nao cadastrado
	
	pFuncionario = fopen("Funcionarios.txt","rb");
	if(pFuncionario!=NULL){
		rewind(pFuncionario);
		while(!feof(pFuncionario)){
			
			fread(&aux,sizeof(Funcionario),1,pFuncionario);
			if(!feof(pFuncionario)){
				if(strcmp(aux.nome,nome)==0){
					verificador = 1;
				}
			}
		}
	}else{
		printf("\n Erro ao abrir arquivo.\n");	
	}
	fclose(pFuncionario);
	//getch();	
	
	return verificador;
}

void menuCrud(){
	int op;

	do{
		system("cls");
		printf("\n\n\n\n\n\n\t\t\t\t--------------------------------------------------\n\t\t\t\tM E N U    D E  O P C O E S    D O   S I S T E M A\n\t\t\t\t--------------------------------------------------\n\n\n");
		printf("\t\t\t\t\tSelecione uma das Opcoes abaixo...\n\n\t\t\t\t\t\t[1] CADASTRAR\n\t\t\t\t\t\t[2] LISTAR \n\t\t\t\t\t\t[3] ALTERAR \n\t\t\t\t\t\t[4] EXCLUIR\n\t\t\t\t\t\t[0] SAIR\n\n\t\t\t\t\t\tOPCAO: ");
		
		scanf("%d",&op);
		switch(op){
			case 1:
				cadastrar();
				menuCrud();
				break;
			case 2:
				listar();
				menuCrud();
				break;
			case 3:
				alterar();
				menuCrud();
				break;
			case 4: 
				excluir();
				menuCrud();
				break;
			case 0:
				exit(0);
				break;
			
		}
		if ((op < 0) || (op > 4)){
	        printf("\n\n\t\t\t\t\t\tOpcao Invalida!\n ");
	        getch();
		}
	}while(op !=0);
	system("cls");
	getch();
}
