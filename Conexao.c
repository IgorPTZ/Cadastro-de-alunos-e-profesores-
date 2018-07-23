#include <stdio.h>
#include <windows.h>
#include <winsock2.h>
#include <mysql.h>
#include <string.h>

#define MAX_SIZE 8
#define Q_SIZE 500

MYSQL conexao;
int statusConexao;
char query[Q_SIZE];


void menu(void){

    int sentinela = 0;

    while(sentinela != 3){

        system("cls");
        printf("Universidade Ruy Barbosa\n\n1-Menu de alunos\n2-Menu de docentes\n3-Sair\n\nOpção desejada:");
        scanf("%d",&sentinela);

        switch(sentinela){

            case 1:
                menuAluno();
                break;

            case 2:
                menuProfessor();
                break;

            case 3:
                break;

            default:
                printf("Opção inválida\n");
                system("PAUSE");
                break;

        } //  fim do switch

    } // fim do while

} // fim da funcao menu


void menuAluno(void){

    int opcaoAluno = 0;

    while(opcaoAluno != 6){

        system("cls");
        printf("Opções\n\n1-Cadastrar\n2-Modificar cadastro\n3-Remover cadastro\n4-Consulta simples\n5-Consulta avançada\n6-Sair\n\nOpção desejada:");
        scanf("%d",&opcaoAluno);

        switch(opcaoAluno){

            case 1:
                cadastroAluno();
                break;

            case 2:
                modificarAluno();
                break;

            case 3:
                removerAluno();
                break;

            case 4:
                consultaAlunoSim();
                break;

            case 5:
                consultaAlunoAvan();
                break;

            case 6:
                break;

            default:
                printf("Opção inválida\n");
                system("PAUSE");
                break;

        } // fim do switch

    } // fim do while

}


void cadastroAluno(void){

    mysql_init(&conexao);
    char nome[MAX_SIZE];
    int matricula;


    system("cls");
    printf("Cadastro de alunos\n\n");
    setbuf(stdin,NULL);

    printf("Digite o nome:");
    fgets(nome,MAX_SIZE,stdin);
    nome[strcspn(nome,"\n")] = 0;

    printf("Digite a matricula:");
    scanf("%d",&matricula);

    setbuf(stdin,NULL);


        if(mysql_real_connect(&conexao,"localhost", "root", "", "universidade", 3306, NULL, 0)){

            sprintf(query,"INSERT INTO aluno values('%s','%d');",nome,matricula);

           statusConexao = mysql_query(&conexao,query);

           if(!statusConexao){
                printf("\nCadastro concluído com sucesso\nLinhas afetadas:%d\n",mysql_affected_rows(&conexao));
           }else{
                printf("\nFalha no cadastro.Tente novamente\n");
           }
           system("PAUSE");
           mysql_close(&conexao);

        }else{

            printf("\nFalha na conexão ao banco de dados\n");
            printf("Erro %d: %s\n", mysql_errno(&conexao), mysql_error(&conexao));

        }

}


void consultaAlunoSim(void){

    system("cls");
    mysql_init(&conexao);
    MYSQL_RES * resp;
    MYSQL_ROW linhas;
    MYSQL_FIELD * campos;
    int contador;
    char querySimples[] = "SELECT * FROM aluno;";

    if(mysql_real_connect(&conexao, "localhost", "root", "", "universidade", 3306, NULL, 0)){

        if(mysql_query(&conexao,querySimples)){
            printf("Erro: %s\n:",mysql_error(&conexao));
        }else{

            resp = mysql_store_result(&conexao);

            if(resp){

                campos = mysql_fetch_field(resp);

                for(contador = 0; contador < mysql_num_fields(resp); contador++){
                    printf("%s",(campos[contador].name));

                    if(mysql_num_fields(resp) > 1){
                        printf("\t");
                    }

                }

                printf("\n\n");

                while((linhas = mysql_fetch_row(resp))!= NULL){

                    for(contador = 0; contador < mysql_num_fields(resp); contador++){
                        printf("%s\t",linhas[contador]);
                    }
                    printf("\n");

                }
            }

            printf("\n");
            system("PAUSE");
            mysql_free_result(resp);
            mysql_close(&conexao);

        }

    }else{
        printf("\nFalha de conexao\n");
        printf("Erro %d : %s\n",mysql_errno(&conexao),mysql_error(&conexao));
    }

}


