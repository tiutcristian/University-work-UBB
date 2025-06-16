/*
 * Threadul principal va citi numele fisierului si cheia de criptare de la tastatura, va crea cate un thread pt fiecare chunk (bucata) 
 * de 1024kb a fisierului initial caruia ii va transmite ca si parametru numele si cheia citite de la tastaura precum si index-ul 
 * chunk-ului asignat.
 *
 * Threadul creat va deschide fisierul primit ca parametru, va citi continutul chunk-ului primit din fisier, va cripta continutul 
 * si il va scrie in fisierul destinatie.
 *
 * Threadul principal va astepta pana cand procesarea in thread se va termina si va afisa pe ecran rezultatul criptarii.
 */

/*
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

const int CHUNK = 1024*1024;

typedef struct{
        char filename[100];
        char key;
	int index;
} param;

void* f(void* parametru) {

        param* p = (param*) parametru;

	FILE* readfile = fopen(p->filename, "r");

	char* writefilename = (char*)malloc(106);
	fseek(readfile, p->index * CHUNK, 0);
	if (feof(readfile)){
		strcpy(writefilename, "-");
		fclose(readfile);
		return writefilename;
	}
	
        strcpy(writefilename, p->filename);
        strcat(writefilename, ".crypt");
        FILE* writefile = fopen(writefilename, "w");

        char c = fgetc(readfile);
        while (!feof(readfile)) {
                c = c ^ p->key;
                fputc(c, writefile);
                c = fgetc(readfile);
        }
        fclose(readfile);
        fclose(writefile);

        return writefilename;
}

int main()
{
        char filename[100];
        char key[2];
        printf("Introduceti nume fisier:\n");
        fgets(filename, 100, stdin);
        filename[strlen(filename)-1] = '\0';
        printf("Introduceti cheie criptare:\n");
        read(0, key, 2);

        pthread_t t;
        param* p = (param*)malloc(sizeof(param));
        strcpy(p->filename, filename);
        p->key = key[0];
        char* writefilename;

	p->index = 0;
	pthread_create(&t, NULL, &f, (void*)p);
        pthread_join(t, (void**)&writefilename);

	while(strcmp(writefilename, "-") != 0) {
		FILE* writefile = fopen(writefilename, "r");
		fseek(writefile, p->index * CHUNK, 0);
	
		printf("Content: ==========================\n");
		char c = fgetc(writefile);
		while (!feof(writefile)) {
			putchar(c);
			c = fgetc(writefile);
		}
		fclose(writefile);
		printf("\n===================================\n");

		p->index++;
		pthread_create(&t, NULL, &f, (void*)p);
		pthread_join(t, (void**)&writefilename);
	}

        free(writefilename);
        free(p);
        return 0;
}
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

// Structura pentru a transmite parametrii catre thread
typedef struct {
    char *filename;
    char *key;
    int chunk_index;
} ThreadData;

// Functie simpla de criptare XOR
void simple_encrypt(char *data, size_t len, char *key) {
    size_t key_len = strlen(key);
    for (size_t i = 0; i < len; i++) {
        data[i] ^= key[i % key_len];
    }
}

// Functia thread-ului
void* process_chunk(void *arg) {
    ThreadData *data = (ThreadData*)arg;
    char buffer[1024 * 1024];  // Buffer de 1MB
    ssize_t bytes_read;

    int fd = open(data->filename, O_RDONLY);
    if (fd < 0) {
        perror("Eroare la deschiderea fisierului");
        pthread_exit(NULL);
    }

    off_t offset = data->chunk_index * (1024 * 1024);
    lseek(fd, offset, SEEK_SET);
    bytes_read = read(fd, buffer, sizeof(buffer));
    close(fd);

    if (bytes_read < 0) {
        perror("Eroare la citirea fisierului");
        pthread_exit(NULL);
    }

    simple_encrypt(buffer, bytes_read, data->key);

    char output_filename[256];
    snprintf(output_filename, sizeof(output_filename), "%s.crypt", data->filename);
    fd = open(output_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    lseek(fd, offset, SEEK_SET);
    if (fd < 0) {
        perror("Eroare la deschiderea fisierului de iesire");
        pthread_exit(NULL);
    }
    write(fd, buffer, bytes_read);
    close(fd);

    pthread_exit(NULL);
}

int main() {
    char filename[256], key[256];
    printf("Introduceti numele fisierului: ");
    scanf("%255s", filename);
    printf("Introduceti cheia de criptare: ");
    scanf("%255s", key);

    // Deschide fisierul pentru a obtine dimensiunea sa
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Eroare la deschiderea fisierului");
        return 1;
    }
    off_t file_size = lseek(fd, 0, SEEK_END);
    close(fd);

    int num_chunks = (file_size + 1024 * 1024 - 1) / (1024 * 1024);  // Calculam numarul de chunk-uri

    pthread_t threads[num_chunks];
    ThreadData thread_data[num_chunks];

    for (int i = 0; i < num_chunks; i++) {
        thread_data[i].filename = filename;
        thread_data[i].key = key;
        thread_data[i].chunk_index = i;
        pthread_create(&threads[i], NULL, process_chunk, &thread_data[i]);
    }

    for (int i = 0; i < num_chunks; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Criptarea fisierului s-a terminat.\n");
    return 0;
}

