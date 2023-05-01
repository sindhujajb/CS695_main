#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>
#include <curl/curl.h>
#include "http.h"

CURL *hle;


bool socket_sender(const char* endp, int p_val, const char* _top, const char* j_val, long t_val)
{
    printf("			*** ");
	
    curl_global_init(CURL_GLOBAL_ALL);
    hle = curl_easy_init();
    
	struct curl_slist *headers = NULL;
	headers = curl_slist_append(headers, "Content-Type: application/json");

    if(hle) 
    {
	//curl_easy_setopt(hle, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(hle, CURLOPT_POSTFIELDS, j_val);
        curl_easy_setopt(hle, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(hle, CURLOPT_URL, endp);
        curl_easy_setopt(hle, CURLOPT_PORT, p_val);
        curl_easy_setopt(hle, CURLOPT_TIMEOUT, t_val-3);	
      

        curl_easy_cleanup (hle);
    }
    curl_global_cleanup();
   
    printf("\n");
   
    }

bool init_socket(const char* endp, int p_val, bool ft_http)
{
    curl_global_init(CURL_GLOBAL_ALL);
    hle = curl_easy_init();
    if(hle) 
    {
	curl_easy_setopt(hle, CURLOPT_WRITEFUNCTION, write_data);	/* Hide the response */
        curl_easy_setopt(hle, CURLOPT_URL, endp);
        curl_easy_setopt(hle, CURLOPT_PORT, p_val);
        curl_easy_setopt(hle, CURLOPT_TIMEOUT, 1);
       

        curl_easy_cleanup (hle);
    }
    curl_global_cleanup();

  
}

size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp)
{
    return size * nmemb;
}
