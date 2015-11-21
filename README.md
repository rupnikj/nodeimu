# nodeimu

Nodejs bindings for accessing IMU/pressure/humidity/temperature data using RTIMULib2. The addon uses nodejs/nan. It has been tested on Sense HAT for Raspberry Pi.

## Install

```
git clone https://github.com/rupnikj/nodeimu --recursive && cd nodeimu
npm install node-gyp -g
npm install
```

## Test

```
node test.js
node testSync.js
```
