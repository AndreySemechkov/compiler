/* 046266 Compilation Methods, EE Faculty, Technion                        */
/* part2_helpers.h - Helper functions for project part 2 - API definitions */

#ifndef COMMON_H
#define COMMON_H
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct node {
    char * type;
    char * value;
    struct node *sibling;
    struct node *child;
} ParserNode;

typedef ParserNode* pNode;

ParserNode *makeNode(const char* type,const char* value, ParserNode *child);

ParserNode *concatList(ParserNode *listHead,ParserNode *newItem);

void dumpParseTree(void);

#ifdef __cplusplus
} // extern "C"
#endif


/* common struct to use for bison and flex*/
typedef struct {
    pNode node;
} yystype_t;

#define YYSTYPE yystype_t 



#endif //COMMON_H
