#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <time.h> 
#include <unistd.h>  

CURL* init_curl(const char *url, struct curl_slist *headers) {
    CURL *curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "cookies.txt");  // Load cookies from file
    }
    return curl;
}

void perform_request(CURL *curl, const char *success_message) {
    CURLcode res;
    long http_code = 0;

    res = curl_easy_perform(curl);
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);

    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    } else if (http_code >= 200 && http_code < 300) {
        printf("\n%s\n", success_message);
    } else {
        printf("\nFailed to complete request. HTTP status code: %ld\n", http_code);
    }

    curl_easy_cleanup(curl);
}

void set_cookie() {
    CURL *curl = init_curl("http://127.0.0.1:8003/set-cookie/michal", NULL);
    perform_request(curl, "Cookie has been set.");
}

void get_cookie() {
    CURL *curl = init_curl("http://127.0.0.1:8003/get-cookie", NULL);
    perform_request(curl, "Cookie retrieved.");
}

int main() {
    set_cookie();
    sleep(1);

    get_cookie();
    sleep(1);

    return 0;
}
