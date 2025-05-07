int lv3() {

    scanf("%d %d %d", &rsi, &rdx, &rcx);

    int eax = 0;

    int edx = *rcx;
    int ecx = *rdx;

    eax = ecx + edx;
    
    int esi = *rsi;


    eax += esi;
    if (edx <= 157) {
        eax = 0;
        return eax;
    }

    if (ecx <= 157) {
        eax = 0;
        return eax;
    }

    if (esi <= 157) {
        eax = 0;
        return eax;
    }

    if (eax <= 543) {
        eax = 1;
        return eax;
    }
}