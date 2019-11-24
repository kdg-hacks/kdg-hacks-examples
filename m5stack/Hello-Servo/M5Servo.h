#ifndef _M5_SERVO_
#define _M5_SERVO_

// http://ogimotokin.hatenablog.com/entry/2018/07/22/182140

class M5Servo{
protected:
  constexpr static const float MIN_WIDTH_MS = 0.6;
  constexpr static const float MAX_WIDTH_MS = 2.4;
  constexpr static const int LEDC_CHANNEL = 3;

  // サーボ信号の１サイクル　50Hz:20ms
  constexpr static const int LEDC_SERVO_FREQ = 50;
  constexpr static const int LEDC_TIMER_BIT = 16;
  int pin_;
  int angle_;

public:
  // M5Servo();

  void attach(int pin){
    pin_ = pin;
    ledcSetup(LEDC_CHANNEL, LEDC_SERVO_FREQ, LEDC_TIMER_BIT) ; // 16ビット精度で制御
    ledcAttachPin(pin_, LEDC_CHANNEL) ;
  }

  int count(int v){
    float vv = (v + 90) / 180.0 ;
    return (int)(65536 * (MIN_WIDTH_MS + vv * (MAX_WIDTH_MS - MIN_WIDTH_MS)) / 20.0) ;
  }

  /**
   * send reference angle to servo
   * @param angle reference angle which is -90--+90 [deg]
   */
  void write(int angle){
    angle_ = angle;
    ledcWrite(LEDC_CHANNEL, count(angle));
  }

  int read(){
    return angle_;
  }

};

#endif