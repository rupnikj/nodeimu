interface Vector {
  x: number;
  y: number;
  z: number;
}

interface Data {
  timestamp: Date;

  accel: Vector;
  gyro: Vector;
  compass: Vector;
  fusionPose: Vector;

  temperature: number;
  pressure: number;
  humidity: number;
  tiltHeading: number;
}

type Callback = (error: string | null, data: Data) => void;

type CallbackFunction = (args: Callback) => void

export class IMU {
  getValue: CallbackFunction;
  getValueSync: () => Data;
}

