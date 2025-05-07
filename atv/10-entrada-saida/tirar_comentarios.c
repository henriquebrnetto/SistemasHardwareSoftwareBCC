#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

// crie suas funções aqui
int main(int argc, char *argv[])
{   
    if (argc != 3) {
        printf("Uso: %s <arquivo_entrada> <arquivo_saida>\n", argv[0]);
        return 1;
    } else {
        int fd = open(argv[1], O_RDONLY);
        int fd2 = open(argv[2], O_WRONLY | O_CREAT, 0700);
        int ret;
        char x[1];

        estado1: ret = read(fd, x, 1);
                if (ret == 0) goto fim;
                if (x[0] == '/') goto estado2;
                else write(fd2, x, 1);
                goto estado1;

        estado2: ret = read(fd, x, 1);
                if (ret == 0) goto fim;
                else if (x[0] == '/') goto estado3;
                else if (x[0] == '*') goto estado4;
                else {
                    write(fd2, "/", 1);
                    write(fd2, x, 1);
                    goto estado1;
                }

        estado3: ret = read(fd, x, 1);
                if (ret == 0) goto fim;
                else if (x[0] == '\n') {
                    write(fd2, x, 1);
                    goto estado1;
                }
                else goto estado3;

        estado4: ret = read(fd, x, 1);
                if (ret == 0) goto fim;
                else if (x[0] == '*') goto estado5;
                else goto estado4;

        estado5: ret = read(fd, x, 1);
                if (ret == 0) goto fim;
                else if (x[0] == '/') goto estado1;
                else goto estado4;

        fim: close(fd);
            close(fd2);
            return 0;

    }
}
