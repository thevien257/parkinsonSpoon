#include <MPU_6050.h>

#include <SimpleKalmanFilter.h>
#include <Servo.h>

SimpleKalmanFilter x(2, 2, 0.01), y(2, 2, 0.01), z(2, 2, 0.01);
SimpleKalmanFilter pidx(2, 2, 0.01),pidy(2, 2, 0.01),pidz(2, 2, 0.01);
Servo m[3];


struct pid_val {
  
  float error = 0, pre_error = 0;
  float kp = 0, ki = 0, kd = 0;
  float p = 0, i = 0, d = 0;
} x_axis, y_axis, z_axis;



void setup() {
  Serial.begin(19200);
  
  Serial.println("1");

  x_axis.kp = 1; x_axis.ki = 0; x_axis.kd = 0.884;
  y_axis.kp = 1; y_axis.ki = 0; y_axis.kd = 0.884;
  z_axis.kp = 1.3; z_axis.ki = 0.01; z_axis.kd = 0.884;

  m[0].attach(4);
  m[0].write(90);

  m[1].attach(3);
  m[1].write(90);

  m[2].attach(2);
  m[2].write(90);

  // for(int i =0 ;i <= 180 ;i ++){
  //   m[0].write(i);
  //   delay(10);
  // }
  // while(1);
  setup_mpu();
  delay(1000);
}

void PID(int state) {
  if(state == 1){
  x_axis.error = ypr[1];
  x_axis.p = x_axis.error * x_axis.kp;
  x_axis.i += x_axis.error * x_axis.ki;
  x_axis.d = ((x_axis.error - x_axis.pre_error) * 0.1 / 0.01) * x_axis.kd;

  x_axis.pre_error = x_axis.error;
  x_axis.i = max(min(x_axis.i,10),-10);
  //Serial.print("hel");
  int16_t pid_out = pidx.updateEstimate(x_axis.p + x_axis.i + x_axis.d);

  pid_out = max(min(pid_out, 90), -90);
  x_axis.error = max(min(x_axis.error, 90), -90);
  Serial.print(pid_out); Serial.print("\t");
  m[1].write(map(pid_out, -90, 90, 0, 180));
  }
  else if(state == 2){
  y_axis.error = -ypr[2];
  y_axis.p = y_axis.error * y_axis.kp;
  y_axis.i += y_axis.error * y_axis.ki;
  y_axis.d = ((y_axis.error - y_axis.pre_error) * 0.1 / 0.01) * y_axis.kd;

  y_axis.pre_error = y_axis.error;
  y_axis.i = max(min(y_axis.i,10),-10);
  //Serial.print("hel");
  int16_t pid_out = pidy.updateEstimate(y_axis.p + y_axis.i + y_axis.d);

  pid_out = max(min(pid_out, 90), -90);
  y_axis.error = max(min(y_axis.error, 90), -90);
 Serial.print(pid_out); Serial.print("\t");
  m[0].write(map(pid_out, -90, 90, 0, 180));
  }
  else {
  z_axis.error =-ypr[0];
  z_axis.p = z_axis.error * z_axis.kp;
  z_axis.i += (int)z_axis.error * z_axis.ki;
  z_axis.d = ((z_axis.error - z_axis.pre_error) * 0.1 / 0.01) * z_axis.kd;

  z_axis.pre_error = z_axis.error;
  z_axis.i = max(min(z_axis.i,50),-50);
  //Serial.print("hel");
  int16_t pid_out = pidz.updateEstimate(z_axis.p + z_axis.i + z_axis.d);

  pid_out = max(min(pid_out, 90), -90);
  z_axis.error = max(min(z_axis.error, 90), -90);
  // if(pid_out == 90 || pid_out == - 90) z_axis.i=0;
  Serial.println(pid_out);
  m[2].write(map(pid_out, -90, 90, 0, 180));
  }
}

void loop() {
  ypr_output();

  // ypr[0] = z.updateEstimate(ypr[0]);
  // ypr[1] = x.updateEstimate(ypr[1]);
  //ypr[2] = y.updateEstimate(ypr[2]);
  // PID(0);
  // PID(1);
  // PID(2);
 
    // m[1].write(map(ypr[1], -90, 90, 0, 180));
    // m[2].write(map(-ypr[2], -90, 90, 0, 180));
  Serial.print(ypr[0]);
  Serial.print("\t");
  Serial.print(-ypr[1]);
  Serial.print("\t");
  Serial.print(-ypr[2]);
  Serial.println("\n\n");
}
