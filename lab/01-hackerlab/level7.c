
long level7() {
    long rsi;
    scanf("%ld", &rsi); // lea    0x8(%rsp),%rsi
    int rax = 0; // mov    $0x0,%eax
    int rcx = 0; // mov    $0x0,%ecx

    // jmp    0x13d3 <level7+51>
    while (rax <= 45) { // cmp    $0x2d,%eax
        rdx = rax; // movslq %eax,%rdx
        rcx += rdx; // add    %rdx,%rcx
        rax += 1; // add    $0x1,%eax
    }

    rdx = 6148914691236517206; // movabs $0x5555555555555556,%rdx
    rax = rcx; // mov    %rcx,%rax
    rdx *= rdx; // imul   %rdx

    rcx = rcx >> 0x3f; // $0x3f,%rcx

    rdx -= rcx; // sub    %rcx,%rdx

    short al = rsi == rdx; // cmp    %rdx,0x8(%rsp) ; sete   %al

    rax = al;
    return rax;
}