void consultaAlunoAvan(void){

    mysql_init(&conexao);
    MYSQL_RES * resp;
    MYSQL_ROW linhas;
    MYSQL_FIELD * campos;
    int contador;
    int matricula;

    system("cls");
    printf("Digite a matricula:");
    scanf("%d",&matricula);

    sprintf(query,"SELECT * FROM aluno WHERE matricula = '%d';",matricula);

    if(mysql_real_connect(&conexao, "localhost", "root", "", "universidade", 3306, NULL, 0)){

        system("cls");
        if(mysql_query(&conexao,query)){
            printf("Erro: %s\n:",mysql_error(&conexao));
        }else{

            resp = mysql_store_result(&conexao);

            if(resp){

                campos = mysql_fetch_field(resp);

                for(contador = 0; contador < mysql_num_fields(resp); contador++){
                    printf("%s",(campos[contador].name));

                    if(mysql_num_fields(resp) > 1){
                        printf("\t");
                    }

                }

                printf("\n\n");

                while((linhas = mysql_fetch_row(resp))!= NULL){

                    for(contador = 0; contador < mysql_num_fields(resp); contador++){
                        printf("%s\t",linhas[contador]);
                    }
                    printf("\n");

                }
            }

            printf("\n");
            system("PAUSE");
            mysql_free_result(resp);
            mysql_close(&conexao);

        }

    }else{
        printf("\nFalha de conexao\n");
        printf("Erro %d : %s\n",mysql_errno(&conexao),mysql_error(&conexao));
    }

}


void modificarAluno(void){

    mysql_init(&conexao);
    int matricula;
    int novaMatricula;
    char novoNome[MAX_SIZE];
    int opcao;

    system("cls");
    printf("Modificação de cadastro\n\n");

    printf("Digite a matricula:");
    scanf("%d",&matricula);

    printf("\n\nDeseja modificar o nome ou a matricula ? 1-Nome / 2-Matricula:");
    scanf("%d",&opcao);

    switch(opcao){

        case 1:
            setbuf(stdin,NULL);
            printf("Digite o novo nome:");
            fgets(novoNome,MAX_SIZE,stdin);
            novoNome[strcspn(novoNome,"\n")] = 0;
            sprintf(query,"UPDATE aluno SET nome = '%s'WHERE matricula = '%d';",novoNome,matricula);
            break;

        case 2:
            printf("\n\nDigite a nova matricula:");
            scanf("%d",&novaMatricula);
            sprintf(query,"UPDATE aluno SET matricula = '%d'WHERE matricula = '%d';",novaMatricula,matricula);
            break;

    }


        if(mysql_real_connect(&conexao,"localhost", "root", "", "universidade", 3306, NULL, 0)){

           statusConexao = mysql_query(&conexao,query);

           if(!statusConexao){

                if(mysql_affected_rows(&conexao) == 0){
                     printf("\nRegistro não foi encontrado\n");
                }else{
                    printf("\nModificação concluída com sucesso\nLinhas afetadas:%d\n",mysql_affected_rows(&conexao));
                }

           }else{
                printf("\nFalha na modificação.Tente novamente\n");
           }
           system("PAUSE");
           mysql_close(&conexao);

        }else{

            printf("\nFalha na conexão ao banco de dados\n");
            printf("Erro %d: %s\n", mysql_errno(&conexao), mysql_error(&conexao));

        }

}


void removerAluno(void){

    mysql_init(&conexao);
    int matricula;

    system("cls");
    printf("Remoção de cadastro\n\n");

    printf("Digite a matricula:");
    scanf("%d",&matricula);


        if(mysql_real_connect(&conexao,"localhost", "root", "", "universidade", 3306, NULL, 0)){

            sprintf(query,"DELETE FROM aluno WHERE matricula = '%d';",matricula);

           statusConexao = mysql_query(&conexao,query);

           if(!statusConexao){

                if(mysql_affected_rows(&conexao) == 0){
                     printf("\nRegistro não foi encontrado\n");
                }else{
                    printf("\nRemoção concluída com sucesso\nLinhas afetadas:%d\n",mysql_affected_rows(&conexao));
                }

           }else{
                printf("\nFalha na remoção.Tente novamente\n");
           }
           system("PAUSE");
           mysql_close(&conexao);

        }else{

            printf("\nFalha na conexão ao banco de dados\n");
            printf("Erro %d: %s\n", mysql_errno(&conexao), mysql_error(&conexao));

        }

}


