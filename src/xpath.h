#ifndef INCLUDE_XPATH
#define INCLUDE_XPATH

#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <stdbool.h>

bool execute_xpath_query(xmlDocPtr doc, const char* query);
void write_xpath_results(xmlXPathObjectPtr cur);

#endif
