#include "nodeimu.h"

using namespace v8;

Persistent<Function> NodeIMU::constructor;

NodeIMU::NodeIMU() {
    settings = new RTIMUSettings("RTIMULib");
    imu = RTIMU::createIMU(settings);

    if ((imu == NULL) || (imu->IMUType() == RTIMU_TYPE_NULL)) {
        printf("No IMU found\n");
        exit(1);
    }

    imu->IMUInit();

    imu->setSlerpPower(0.02);
    imu->setGyroEnable(true);
    imu->setAccelEnable(true);
    imu->setCompassEnable(true);
}

NodeIMU::~NodeIMU() {
    delete imu;
    delete settings;
}

void NodeIMU::Init(Handle<Object> exports) {
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    // Prepare constructor template
    Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
    tpl->SetClassName(String::NewFromUtf8(isolate, "IMU"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    // Prototype
    NODE_SET_PROTOTYPE_METHOD(tpl, "getValue", GetValue);

    constructor.Reset(isolate, tpl->GetFunction());
    exports->Set(String::NewFromUtf8(isolate, "IMU"),
                 tpl->GetFunction());
}

void NodeIMU::New(const FunctionCallbackInfo<Value>& args) {
    NodeIMU* obj = new NodeIMU();    
    obj->Wrap(args.This());
    args.GetReturnValue().Set(args.This());
}

void NodeIMU::GetValue(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    NodeIMU* obj = ObjectWrap::Unwrap<NodeIMU>(args.Holder());

    while (obj->imu->IMURead()) {  
        RTIMU_DATA imuData = obj->imu->getIMUData();
        printf("%s\n",RTMath::displayDegrees("", imuData.fusionPose));
    }
}


