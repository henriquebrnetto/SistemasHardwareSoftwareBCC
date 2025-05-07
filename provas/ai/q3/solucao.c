// Seu código da funcao1_solucao

long funcao1_solucao(long rdi, long rsi) {
    long rax = rdi; // mov    %rdi,%rax
    long rcx = 0; // mov    $0x0,%ecx (rcx == ecx)

    // jmp    0x11b <funcao1+23>
    while (rax >= rsi) { // cmp    %rsi,%rax ; jge    0x112 <funcao1+14>
        
        long rdx = rax % rsi; // idiv   %rsi (Não utilizado em cálculos)
        long rax = rax / rsi; // idiv   %rsi
        rcx++; // add    $0x1,%rcx
    }

    rax = rcx; // mov    %rcx,%rax
    return rax; // ret
}