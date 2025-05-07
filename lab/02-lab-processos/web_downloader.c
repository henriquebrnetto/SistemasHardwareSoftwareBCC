#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <curl/curl.h>

#define MAX_PROCESSES 4
#define MAX_URL_SIZE 2048
#define MAX_FILENAME 256

// Converte URL para nome de arquivo
void url_to_filename(const char *url, char *filename) {
    const char *start = strstr(url, "://");
    start = (start) ? start + 3 : url;

    if (strlen(start) > MAX_FILENAME - 10) {
        fprintf(stderr, "URL muito longa para nome de arquivo\n");
        exit(1);
    }

    strcpy(filename, start);
    for (int i = 0; filename[i]; i++) {
        if (filename[i] == '/' || filename[i] == '.')
            filename[i] = '_';
    }

    const char *ext = strrchr(start, '.');
    if (ext && strchr(ext, '/') == NULL && strlen(ext) <= 5) {
        if (strcmp(ext, ".com") == 0)
            strcat(filename, ".html");
        else
            strcat(filename, ext);
    } else {
        strcat(filename, ".html");
    }
}

// Faz download usando libCurl
void download(const char *url, const char *filename) {
    CURL *curl = curl_easy_init();
    if (!curl) exit(1);

    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        perror("fopen");
        curl_easy_cleanup(curl);
        exit(1);
    }

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "web_downloader");

    if (curl_easy_perform(curl) == CURLE_OK)
        printf("%s baixada com sucesso!\n", url);
    else
        fprintf(stderr, "Erro ao baixar: %s\n", url);

    fclose(fp);
    curl_easy_cleanup(curl);
    exit(0);
}

void process_url(const char *url) {
    char filename[MAX_FILENAME];
    url_to_filename(url, filename);
    download(url, filename);
}

int main(int argc, char *argv[]) {
    int N = MAX_PROCESSES;
    char **urls = NULL;
    int url_count = 0;

    // Processa entrada com -f arquivo
    if (argc >= 2 && strcmp(argv[1], "-f") == 0) {
        if (argc < 3) {
            fprintf(stderr, "Uso: %s -f arquivo [-N num]\n", argv[0]);
            return 1;
        }

        FILE *fp = fopen(argv[2], "r");
        if (!fp) {
            perror("fopen");
            return 1;
        }

        urls = malloc(sizeof(char *) * 1000);
        if (!urls) {
            perror("malloc");
            fclose(fp);
            return 1;
        }

        char linha[MAX_URL_SIZE];
        while (fgets(linha, sizeof(linha), fp)) {
            linha[strcspn(linha, "\n")] = '\0';
            if (strlen(linha) == 0) continue;

            urls[url_count] = strdup(linha);
            if (!urls[url_count]) {
                perror("strdup");
                fclose(fp);
                return 1;
            }
            url_count++;
        }
        fclose(fp);

        if (argc == 5 && strcmp(argv[3], "-N") == 0)
            N = atoi(argv[4]);

    } else {
        urls = malloc(sizeof(char *) * argc);
        if (!urls) {
            perror("malloc");
            return 1;
        }

        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "-N") == 0 && i + 1 < argc) {
                N = atoi(argv[++i]);
            } else {
                urls[url_count] = strdup(argv[i]);
                if (!urls[url_count]) {
                    perror("strdup");
                    return 1;
                }
                url_count++;
            }
        }
    }

    int active = 0;
    for (int i = 0; i < url_count; i++) {
        while (active >= N) {
            wait(NULL);
            active--;
        }

        pid_t pid = fork();
        if (pid == 0) {
            process_url(urls[i]);
        } else if (pid > 0) {
            active++;
        } else {
            perror("fork");
        }
    }

    while (active-- > 0) wait(NULL);

    for (int i = 0; i < url_count; i++)
        free(urls[i]);
    free(urls);
    return 0;
}