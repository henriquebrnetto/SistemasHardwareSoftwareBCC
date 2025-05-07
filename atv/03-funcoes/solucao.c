// TODO implemente aqui uma funcao chamada "solucao"

int solucao(long rdi, long rsi, long *rdx) {
    int eax;
    eax = 5*rsi;
    eax += rdi;
    *rdx = eax;
    eax = 3*rsi;
    eax = 4*rdi+eax;
    return eax;
}