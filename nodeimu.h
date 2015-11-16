#ifndef NODEIMU_H
#define NODEIMU_H

#include "RTIMULib.h"

#include <node.h>
#include <node_object_wrap.h>
#include <nan.h>

class NodeIMU : public Nan::ObjectWrap {
 public:
	 static NAN_MODULE_INIT(Init) {
		 v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
		 tpl->SetClassName(Nan::New("IMU").ToLocalChecked());
		 tpl->InstanceTemplate()->SetInternalFieldCount(1);

		 Nan::SetPrototypeMethod(tpl, "getValue", GetValue);

		 Nan::Set(target, Nan::New("IMU").ToLocalChecked(),
			 Nan::GetFunction(tpl).ToLocalChecked());
	 }
  

 private:
  explicit NodeIMU();

  ~NodeIMU();

  static NAN_METHOD(New);

  static NAN_METHOD(GetValue);

  RTIMU *imu;
  RTIMUSettings *settings;

};

#endif
