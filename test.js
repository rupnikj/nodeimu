var util = require('util')
var nodeimu  = require('./index.js');
var IMU = new nodeimu.IMU();
function dispAccel() { 
  var accel = IMU.getValue();
  var sx = accel.x >= 0 ? ' ' : '';
  var sy = accel.y >= 0 ? ' ' : '';
  var sz = accel.z >= 0 ? ' ' : '';
  var str = util.format('%s%s %s%s %s%s', sx, accel.x.toFixed(4), sy, accel.y.toFixed(4), sz, accel.z.toFixed(4));
  console.log(str);
}

setInterval(dispAccel, 50);

