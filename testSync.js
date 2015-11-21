var util = require('util')
var nodeimu  = require('./index.js');
var IMU = new nodeimu.IMU();

var num = 0;

console.time("sync");

function dispAccel() { 
  var data = IMU.getValueSync();
  var sx = data.accel.x >= 0 ? ' ' : '';
  var sy = data.accel.y >= 0 ? ' ' : '';
  var sz = data.accel.z >= 0 ? ' ' : '';
  var str = util.format('%s%s %s%s %s%s', sx, data.accel.x.toFixed(4), sy, data.accel.y.toFixed(4), sz, data.accel.z.toFixed(4));
  var str2 = util.format(' %s %s %s', data.temperature.toFixed(4), data.pressure.toFixed(4), data.humidity.toFixed(4));
  console.log(str + str2);
  num++;
  if (num == 100) {
    clearInterval(intv);
    console.timeEnd("sync");
  }
}

var intv = setInterval(dispAccel, 50);

