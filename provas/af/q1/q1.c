// Leia o README antes de iniciar este exercício!

// inclua as bibliotecas necessárias
// #include ...

void *thread1(void *_arg)
{

    printf("A\n");

    printf("B\n");

    printf("C\n");

    return NULL;
}

void *thread2(void *_arg)
{

    printf("D\n");

    printf("E\n");
    
    return NULL;
}

void *thread3(void *_arg)
{

    printf("F\n");

    return NULL;
}

void *thread4(void *_arg)
{

    printf("G\n");

    return NULL;
}

int main(int argc, char *argv[])
{

    // Crie TODAS as threads. Voce deve utilizar semaforos para sincronizacao.

    // Espere por TODAS as threads

    return 0;
}
