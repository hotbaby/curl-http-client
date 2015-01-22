#include <string.h>
#include <stdlib.h>
#include <curl/curl.h>

typedef struct {
    char *buf;
    int len;
    int pos;

} readarg_t;

size_t readcb(void *ptr, size_t size, size_t nitems, void *stream)
{
    readarg_t *rarg = (readarg_t *)stream;

    int len = rarg->len - rarg->pos;
    if (len > size * nitems)
    {
        len = size * nitems;
    }

    memcpy(ptr, rarg->buf + rarg->pos, len);
    rarg->pos += len;

    fprintf(stderr, "readcb: %d bytes\n", len);

    return len;
}

int main(int argc, char *argv[])
{
    CURL *curl;
    CURLcode cc;
    char postdata[2048];
    readarg_t rarg;

    memset(postdata, 'a', sizeof(postdata));/* dummy data */

    rarg.buf = postdata;
    rarg.len = sizeof(postdata);
    rarg.pos = 0;

    if ((curl = curl_easy_init()) == NULL)
        exit(1);

    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
    curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1/pub?id=my_channel_1");
    curl_easy_setopt(curl, CURLOPT_POST, 1);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, rarg.len);
    curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_1);

    /* this works, but "Expect: 100-continue" is not added */
    curl_easy_setopt(curl, CURLOPT_READFUNCTION, readcb);
    curl_easy_setopt(curl, CURLOPT_READDATA, &rarg);

    cc = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    return 0;
}

