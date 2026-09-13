#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    Definicao dos tipos usados no programa
    Sistema: representa um sistema solar.
        Cada sistema tem um
            - tempo de descoberta (T),
            - nome (S),
            - raio do seu sol (R),
            - quantidade de planetas (P),
            - lista de planetas que fazem parte do sistema
    Planeta: representa um planeta de um sistema.
        Cada planeta tem um:
            - nome (p),
            - raio (r),
            - quantidade de luas (L),
            - lista de luas associadas ao planeta
    Lua: representa uma lua de um planeta.
        Cada lua tem um:
            - nome (l),
            - raio (q)
*/
 
typedef struct
{
    char *l;
    int q;
} Lua;

typedef struct
{
    char *p;
    int r;
    int L;
    Lua *luas;
} Planeta;

typedef struct
{
    int T;
    char *S;
    int R;
    int P;
    Planeta *planetas;
} Sistema;

// Prototipo das funcoes utilizadas no programa
int alocacaofalhou(const void*);
int ler_entrada(Sistema*, char*);
void bromerosort(Sistema*, int, int);
int ritacao(Sistema*, int, int);
int sistcmp(const Sistema*, const Sistema*);
int raiomaiorplaneta(const Sistema*);
int qtdeluas(const Sistema*);
int raiomaiorlua(const Sistema*);

int main()
{
    /*
        Inicialmente, aloca-se memoria para armazenar a lista de sistemas
        e o nome do arquivo de teste.
        Apos isso, a funcao `alocacaofalhou()` eh executada em uma condicional.
        Essa condicional sera executada caso a alocacao
        de pelo menos um dos tipos mencionados acima falhe.
    */
    Sistema *sists = (Sistema *)malloc(1000000 * sizeof(Sistema));
    char* arq = (char*)malloc(1000 * sizeof(char));
    if(alocacaofalhou(sists) || alocacaofalhou(arq)) exit(1);

    /*
        Aqui, pega-se do STDIN o nome do arquivo; que eh passado,
        junto da lista de sistemas, para a funcao `ler_entrada()`.
        Essa funcao eh responsavel por ler os dados do arquivo indicado
        e retornar o numero de sistemas lidos com sucesso.
        Entao, executa-se a funcao `bromerosort()`, responsavel por
        ordernar a lista de sistemas. Como argumento, ela recebe um "intervalo
        fechado", que representa os limites do array: [0, n-1], com n sendo
        o numero de sistemas lidos com sucesso.
    */
    scanf("%s", arq);
    int n = ler_entrada(sists, arq);
    bromerosort(sists, 0, n-1);
    
    /*
        Por fim, eh impresso o nome de cada sistema, retirado da lista
        ja ordenada. Entao, o `free()` libera de volta para o S.O. a memoria
        alocada, e o return 0; encerra a execucao do programa.
    */
    for(int i = n-1; i >= 0; i--)
        printf("%s\n", sists[i].S);

    free(sists);
    free(arq);
    return 0;
}

/*
    Atalho para a checagem de ponteiro nulo.
    Caso o ponteiro (arbitrario, por ser void*) recebido
    seja nulo, a funcao imprime um erro e retorna 1.
    Caso contrario, retorna 0.
*/
int alocacaofalhou(const void* ptr) { 
    if(ptr == NULL) {
        printf("Nao ha memoria suficiente.\n");
        return 1;
    }

    return 0;
}

/*
    Funcao para ler a entrada: recebe a lista de sistemas e o caminho
    do arquivo; retorna o numero de sistemas salvos com sucesso na lista
    recebida.
*/
int ler_entrada(Sistema *sists, char *arq)
{
    /*
        Definicao de variaveis:
            - N: numero de registros (sistemas solares) a serem lidos
            - fp: ponteiro para o arquivo cujo nome eh recebido pela funcao
        
        Apos isso, checa-se se o arquivo foi aberto com sucesso.
        Se nao, o programa eh encerrado.

        Entao, le-se o numero de sistemas solares presentes no arquivo e
        ajusta-se o tamanho da memoria alocada, para nao desperdicar recursos. 
    */
    int N;
    FILE *fp = fopen(arq, "r");

    if (fp == NULL)
    {
        printf("Erro na abertura do arquivo %s\n", arq);
        exit(1);
    }

    fscanf(fp, "%d", &N);
    sists = (Sistema *)realloc(sists, N);

    /*
        Loop para ler as informacoes do arquivo.

        O uso de ponteiros ("alias"), *s, *p e *l, tem o objetivo de encurtar a escrita
        caso contrario, seria necessario escrever `sists[i].planetas[j].luas[k].l`
        para acessar o nome de uma lua arbitraria.

        Em linhas gerais, o algoritmo eh o seguinte:
            - aloca-se memoria para tipos char* e Planeta*
            - verifica-se se a alocacao foi feita com sucesso
                em caso de falha, o programa eh encerrado
            - le-se, do arquivo, as informacoes
            - redimensiona-se as memorias alocadas, para char* e Planeta*,
                com o objetivo de nao desperdicar recursos.
            OBS.: na alocacao de nomes (de sistemas, planetas e luas), foi utilizado
                como "tamanho" 101. Na especificacao diz que cada nome possui no maximo
                100 caracteres; o +1 se refere ao `\0`, que foi considerado nao fazer
                parte da contagem de 100 caracteres "validos".
            OBS.: na realocacao de nomes (de sistemas, planetas e luas), foi utilizado
                como "novo tamanho" o resultado de `strlen() + 1`. A justificativa para isso
                eh contar o caracter `\0`, que nao eh computado pelo `strlen()`.
            OBS.: nao foi feita a checagem de sucesso da alocacao apos os reallocs,
                pois todos essas realocacoes tem como objetivo reduzir o tamanho da
                memoria, nao aumenta-la. Portanto, considerou-se que a operacao sempre
                teria sucesso.
    */

    for (int i = 0; i < N; i++)
    {
        Sistema *s = &sists[i];

        s->S = (char *)malloc(101 * sizeof(char));
        if(alocacaofalhou(s->S)) exit(1);
        fscanf(fp, "%d %s %d %d", &s->T, s->S, &s->R, &s->P);
        s->S = (char*)realloc(s->S, sizeof(char) * (strlen(s->S) + 1));
        s->planetas = (Planeta *)malloc(s->P * sizeof(Planeta));
        if(alocacaofalhou(s->planetas)) exit(1);

        for (int j = 0; j < s->P; j++)
        {
            Planeta *p = &s->planetas[j];

            p->p = (char *)malloc(101 * sizeof(char));
            if(alocacaofalhou(p->p)) exit(1);
            fscanf(fp, "%s %d %d", p->p, &p->r, &p->L);
            p->p = (char*)realloc(p->p, sizeof(char) * (strlen(p->p) + 1));
            p->luas = (Lua *)malloc(p->L * sizeof(Lua));
            if(alocacaofalhou(p->luas)) exit(1);

            for (int k = 0; k < p->L; k++)
            {
                Lua *l = &p->luas[k];

                l->l = (char *)malloc(101 * sizeof(char));
                if(alocacaofalhou(l->l)) exit(1);
                fscanf(fp, "%s %d", l->l, &l->q);
                l->l = (char*)realloc(l->l, sizeof(char) * (strlen(l->l) + 1));
            }
        }
    }

    // Por fim, o arquivo eh fechado e o numero de registros lidos eh retornado
    fclose(fp);
    return N;
}

