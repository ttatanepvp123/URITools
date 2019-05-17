#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "URITools.h"

char *URIBuilder(URI_t URI){
    char *output = NULL;
    int URISize = 1;
    if (URI.scheme != NULL && URI.path != NULL && URI.host == NULL){
        URISize += strlen(URI.scheme);
        URISize += 1; // ":"
        URISize += strlen(URI.path);
        output = calloc(1, URISize);
        if (output == NULL)
            return NULL;
        sprintf(output, "%s:%s", URI.scheme, URI.path);
        return output;
    } else if (URI.scheme != NULL && URI.host != NULL){
        URISize += strlen(URI.scheme);
        URISize += 3; // "://" (3)
        if (URI.user != NULL){
            URISize += strlen(URI.user);
            URISize += 1; // "@"
        }
        URISize += strlen(URI.host);
        if (URI.port != 0) {
            URISize += 1; // ":"
            if(URI.port < 10)
                URISize += 1; // "X"
            else if(URI.port < 100)
                URISize += 2; // "XX"
            else if(URI.port < 1000)
                URISize += 3; // "XXX"
            else if(URI.port < 10000)
                URISize += 4; // "XXXX"
            else
                URISize += 5;
        }
        if (URI.path != NULL){
            if (URI.path[0] != '/')
                URISize += 1; // "/"
            URISize += strlen(URI.path);
        }
        if (URI.query != NULL){
            URISize += 1; // "?"
            URISize += strlen(URI.query);
        }
        if (URI.fragment != NULL){
            URISize += 1; // "#"
            URISize += strlen(URI.fragment);
        }
        
        output = calloc(1, URISize);
        if (output == NULL)
            return NULL;
        sprintf(output, "%s://", URI.scheme);
        if (URI.user != NULL)
            sprintf(output, "%s%s@", output, URI.user);
        sprintf(output,"%s%s", output, URI.host);
        if (URI.port != 0)
            sprintf(output, "%s:%d", output, URI.port);
        if (URI.path != NULL){
            if (URI.path[0] != '/')
                sprintf(output, "%s/", output);
            sprintf(output, "%s%s", output, URI.path);
        }
        if (URI.query != NULL)
            sprintf(output, "%s?%s", output, URI.query);
        if (URI.fragment != NULL)
            sprintf(output, "%s#%s", output, URI.fragment);
        return output;
    } else {
        return NULL;
    }
    
}