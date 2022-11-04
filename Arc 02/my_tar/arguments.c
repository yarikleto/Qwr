#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#include "./arguments.h"
#include "./helpers.h"
#include "./array.h"

bool is_arg_flag(char* arg_value);
void print_usage_message();

arguments_t* parse_arguments(int argc, char** argv) {
  arguments_t* arguments = malloc(sizeof(arguments_t));
  arguments->included_files = create_array();
  arguments->exit_code = ARGUMENTS_EXIT_CODE__SUCCESS;

  // Init default values
  arguments->create_flag = false;
  arguments->append_flag = false;
  arguments->list_flag = false;
  arguments->update_flag = false;
  arguments->extract_flag = false;
  arguments->output_file_flag = NULL;

  char active_flag = '\0';
  for (int arg_index = 1; arg_index < argc; ++arg_index) {
    char* arg_value = argv[arg_index];
    bool is_flag = is_arg_flag(arg_value);

    if (!is_flag && !active_flag) {
      arguments->exit_code = ARGUMENTS_EXIT_CODE__INVALID_FLAG;
      return arguments;
    }

    if (!is_flag) {
      Array__push(arguments->included_files, arg_value);
      continue;
    }

    Array__clear(arguments->included_files);

    for (int i = 1; arg_value[i]; ++i) {
      char flag = arg_value[i];
      active_flag = flag;
      if (flag == 'c') {
        arguments->create_flag = true;
        continue;
      }
      if (flag == 'r') {
        arguments->append_flag = true;
        continue;
      }
      if (flag == 't') {
        arguments->list_flag = true;
        continue;
      }
      if (flag == 'u') {
        arguments->update_flag = true;
        continue;
      }
      if (flag == 'x') {
        arguments->extract_flag = true;
        continue;
      }
      if (flag == 'f') {
        if (arg_value[i + 1] != '\0' || !argv[arg_index + 1]) {
          arguments->output_file_flag = malloc(sizeof(char) * 1);
          arguments->output_file_flag[0] = '\0';
          return arguments;
        }
        arguments->output_file_flag = argv[arg_index + 1];
        arg_index += 1;
        continue;
      }
    }
  }

  return arguments;
}

void free_arguments(arguments_t* arguments) {
  Array__free(arguments->included_files);
  free(arguments);
}

bool is_arg_flag(char* arg_value) {
  return arg_value[0] == '-';
}

void print_usage_message() {
  print_message(STDERR_FILENO, "Usage:\n");
  print_message(STDERR_FILENO, "  List:    tar -tf <archive-filename>\n");
  print_message(STDERR_FILENO, "  Extract: tar -xf <archive-filename>\n");
  print_message(STDERR_FILENO, "  Create:  tar -cf <archive-filename> [filenames...]\n");
}

int validate_arguments(arguments_t* arguments, int argc) {
  bool is_action_flag_included = (
    arguments->create_flag
    || arguments->append_flag
    || arguments->update_flag
    || arguments->extract_flag
  );

  if (arguments->exit_code == ARGUMENTS_EXIT_CODE__INVALID_FLAG) {
    print_usage_message();
    return 1;
  }

  if (arguments->output_file_flag != NULL && get_str_length(arguments->output_file_flag) == 0) {
    print_message(STDERR_FILENO, "tar: Option -f requires an argument\n");
    print_usage_message();
    return 1;
  }

  if (argc == 1 || !is_action_flag_included) {
    print_message(STDERR_FILENO, "tar: Must specify one of -c, -r, -t, -u, -x\n");
    return 1;
  }

  if (arguments->create_flag) {
    if (arguments->append_flag) {
      print_message(STDERR_FILENO, "tar: Can't specify both -r and -c\n");
      return 1;
    }
    if (arguments->update_flag) {
      print_message(STDERR_FILENO, "tar: Can't specify both -u and -c\n");
      return 1;
    }
    if (arguments->extract_flag) {
      print_message(STDERR_FILENO, "tar: Can't specify both -x and -c\n");
      return 1;
    }

    if (arguments->included_files->size == 0) {
      print_message(STDERR_FILENO, "tar: no files or directories specified\n");
      return 1;
    }
  }

  if (arguments->append_flag) {
    if (arguments->update_flag) {
      print_message(STDERR_FILENO, "tar: Can't specify both -u and -r\n");
      return 1;
    }
    if (arguments->extract_flag) {
      print_message(STDERR_FILENO, "tar: Can't specify both -x and -r\n");
      return 1;
    }
  }

  if (arguments->update_flag) {
    if (arguments->extract_flag) {
      print_message(STDERR_FILENO, "tar: Can't specify both -x and -u\n");
      return 1;
    }
  }

  return 0;
}