// Implementacao do pseudo-codigo descrito no PDF
void bromerosort(Sistema *sists, int l, int r)
{
    if(l < r) {
        int q = ritacao(sists, l, r);
        bromerosort(sists, l, q-1);
        bromerosort(sists, q+1, r);
    }
}

// Implementacao da `Ritacao()` descrita no PDF
int ritacao(Sistema *sists, int l, int q)
{
    /*
        Variavel temporaria responsavel pela troca 'in-place'
        dos itens da lista de sistemas.
        OBS.: ainda que ponteiros em structs sejam apenas repassados, nao eh
            necessario realizar uma "copia profunda", uma vez que os nomes,
            ou as listas de planetas e de luas, nao sao alterados; apenas acessados.
            Nesse sentido, nao ha problema o "novo struct" ter um ponteiro apontando
            para um local de memoria do struct antigo.
    */
    int i = l - 1;
    Sistema tmp;
    
    for(int j = l; j < q; j++) {
        if(sistcmp(&sists[q], &sists[j])) {
            i++;
            tmp = sists[i];
            sists[i] = sists[j];
            sists[j] = tmp;
        }
    }
          
    i++;
    tmp = sists[q];
    sists[q] = sists[i];
    sists[i] = tmp;

    return i;
}

/*
    Retorna 1 se o sistema s1 for mais interessante que o sistema s2
    e 0 caso contrario; com base nos criterios predefinidos no PDF
*/
int sistcmp(const Sistema* s1, const Sistema* s2)
{
    int raiomaiorplaneta1 = raiomaiorplaneta(s1);
    int raiomaiorplaneta2 = raiomaiorplaneta(s2);

    int qtdeluas1 = qtdeluas(s1);
    int qtdeluas2 = qtdeluas(s2);

    int raiomaiorlua1 = raiomaiorlua(s1);
    int raiomaiorlua2 = raiomaiorlua(s2);

    if(s1->R != s2->R) return s1->R > s2->R;
    else if(s1->P != s2->P) return s1->P > s2->P;
    else if(raiomaiorplaneta1 != raiomaiorplaneta2) return raiomaiorplaneta1 > raiomaiorplaneta2;
    else if(qtdeluas1 != qtdeluas2) return qtdeluas1 > qtdeluas2;
    else if(raiomaiorlua1 != raiomaiorlua2) return raiomaiorlua1 > raiomaiorlua2;
    else return s1->T < s2->T;
}

// Retorna o raio do maior planeta de um sistema `sist`
int raiomaiorplaneta(const Sistema* sist) {
    int maior = 0;
    for(int i = 0; i < sist->P; i++) {
        Planeta* p = &sist->planetas[i]; 
        if(p->r > maior) maior = p->r; 
    }

    return maior;
}

/*
    Retorna a quantidade total de luas de um sistema: a soma
    da quantidade de luas de cada planeta pertencente ao sistema
*/
int qtdeluas(const Sistema* sist) {
    int luas = 0;
    for(int i = 0; i < sist->P; i++) luas += sist->planetas[i].L;
    return luas;
}

// Retorna o raio da maior lua de um sistema `sist`
int raiomaiorlua(const Sistema* sist) {
    int maior = 0;
    for(int i = 0; i < sist->P; i++) {
        Planeta* p = &sist->planetas[i];
        for(int j = 0; j < p->L; j++) {
            Lua* l = &p->luas[j];
            if(l->q > maior) maior = l->q;
        }
    }

    return maior;
}
