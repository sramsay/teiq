#include <assert.h>
#include <getopt.h>
#include <libxml/parser.h>
#include <libxml/xmlversion.h>
#include <libxml/xpathInternals.h>
#include <stdlib.h>

#include "license.h"
#include "xpath.h"

static void print_usage(void);

int main(int argc, char* argv[]) {
  if (argc == 1) {
    print_usage();
    return EXIT_SUCCESS;
  }

  static struct option long_options[] = {
      {"help", no_argument, (void*)0, 'h'},
      {"version", no_argument, (void*)0, 'V'},
      {"xpath", required_argument, 0, 'x'},
      {0, 0, 0, 0}};

  int option_index = 0;
  extern char* optarg;
  bool xpath = false;
  char* query = {0};

  for (;;) {
    int opt = getopt_long(argc, argv, "hVx:", long_options, &option_index);

    if (opt == -1) {
      break;
    }

    switch (opt) {
      case '?':
        break;
      case 'h':
        print_usage();
        break;
      case 'V':
        print_version();
        break;
      case 'x':
        xpath = true;
        query = optarg;
        break;
      default:
        print_usage();
    }
  }

  if (xpath) {

		for (; optind < argc - 1; optind++) {
			char* filename = argv[optind];

			LIBXML_TEST_VERSION
			xmlInitParser();
			int options = XML_PARSE_COMPACT | XML_PARSE_BIG_LINES;

			assert(filename);
			xmlDocPtr doc = xmlReadFile(filename, "UTF-8", options);
			if (xpath) {
				printf("%s:\n", filename);
				execute_xpath_query(doc, query);
			}

			xmlFreeDoc(doc);
			xmlCleanupParser();
		}
	}

  return EXIT_SUCCESS;
}

static void print_usage() {
  puts("Usage:");
  puts("  xq [options] <file>");
  puts("");
  puts("Options:");
  puts("  -x --xpath <xpath expression>   \"grep\" a node to standard out");
  puts("");
  puts("  -h --help     Print this message");
  puts("  -v --version  Print version number and license info");
}
