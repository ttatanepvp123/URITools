#ifndef URITOOLS_H
#define URITOOLS_H

#include <stdint.h>

typedef struct URI
{
    char *scheme;
    char *user;
    char *host;
    char *path;
    char *query;
    char *fragment;
    uint16_t port;
} URI_t;


char *URIEncode(char *text);
char *URIDecode(char *text);
char *URIBuilder(URI_t URI);

#endif