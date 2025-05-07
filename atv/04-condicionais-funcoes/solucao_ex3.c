/* Implementar função solucao_ex3 */
int solucao_ex3(int rdi, int rsi, int *rdx, int *rcx, int *r8) {
    int temp = rdi - rsi; // cmp %rsi,%rdi

    short al = (temp < 0); // setl %al
    int eax = al; // movzbl %al,%eax
    *rdx = eax; // mov %eax,(%rdx)

    al = (temp == 0); // sete %al
    eax = al; // movzbl %al,%eax
    *rcx = eax; // mov %eax,(%rcx)

    al = (temp > 0); // setg %al
    eax = al; // movzbl %al,%eax
    *r8 = eax; // mov %eax,(%r8)

    return eax;
}