void menuProfessor(void){

    int opcaoProfessor = 0;

    while(opcaoProfessor != 6){

        system("cls");
        printf("Opções\n\n1-Cadastrar\n2-Modificar cadastro\n3-Remover cadastro\n4-Consulta simples\n5-Consulta avançada\n6-Sair\n\nOpção desejada:");
        scanf("%d",&opcaoProfessor);

        switch(opcaoProfessor){

            case 1:
                cadastroProfessor();
                break;

            case 2:
                modificarProfessor();
                break;

            case 3:
                removerProfessor();
                break;

            case 4:
                consultaProfessorSim();
                break;

            case 5:
                consultaProfessorAvan();
                break;

            case 6:
                break;

            default:
                printf("Opção inválida\n");
                system("PAUSE");
                break;

        } // fim do switch

    } // fim do while

}


void cadastroProfessor(void){

    mysql_init(&conexao);
    char nome[MAX_SIZE];
    int matricula;

    system("cls");
    printf("Cadastro de professores\n\n");
    setbuf(stdin,NULL);

    printf("Digite o nome:");
    fgets(nome,MAX_SIZE,stdin);
    nome[strcspn(nome,"\n")] = 0;

    printf("Digite a matricula:");
    scanf("%d",&matricula);

    setbuf(stdin,NULL);

        if(mysql_real_connect(&conexao,"localhost", "root", "", "universidade", 3306, NULL, 0)){

            sprintf(query,"INSERT INTO professor values('%s','%d');",nome,matricula);

           statusConexao = mysql_query(&conexao,query);

           if(!statusConexao){
                printf("\nCadastro concluído com sucesso\nLinhas afetadas:%d\n",mysql_affected_rows(&conexao));
           }else{
                printf("\nFalha no cadastro.Tente novamente\n");
           }
           system("PAUSE");
           mysql_close(&conexao);

        }else{

            printf("\nFalha na conexão ao banco de dados\n");
            printf("Erro %d: %s\n", mysql_errno(&conexao), mysql_error(&conexao));

        }

}


void consultaProfessorSim(void){

    system("cls");
    mysql_init(&conexao);
    MYSQL_RES * resp;
    MYSQL_ROW linhas;
    MYSQL_FIELD * campos;
    int contador;
    char querySimples[] = "SELECT * FROM professor;";

    if(mysql_real_connect(&conexao, "localhost", "root", "", "universidade", 3306, NULL, 0)){

        if(mysql_query(&conexao,querySimples)){
            printf("Erro: %s\n:",mysql_error(&conexao));
        }else{

            resp = mysql_store_result(&conexao);

            if(resp){

                campos = mysql_fetch_field(resp);

                for(contador = 0; contador < mysql_num_fields(resp); contador++){
                    printf("%s",(campos[contador].name));

                    if(mysql_num_fields(resp) > 1){
                        printf("\t");
                    }

                }

                printf("\n\n");

                while((linhas = mysql_fetch_row(resp))!= NULL){

                    for(contador = 0; contador < mysql_num_fields(resp); contador++){
                        printf("%s\t",linhas[contador]);
                    }
                    printf("\n");

                }
            }

            printf("\n");
            system("PAUSE");
            mysql_free_result(resp);
            mysql_close(&conexao);

        }

    }else{
        printf("\nFalha de conexao\n");
        printf("Erro %d : %s\n",mysql_errno(&conexao),mysql_error(&conexao));
    }

}


