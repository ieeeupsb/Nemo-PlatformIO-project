#pragma once

#include <iostream>
using namespace std;

#define FUNCTION_ERROR_CONTROL(__FUNCTION_CALL__, ERROR_RETURN_VAL) \
  {                                                                 \
    if (__FUNCTION_CALL__ == -1) {                                  \
      cout << "Error in " << #__FUNCTION_CALL__ << endl;            \
      return ERROR_RETURN_VAL;                                      \
    }                                                               \
  }
/**
 * @brief use ; for void functions.
 *
 */
#define TEST_C_LIKE_STRING(__string__, ERROR_RETURN_VAL)             \
  {                                                                  \
    if (!__string__) {                                               \
      cout << "NULL input at send_message(char *input)" << endl;     \
      return #ERROR_RETURN_VAL;                                      \
    }                                                                \
    if (strlen(__string__) < 1) {                                    \
      cout << "Empty message at send_message(char *input) " << endl; \
      return #ERROR_RETURN_VAL;                                      \
    }                                                                \
  }
