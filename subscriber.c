
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <curl/curl.h>


int callback(void *data, size_t size, size_t nmemb, void *stream)
{
    size_t bufferSize = nmemb*size + 8;
    char *buffer = calloc(1, bufferSize);

    memcpy(buffer, data, size*nmemb);
    fprintf(stderr, "%s\n", buffer);
    free(buffer);

    return size*nmemb;
}

int main(int argc, char **argv)
{
    int ret = 0;
    CURL *curl = NULL;
    CURLcode res;
    char *URL = "http://127.0.0.1/sub/ch1";
 
    if (argc == 2)
    {
        URL = argv[1];
    }

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    assert(curl != 0);

    while(1)
    {
        curl_easy_setopt(curl, CURLOPT_URL, URL);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
        res = curl_easy_perform(curl);
        if(CURLE_OK != res)
        {
            fprintf(stderr, "curl told us %d\n", res);
        }

        curl_easy_cleanup(curl);
    }
 
    curl_global_cleanup();
    return 0;
}