void consultaProfessorAvan(void){

    mysql_init(&conexao);
    MYSQL_RES * resp;
    MYSQL_ROW linhas;
    MYSQL_FIELD * campos;
    int contador;
    int matricula;

    system("cls");
    printf("Digite a matricula:");
    scanf("%d",&matricula);

    sprintf(query,"SELECT * FROM professor WHERE matricula = '%d';",matricula);

    if(mysql_real_connect(&conexao, "localhost", "root", "", "universidade", 3306, NULL, 0)){

        system("cls");
        if(mysql_query(&conexao,query)){
            printf("Erro: %s\n:",mysql_error(&conexao));
        }else{

            resp = mysql_store_result(&conexao);

            if(resp){

                campos = mysql_fetch_field(resp);

                for(contador = 0; contador < mysql_num_fields(resp); contador++){
                    printf("%s",(campos[contador].name));

                    if(mysql_num_fields(resp) > 1){
                        printf("\t");
                    }

                }

                printf("\n\n");

                while((linhas = mysql_fetch_row(resp))!= NULL){

                    for(contador = 0; contador < mysql_num_fields(resp); contador++){
                        printf("%s\t",linhas[contador]);
                    }
                    printf("\n");

                }
            }

            printf("\n");
            system("PAUSE");
            mysql_free_result(resp);
            mysql_close(&conexao);

        }

    }else{
        printf("\nFalha de conexao\n");
        printf("Erro %d : %s\n",mysql_errno(&conexao),mysql_error(&conexao));
    }

}


void modificarProfessor(void){

    mysql_init(&conexao);
    int matricula;
    int novaMatricula;
    char novoNome[MAX_SIZE];
    int opcao;

    system("cls");
    printf("Modificação de cadastro\n\n");

    printf("Digite a matricula:");
    scanf("%d",&matricula);

    printf("\n\nDeseja modificar o nome ou a matricula ? 1-Nome / 2-Matricula:");
    scanf("%d",&opcao);

    switch(opcao){

        case 1:
            setbuf(stdin,NULL);
            printf("Digite o novo nome:");
            fgets(novoNome,MAX_SIZE,stdin);
            novoNome[strcspn(novoNome,"\n")] = 0;
            sprintf(query,"UPDATE professor SET nome = '%s'WHERE matricula = '%d';",novoNome,matricula);
            break;

        case 2:
            printf("\n\nDigite a nova matricula:");
            scanf("%d",&novaMatricula);
            sprintf(query,"UPDATE professor SET matricula = '%d'WHERE matricula = '%d';",novaMatricula,matricula);
            break;

    }


        if(mysql_real_connect(&conexao,"localhost", "root", "", "universidade", 3306, NULL, 0)){

           statusConexao = mysql_query(&conexao,query);

           if(!statusConexao){

                if(mysql_affected_rows(&conexao) == 0){
                     printf("\nRegistro não foi encontrado\n");
                }else{
                    printf("\nModificação concluída com sucesso\nLinhas afetadas:%d\n",mysql_affected_rows(&conexao));
                }

           }else{
                printf("\nFalha na modificação.Tente novamente\n");
           }
           system("PAUSE");
           mysql_close(&conexao);

        }else{

            printf("\nFalha na conexão ao banco de dados\n");
            printf("Erro %d: %s\n", mysql_errno(&conexao), mysql_error(&conexao));

        }

}


void removerProfessor(void){

    mysql_init(&conexao);
    int matricula;

    system("cls");
    printf("Remoção de cadastro\n\n");

    printf("Digite a matricula:");
    scanf("%d",&matricula);


        if(mysql_real_connect(&conexao,"localhost", "root", "", "universidade", 3306, NULL, 0)){

            sprintf(query,"DELETE FROM professor WHERE matricula = '%d';",matricula);

           statusConexao = mysql_query(&conexao,query);

           if(!statusConexao){

                if(mysql_affected_rows(&conexao) == 0){
                     printf("\nRegistro não foi encontrado\n");
                }else{
                    printf("\nRemoção concluída com sucesso\nLinhas afetadas:%d\n",mysql_affected_rows(&conexao));
                }

           }else{
                printf("\nFalha na remoção.Tente novamente\n");
           }
           system("PAUSE");
           mysql_close(&conexao);

        }else{

            printf("\nFalha na conexão ao banco de dados\n");
            printf("Erro %d: %s\n", mysql_errno(&conexao), mysql_error(&conexao));

        }

}










