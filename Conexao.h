
/*
* Menu inicial,direciona o aluno ou professor para os menus respectivos
*/
void menu(void);


/*
* Possui as opcoes cadastro,modificação,remoção,consulta simples e consulta avançada
* Unica funçao que possui acesso as funcoes cadastroAluno,consultaAlunoSim,consultaAlunoAvan
* modificarAluno e removerAluno.
* Nao possui nenhum operacao importante, apenas faz o desvio de fluxo do programa
*/
void menuAluno(void);


/*
* Solicita as informacoes do aluno
* Preenche a query com as informacoes colhidas e faz a conexao com o banco de dados.
*/
void cadastroAluno(void);


/*
* Funcao de consulta simples
* Exibe todos os alunos cadastrados, sem filtrar resultados
*/
void consultaAlunoSim(void);


/*
* Funcao de consulta avancada
* Exibe resultados filtrando por matricula
* Caso a matricula nao seja encontrada,nenhuma mensagem é exibida
*/
void consultaAlunoAvan(void);



/*
* Solicita matricula,conecta ao banco de dados e modifica o registro que contenha a matricula informada
* A escolha da informação que será modificada fica a criterio do usuario
*/
void modificarAluno(void);



/*
* Solicita a matricula,conecta ao banco de dados e exclui todos os registros que contenham a matricula informada
*/
void removerAluno(void);



/*
* Possui as opcoes cadastro,modificacaoo,remocaoo,consulta simples e consulta avançada
* Unica funcaoo que possui acesso as funcoes cadastroProfessor,consultaProfessorSim,consultaProfessorAvan
* modificarProfessor e removerProfessor.
* Nao possui nenhum operacao importante, apenas faz o desvio de fluxo do programa
*/
void menuProfessor(void);


/*
* Solicita as informacoes do professor
* Preenche a query com as informações colhidas e faz a conexao com o banco de dados.
*/
void cadastroProfessor(void);


/*
* Funcao de consulta simples
* Exibe todos os professores cadastrados, sem filtrar resultados
*/
void consultaProfessorSim(void);


/*
* Funcao de consulta avancada
* Exibe resultados filtrando por matricula
* Caso a matricula nao seja encontrada,nenhuma mensagem é exibida
*/
void consultaProfessorAvan(void);



/*
* Solicita matricula,conecta ao banco de dados e modifica o registro que contenha a matricula informada
* A escolha da informacao que será modificada fica a criterio do usuario
*/
void modificarProfessor(void);



/*
* Solicita a matricula,conecta ao banco de dados e exclui todos os registros que contenham a matricula informada
*/
void removerProfessor(void);

