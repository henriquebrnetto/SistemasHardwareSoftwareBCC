/* Implementar função solucao_ex1 */
int solucao_ex1(long rdi, long rsi, long rdx) {
    long rax = rsi + rdi;
    long rcx = 4 * rdx + rax;
    rdi *= rdi;
    rax = 2 * rsi + rdi;
    rdx += rax;
    short temp = rcx - rdx;
    short al = temp >= 0;
    rax = al;
    return rax;
}