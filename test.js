var nodeimu  = require('./index.js');
var IMU = new nodeimu.IMU();
function lala() { IMU.getValue(); }

setInterval(lala, 50);

