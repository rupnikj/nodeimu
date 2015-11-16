#include "nodeimu.h"
#include <nan.h>

using namespace v8;

NodeIMU::NodeIMU() {
    settings = new RTIMUSettings("RTIMULib");
    imu = RTIMU::createIMU(settings);

    if ((imu == NULL) || (imu->IMUType() == RTIMU_TYPE_NULL)) {
        printf("No IMU found\n");
        exit(1);
    }

    imu->IMUInit();

    imu->setSlerpPower((float)0.02);
    imu->setGyroEnable(true);
    imu->setAccelEnable(true);
    imu->setCompassEnable(true);
}

NodeIMU::~NodeIMU() {
    delete imu;
    delete settings;
}

NAN_METHOD(NodeIMU::New) {
	NodeIMU* obj = new NodeIMU();
	obj->Wrap(info.This());
	info.GetReturnValue().Set(info.This());
}

NAN_METHOD(NodeIMU::GetValue) {
	NodeIMU* obj = Nan::ObjectWrap::Unwrap<NodeIMU>(info.This());
	if (obj->imu->IMURead()) {
		RTIMU_DATA imuData = obj->imu->getIMUData();

		auto result = Nan::New<v8::Object>();
		Nan::Set(result, Nan::New("x").ToLocalChecked(), Nan::New(imuData.accel.x()));
		Nan::Set(result, Nan::New("y").ToLocalChecked(), Nan::New(imuData.accel.y()));
		Nan::Set(result, Nan::New("z").ToLocalChecked(), Nan::New(imuData.accel.z()));
		info.GetReturnValue().Set(result);
	}
}