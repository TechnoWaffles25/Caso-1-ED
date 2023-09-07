#include <iostream>
#include <string>
#include <stdio.h>
#include <curl/curl.h>
#include "json.hpp"
#include "nodo_doble.h"

using namespace std;
using json = nlohmann::json;

#define CHUNK_SIZE 2048

typedef struct
{
    unsigned char *buffer;
    size_t len;
    size_t buflen;
} get_request;



// static method to act as callback for curl
size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    size_t realsize = size * nmemb;
    get_request *req = (get_request *)userdata;

    printf("receive chunk of %zu bytes\n", realsize);

    while (req->buflen < req->len + realsize + 1)
    {
        req->buffer = (unsigned char *)realloc(req->buffer, req->buflen + CHUNK_SIZE);
        req->buflen += CHUNK_SIZE;
    }
    memcpy(&req->buffer[req->len], ptr, realsize);
    req->len += realsize;
    req->buffer[req->len] = 0;

    return realsize;
};

class Newsapi
{
private:
    CURL *curl;
    CURLcode res;

public:
    vector<struct noticia *> getRecords()
    {

        vector<struct noticia *> result;
        get_request req = {.buffer = NULL, .len = 0, .buflen = 0};

        curl_global_init(CURL_GLOBAL_ALL);
        curl = curl_easy_init();

        // build the URL with the proper entryid
        string url = "https://newsapi.org/v2/everything?q=election&from=2023-08-29&sortBy=popularity&apiKey=61f0db451aa949e893619955b93d0a18";
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/93.0.4577.63 Safari/537.36");
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");

        // prepare the callback function to catch the result json
        req.buffer = (unsigned char *)malloc(CHUNK_SIZE);
        req.buflen = CHUNK_SIZE;

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&req);

        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);

        /* Check for errors */
        if (res == CURLE_OK)
        {
            json responseData = json::parse(req.buffer);
            int contador_news = 0;
            for (auto &item : responseData["articles"])
            {
                try
                {
                    struct noticia *Noticia = (struct noticia*)malloc(sizeof(struct noticia));
                    Noticia->numero = contador_news++;
                    Noticia->titular = item["title"].get<string>();
                    /*News *article = new News(item["author"].get<string>(),
                                             item["title"].get<string>(),
                                             item["description"].get<string>());*/

                    result.push_back(Noticia);
                }
                catch (const exception &e)
                {
                }
            }

            free(req.buffer);
        }
        else
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        // clean the curl objects
        curl_easy_cleanup(curl);
        curl_global_cleanup();

        return result;
    };
};

int main2(void)
{

    Newsapi newsapi;

    vector<struct noticia *> allrecords = newsapi.getRecords();

    //cout << allrecords.at(0)->titular << endl;

    return 0;
}
