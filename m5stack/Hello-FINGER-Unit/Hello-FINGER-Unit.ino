// M5STACKにFINGER UNIT(FPC1020A)を繋いだサンプルアプリ
// M5STACK上のAボタンを押すと、登録モードになるので、指を載せたままにすると、SUCCESSになればOK
// M5STACK上のBボタンを押すと、認証モードになるので、指を載せると、認証されればSUCCESS,認証NGの場合は、No Such Userになる
// M5STACK上のCボタンを押すと、データを全削除します

#include <M5Stack.h>
#include "finger.h"

uint8_t userNum;           //User number
FingerPrint FP_M;

void CleanScreen()
{
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.fillRect(0,50,400,300,BLACK);
    M5.Lcd.setCursor(0, 50);
    M5.Lcd.setTextSize(2);
    userNum = FP_M.fpm_getUserNum();
    M5.Lcd.print("userNum:");
    M5.Lcd.println(userNum);
}

void setup() {
    M5.begin();
    // 使用するポートに合わせて、コメント外してください
    // Serial2.begin(19200, SERIAL_8N1, 22, 21); // Port-A
    // Serial2.begin(19200, SERIAL_8N1, 36, 26); // Port-B
    // Serial2.begin(19200, SERIAL_8N1, 16, 17); // Port-C
    M5.Lcd.clear(BLACK);
    M5.Lcd.setTextColor(YELLOW);
    M5.Lcd.setTextFont(2);
    M5.Lcd.setTextSize(3);
    M5.Lcd.setCursor(20, 0);
    M5.Lcd.println("Finger example");
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.fillRect(0,50,400,300,BLACK);
    M5.Lcd.setCursor(0, 50);
    M5.Lcd.setTextSize(2);
    userNum = FP_M.fpm_getUserNum();
    M5.Lcd.print("userNum:");
    M5.Lcd.println(userNum);
}

void loop(){
    uint8_t res1;

    // 指紋を登録する
    if(M5.BtnA.wasPressed()){
        CleanScreen();
        M5.Lcd.println("Fingerprint Typing");

        res1 = FP_M.fpm_addUser(userNum,1);
        if(res1 == ACK_SUCCESS){
            M5.Lcd.println("Success");
        }
        else if(res1 == ACK_FAIL){
            M5.Lcd.println("Fail");
        }
        else if(res1 == ACK_FULL){
            M5.Lcd.println("Full");
        }
        else{
            M5.Lcd.println("Timeout");
        }
        
        userNum++;
    }

    // 指紋を照合する
    if(M5.BtnB.wasPressed()){
      CleanScreen();
      M5.Lcd.println("Matching");

      res1 = FP_M.fpm_compareFinger();
      
      if(res1 == ACK_SUCCESS){
          M5.Lcd.println("Success");
      }
      if(res1 == ACK_NOUSER){
          M5.Lcd.println("No Such User");
      }
      if(res1 == ACK_TIMEOUT){
          M5.Lcd.println("Timeout");
      }
    }

    // データの削除
    if(M5.BtnC.wasPressed()){
      res1 = FP_M.fpm_deleteAllUser();
      
      CleanScreen();

      if(res1 == ACK_SUCCESS){
          M5.Lcd.println("Delete All User Successful");
      }
      else{
          M5.Lcd.println("Delete All User Failed");
      }
    }
    M5.update();
}
