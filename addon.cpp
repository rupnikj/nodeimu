#include <node.h>
#include "nodeimu.h"

using namespace v8;

void InitAll(Handle<Object> exports) {
  NodeIMU::Init(exports);
}

NODE_MODULE(addon, InitAll)
