
#if MODE == FACTORY_LITE
#include "factory_lite/factory_lite.h"
#define MAIN_FUNCTION factory_lite()
#endif

void setup() { MAIN_FUNCTION; }

void loop() {}