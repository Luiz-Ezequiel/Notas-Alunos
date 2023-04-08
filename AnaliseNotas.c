#include <stdio.h>
#include <string.h>

struct aluno{
    int matricula;
    float notas[3];
    char nome[50];	
};

void ler_notas(struct aluno notas[]){
    FILE *arq_notas;
    arq_notas = fopen("notas.txt", "r");
    if (arq_notas == NULL)
    {
        printf("Erro ao abrir o arquivo notas.txt");
    }
    int i = 0;
    while (!feof(arq_notas)){
        fscanf(arq_notas,"%d %f %f %f", &notas[i].matricula, &notas[i].notas[0], &notas[i].notas[1], &notas[i].notas[2]);
        i++;
    }
    fclose(arq_notas);
}

void ler_nomes(struct aluno nomes[]){
    FILE *arq_nomes;
    arq_nomes = fopen("nomes.txt", "r");
    if (arq_nomes == NULL)
    {
        printf("Erro ao abrir o arquivo nomes.txt");
    }
    int i = 0;
    while (!feof(arq_nomes))
    {
        fscanf(arq_nomes,"%d %[^\n]\n", &(nomes[i].matricula), nomes[i].nome);
        i++;
    }
    fclose(arq_nomes);
}

float media(struct aluno a){
    return(a.notas[0] + a.notas[1] + a.notas[2]) / 3.0;
}

int main() {
    struct aluno notas[30];
    struct aluno nomes[30];
    ler_notas(notas);
    ler_nomes(nomes);
    
    float media_turma = 0.0;
    int num_alunos = 0;
	int i;
	
    FILE *arq_aprovados = fopen("aprovados.txt", "w");
    FILE *arq_reprovados = fopen("reprovados.txt", "w");

    for (i = 0; i < 30; i++) {
        float m = media(notas[i]);
        if (m >= 6.0) {
            fprintf(arq_aprovados, "%d %s %.3f\n", notas[i].matricula, nomes[i].nome, m);
        } else {
            fprintf(arq_reprovados, "%d %s %.3f\n", notas[i].matricula, nomes[i].nome, m);
        }
        media_turma += m;
        num_alunos++;
    }
    fclose(arq_aprovados);
    fclose(arq_reprovados);
    
    media_turma /= 30;
    printf("Media da turma: %.3f", media_turma);
    return 0;
    
}
