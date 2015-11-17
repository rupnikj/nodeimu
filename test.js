var util = require('util')
var nodeimu  = require('./index.js');
var IMU = new nodeimu.IMU();
function dispAccel() { 
  var data = IMU.getValue();
  var sx = data.accelx >= 0 ? ' ' : '';
  var sy = data.accely >= 0 ? ' ' : '';
  var sz = data.accelz >= 0 ? ' ' : '';
  var str = util.format('%s%s %s%s %s%s', sx, data.accelx.toFixed(4), sy, data.accely.toFixed(4), sz, data.accelz.toFixed(4));
  var str2 = util.format(' %s %s %s', sx, data.temperature.toFixed(4), sy, data.pressure.toFixed(4), sz, data.humidity.toFixed(4));
  console.log(str);
}

setInterval(dispAccel, 50);

