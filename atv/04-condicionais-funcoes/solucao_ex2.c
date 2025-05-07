/* Implementar função solucao_ex2 */
long vezes2(long a);

long solucao_ex2(long rdi, long rsi) {
    long rbx = rdi;
    rdi = rsi;
    long rax = vezes2(rdi);
    long temp = rax - rbx;
    if (temp > 0) {
        rbx += rbx;
    }

    rax += rbx;

    return rax;
}


