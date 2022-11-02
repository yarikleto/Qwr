#include "./arguments.h"

int main (int argc, char** argv) {
  arguments_t* arguments = parse_arguments(argc, argv);

  if (validate_arguments(arguments, argc) > 0) return 1;
}
