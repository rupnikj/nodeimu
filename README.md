# nodeimu

Nodejs 0.12 bindings for accessing IMU data using RTIMULib2.

## Install

```
git clone https://github.com/rupnikj/nodeimu --recursive && cd nodeimu
npm install node-gyp -g
node-gyp configure build
```

## Test

```
var nodeimu  = require('./index.js');
var IMU = new nodeimu.IMU();
IMU.getValue();
```
