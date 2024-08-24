#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <unistd.h>

#define SERVER_URL "http://127.0.0.1:8002/tasks"

CURL* init_curl(const char *url, struct curl_slist *headers) {
    // Helper function to initialize and configure a CURL object
    CURL *curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
    }
    return curl;
}

void perform_request(CURL *curl, const char *success_message) {
    // Helper function to perform the CURL request and check the response code
    CURLcode res;
    long http_code = 0;

    res = curl_easy_perform(curl);
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);

    if (res != CURLE_OK) {
        fprintf(stderr, "\ncurl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    } else if (http_code >= 200 && http_code < 300) {
        printf("\n%s\n\n", success_message);
    } else {
        printf("\nFailed to complete request. HTTP status code: %ld\n\n", http_code);
    }

    curl_easy_cleanup(curl);
}

void create_task(int id, const char *title, const char *description, int completed) {
    // Function to create a new task
    CURL *curl;
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");

    char data[256];
    snprintf(data, sizeof(data),
             "{\"id\": %d, \"title\": \"%s\", \"description\": \"%s\", \"completed\": %s}",
             id, title, description, completed ? "true" : "false");

    curl = init_curl(SERVER_URL, headers);
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);

    perform_request(curl, "Task created successfully.");

    curl_slist_free_all(headers);
}

void get_tasks() {
    // Function to retrieve all tasks
    CURL *curl = init_curl(SERVER_URL, NULL);
    perform_request(curl, "Tasks retrieved successfully.");
}

void get_task(int id) {
    // Function to retrieve a specific task by ID
    char url[256];
    snprintf(url, sizeof(url), "%s/%d", SERVER_URL, id);
    CURL *curl = init_curl(url, NULL);
    perform_request(curl, "Task retrieved successfully.");
}

void update_task(int id, const char *title, const char *description, int completed) {
    // Function to update an existing task
    CURL *curl;
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");

    char url[256];
    snprintf(url, sizeof(url), "%s/%d", SERVER_URL, id);

    char data[256];
    snprintf(data, sizeof(data),
             "{\"title\": \"%s\", \"description\": \"%s\", \"completed\": %s}",
             title, description, completed ? "true" : "false");

    curl = init_curl(url, headers);
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PATCH");
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);

    perform_request(curl, "Task updated successfully.");

    curl_slist_free_all(headers);
}

void delete_task(int id) {
    // Function to delete an existing task
    char url[256];
    snprintf(url, sizeof(url), "%s/%d", SERVER_URL, id);
    CURL *curl = init_curl(url, NULL);
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
    perform_request(curl, "Task deleted successfully.");
}

int main(void) {
    printf("Creating a new task...\n");
    create_task(1, "Task 1", "This is task 1", 0);
    sleep(1);

    printf("Creating a task with a duplicate ID (should fail)...\n");
    create_task(1, "Task 1 Duplicate", "This task should not be created", 0);
    sleep(1);

    printf("Retrieving all tasks...\n");
    get_tasks();
    sleep(1);

    printf("Retrieving a non-existent task (should fail)...\n");
    get_task(99); // Attempt to retrieve a task that does not exist
    sleep(1);

    printf("Updating the existing task...\n");
    update_task(1, "Updated Task 1", "This is the updated task 1", 1);
    sleep(1);

    printf("Updating a non-existent task (should fail)...\n");
    update_task(99, "Non-existent Task", "This task does not exist", 1);
    sleep(1);

    printf("Deleting the existing task...\n");
    delete_task(1);
    sleep(1);

    printf("Deleting a non-existent task (should fail)...\n");
    delete_task(99);
    sleep(1);

    return 0;
}
