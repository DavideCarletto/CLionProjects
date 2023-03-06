#ifndef PREPARAZIONEESAME_CALCOLOCOMBINATORIO_H
#define PREPARAZIONEESAME_CALCOLOCOMBINATORIO_H


typedef struct livello{
    int *val, nScelte;
}Livello;

int princ_molt(int pos, Livello *val, int *sol, int n, int cnt);
int disp_semplici(int pos, int *val, int *sol, int *mark, int n, int k, int cnt);
int disp_ripetute(int pos, int *val, int *sol, int n, int k, int cnt);
int perm_semplici(int pos, int *val, int *sol, int *mark, int n, int cnt);
int perm_ripetute(int pos, int *val, int *sol, int *mark, int n, int cnt);
int comb_semplici(int pos, int start, int *val, int *sol, int n, int k, int cnt);
int comb_ripetute(int pos, int start, int *val, int *sol, int n, int k, int cnt);
int powerset_divide_et_impera(int pos, int start, int *val, int *sol, int n, int cnt);
int powerset_disp_rip(int pos, int *val, int *sol, int n, int cnt);
int powerset_comb_semp(int *val, int *sol, int n);
void partition_disp_rip(int pos, int *val, int *sol, int n, int k);
void algoritmo_ER(int pos, int k, int *val, int *sol, int n, int m);
void generaVettoreLivelli(Livello* livelli, int length);
void generaVettore(int *val, int lenght);
void stampaVettore(int *val, int n);
#endif //PREPARAZIONEESAME_CALCOLOCOMBINATORIO_H
