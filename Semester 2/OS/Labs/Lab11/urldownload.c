#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <semaphore.h>
#include "curl/curl.h"

static int PARALEL_DOWNLOADS = 3;
static int THR = 5;
static char* urls[] = {
        "https://www.hotnews.ro",
        "https://www.gandul.info",
        "https://www.adevarul.ro",
        "https://www.stackoverflow.com",
        "https://www.microsoft.com",
        "https://www.google.com",
        "https://www.ubbcluj.ro",
        "https://www.utcluj.ro/"
        };
int nextUrl = 0;
pthread_mutex_t nextUrl_mutex = PTHREAD_MUTEX_INITIALIZER;

sem_t downloader_sem;

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    return nmemb;
}

int debug_callback(CURL *handle, curl_infotype type, char *data, size_t size, void *userptr)
{
    return 0;
}

void* downloader(void* p)
{
    while (1)
    {
        int n = 0;
        pthread_mutex_lock(&nextUrl_mutex);
        n = nextUrl++;
        pthread_mutex_unlock(&nextUrl_mutex);

        if ( n > sizeof(urls)/sizeof(urls[0])-1 )
        {
            break;
        }

        sem_wait(&downloader_sem);
        printf("Thread %ld prepare to download url index %d [%s]\n", pthread_self(), n, urls[n]);

        CURL *curl;
        CURLcode res;
    
        curl = curl_easy_init();
        if(curl)
        {
            curl_easy_setopt(curl, CURLOPT_URL, urls[n]);
            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
            curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, debug_callback);
    
            res = curl_easy_perform(curl);

            if(res != CURLE_OK)
                fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));
    
            curl_easy_cleanup(curl);
        }

        printf("Thread %ld done with url %s\n", pthread_self(), urls[n]);
        sem_post(&downloader_sem);
    }
}


int main(void)
{
    pthread_t tids[THR];
    sem_init(&downloader_sem, 0, PARALEL_DOWNLOADS);

    for (int i = 0; i < THR; i++)
    {
        pthread_create(&tids[i], NULL, downloader, NULL);
    }

    for (int i = 0; i < THR; i++)
    {
        pthread_join(tids[i], NULL);
    }

    sem_destroy(&downloader_sem);

    return 0;
}
