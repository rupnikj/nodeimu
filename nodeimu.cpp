#include "nodeimu.h"
#include <nan.h>

using namespace v8;

NodeIMU::NodeIMU() {
    settings = new RTIMUSettings("RTIMULib");
    imu = RTIMU::createIMU(settings);
	pressure = RTPressure::createPressure(settings);
	humidity = RTHumidity::createHumidity(settings);

    if ((imu == NULL) || (imu->IMUType() == RTIMU_TYPE_NULL)) {
        printf("No IMU found\n");
        exit(1);
    }	
	
    imu->IMUInit();
	if (pressure != NULL) { pressure->pressureInit(); }	
	if (humidity != NULL) { humidity->humidityInit(); }

    imu->setSlerpPower((float)0.02);
    imu->setGyroEnable(true);
    imu->setAccelEnable(true);
    imu->setCompassEnable(true);
}

NodeIMU::~NodeIMU() {
    delete imu;
    delete settings;
	delete pressure;
	delete humidity;
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
		
		if (obj->pressure != NULL) { obj->pressure->pressureRead(imuData); }		
		if (obj->humidity != NULL) { obj->humidity->humidityRead(imuData); }

		v8::Local<v8::Object> result = Nan::New<v8::Object>();
		Nan::Set(result, Nan::New("accelx").ToLocalChecked(), Nan::New(imuData.accel.x()));
		Nan::Set(result, Nan::New("accely").ToLocalChecked(), Nan::New(imuData.accel.y()));
		Nan::Set(result, Nan::New("accelz").ToLocalChecked(), Nan::New(imuData.accel.z()));

		if (obj->pressure != NULL) {
			Nan::Set(result, Nan::New("pressure").ToLocalChecked(), Nan::New(imuData.pressure));
			Nan::Set(result, Nan::New("temperature").ToLocalChecked(), Nan::New(imuData.temperature));
		}
		if (obj->humidity != NULL) {
			Nan::Set(result, Nan::New("humidity").ToLocalChecked(), Nan::New(imuData.humidity));
		}

		info.GetReturnValue().Set(result);
	}
}
