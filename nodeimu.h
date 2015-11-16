#ifndef NODEIMU_H
#define NODEIMU_H

#include "RTIMULib.h"

#include <node.h>
#include <node_object_wrap.h>

class NodeIMU : public node::ObjectWrap {
 public:
  static void Init(v8::Handle<v8::Object> exports);

 private:
  explicit NodeIMU();

  ~NodeIMU();

  static void New(const v8::FunctionCallbackInfo<v8::Value>& args);

  static void GetValue(const v8::FunctionCallbackInfo<v8::Value>& args);

  static v8::Persistent<v8::Function> constructor;

  RTIMU *imu;
  RTIMUSettings *settings; 
};

#endif
