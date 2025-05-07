/* Implementar função solucao_ex4 */
int solucao_ex4(int rdi, int esi) {

    int temp = rdi - 0x11; // cmp    $0x11,%rdi
    int eax;

    short notJle = temp > 0; // jle    0x17 <ex4+23>
    if (notJle) {

        esi -= 0x41; // sub    $0x41,%esi
        temp = esi - 0x1; // cmp    $0x1,%sil

        short notJa = temp <= 0; // ja     0x1f <ex4+31>
        if (notJa) {

            eax = rdi - 0x11;// lea    -0x11(%rdi),%eax
            return eax; // ret

        }

        eax = 0xffffffff; // mov    $0xffffffff,%eax  (<+31>)
        return eax; // ret

    }

    eax = 0x12; // mov    $0x12,%eax  (<+23>)
    eax -= rdi; // sub    %erdi,%eax

    return eax; // ret
}