#include "xpath.h"

#include <libxml/parser.h>
#include <libxml/xmlIO.h>
#include <libxml/xmlstring.h>
#include <libxml/xpath.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool execute_xpath_query(xmlDocPtr doc, const char* query) {
  xmlXPathContextPtr ctx = xmlXPathNewContext(doc);

	xmlXPathRegisterNs(ctx, BAD_CAST "tei", BAD_CAST "http://www.tei-c.org/ns/1.0");

  if (!ctx) {
    fprintf(stderr, "Out of memory for XPath query\n");
    return false;
  }

  xmlNodePtr doc_node;
  memcpy(&doc_node, &doc, sizeof(doc));
  ctx->node = doc_node;

  xmlXPathObjectPtr res = xmlXPathEval(BAD_CAST query, ctx);
  xmlXPathFreeContext(ctx);

  if (!res) {
    fprintf(stderr, "Error evaluating XPath\n");
    return false;
  }

  write_xpath_results(res);
  xmlXPathFreeObject(res);

  return EXIT_SUCCESS;
}

void write_xpath_results(xmlXPathObjectPtr cur) {
  switch (cur->type) {
    case XPATH_NODESET: {
      if ((!cur->nodesetval) || (cur->nodesetval->nodeNr <= 0)) {
        fprintf(stderr, "XPath results set is empty\n");
        break;
      }
      xmlOutputBufferPtr buf = xmlOutputBufferCreateFile(stdout, NULL);
      if (!buf) {
        fprintf(stderr, "Out of memory for XPath\n");
        break;
      }
      xmlNodePtr node;
      for (int i = 0; i < cur->nodesetval->nodeNr; i++) {
        node = cur->nodesetval->nodeTab[i];
        xmlNodeDumpOutput(buf, NULL, node, 0, 0, NULL);
        xmlOutputBufferWrite(buf, 1, "\n");
      }
      xmlOutputBufferClose(buf);
      break;
    }
    case XPATH_BOOLEAN:
      if (cur->boolval) {
        puts("true");
      } else {
        puts("false");
      }
      break;
    case XPATH_NUMBER:
      switch (xmlXPathIsInf(cur->floatval)) {
        case 1:
          puts("Infinity");
          break;
        case -1:
          puts("-Infinity");
          break;
        default:
          if (xmlXPathIsNaN(cur->floatval)) {
            puts("NaN");
          } else {
            printf("%g\n", cur->floatval);
          }
      }
      break;
    case XPATH_STRING: {
      const char* string;
      memcpy(&string, &cur->stringval, sizeof(cur->stringval));
      printf("%s\n", string);
      break;
    }
    case XPATH_UNDEFINED:
      fprintf(stderr, "Uninitialized XPath object\n");
      break;
    default:
      fprintf(stderr, "XPath object of unknown type\n");
      break;
  }
}
