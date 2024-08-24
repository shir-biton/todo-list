#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <unistd.h>

CURL* init_curl(char *url, struct curl_slist *headers) {
    CURL *curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "cookies.txt");
        curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "cookies.txt");
    }
    return curl;
}

void perform_request(CURL *curl) {
    CURLcode res;
    int http_code = 0;

    res = curl_easy_perform(curl);
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);

    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    } else if (http_code >= 200 && http_code < 300) {
        printf("\nStatus code: %d\n", http_code);
    } else {
        printf("\nFailed to complete request. HTTP status code: %d\n", http_code);
    }

    curl_easy_cleanup(curl);
}

void set_cookie(char *username) {
    char url[256];
    snprintf(url, sizeof(url), "http://127.0.0.1:8003/set-cookie/%s", username);
    CURL *curl = init_curl(url, NULL);
    perform_request(curl);
}

void get_cookie() {
    CURL *curl = init_curl("http://127.0.0.1:8003/get-cookie", NULL);
    perform_request(curl);
}

int main() {
    get_cookie();
    sleep(1);

    set_cookie("michal");
    sleep(1);

    get_cookie();
    sleep(1);

    return 0;
}
