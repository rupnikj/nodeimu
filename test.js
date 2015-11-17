var util = require('util')
var nodeimu  = require('./index.js');
var IMU = new nodeimu.IMU();
function dispAccel() { 
  var data = IMU.getValue();
  var sx = data.accelx >= 0 ? ' ' : '';
  var sy = data.accely >= 0 ? ' ' : '';
  var sz = data.accelz >= 0 ? ' ' : '';
  var str = util.format('ax:%s%s ay:%s%s az:%s%s', sx, data.accelx.toFixed(4), sy, data.accely.toFixed(4), sz, data.accelz.toFixed(4));
  var str2 = util.format(' t:%s p:%s h:%s', data.temperature.toFixed(4), data.pressure.toFixed(4), data.humidity.toFixed(4));
  console.log(str + str2);
}

setInterval(dispAccel, 50);

