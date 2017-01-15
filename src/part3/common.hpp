/* 046266 Compilation Methods, EE Faculty, Technion                        */
/* part2_helpers.h - Helper functions for project part 2 - API definitions */

#ifndef COMMON_H
#define COMMON_H
#include <stdlib.h>
#include <string.h>
#include <string>

typedef enum { REAL, INT } t_type ;


#ifdef __cplusplus
extern "C" {
#endif



/* common struct to use for bison and flex*/
typedef struct {
	t_type type;
	std::string value; // for keeping multiple types.

} yystype_t;

#define YYSTYPE yystype_t 


#ifdef __cplusplus
} // extern "C"
#endif



#endif //COMMON_H
