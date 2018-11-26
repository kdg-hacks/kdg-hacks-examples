# kdg-hacks-examples
KDG HACKS 2018向けのサンプルコード集

|製品名|製品説明|ディレクトリ|概要|参考URL|
|-----|-------|-------|----|------|
| 内蔵フルカラーLED | | [Hello-LED](Hello-LED) |内蔵フルカラーLEDをLチカする|[公式リファレンス](https://github.com/SeeedJP/Wiki/blob/master/Wio_cell_lib_for_Arduino/reference-ja.md#ledsetrgb)|
| GROVE-Button| | [Hello-Button](Hello-Button) |ボタンの状態を取得する|[公式Wiki](http://wiki.seeedstudio.com/Grove-Button/)|
| GROVE-Buzzer| | [Hello-Buzzer](Hello-Buzzer) |ブザーをON/OFFする|[公式Wiki](http://wiki.seeedstudio.com/Grove-Buzzer/)|
| GROVE-GSR| <details><summary>皮膚の電気伝導度を検出</summary><sub>睡眠の質のモニタリングなど、感情関連のプロジェクトを実現するのに最適です。<br>GSRは、Galvanic Skin Responseの略で、皮膚の電気伝導度を測定する方法です。<br>汗腺によって分泌される汗の量の変化などを測定すれば、うそ発見器も作成できるかもしれません。</sub></details> | [GSR-Monitor](https://github.com/kdg-hacks/kdg-hacks-examples/tree/master/GSR-Monitor) | TODO |[公式Wiki](http://wiki.seeed.cc/Grove-GSR_Sensor/)|
| GROVE-I2Cカラー| <details><summary>環境光の色度や、物体の色を検出</summary><sub>TCS34725FNを搭載。<br>2行8列のフィルターされたフォトダイオードと16 bitのADコンバータを内蔵しています。<br>16個のフォトダイオードのうち4個は赤色フィルタ、4個は緑色フィルタ、4個は青色フィルタ、4個はフィルタなし（クリア）</sub></details>| TODO |TODO|[公式Wiki](http://wiki.seeed.cc/Grove-I2C_Color_Sensor/)|
| GROVE-光| <details><summary>光量を計測</summary><sub>広範囲の光を感知し、電気信号を出力するアナログセンサモジュールです。<br>出力レンジは制御するボードのADコンバータに依存します（例えば、8 bit ADCなら0〜255を出力します）。</sub></details>| TODO | TODO|[公式Wiki](http://wiki.seeed.cc/Grove-Light_Sensor/)|
| GROVE-ダスト| <details><summary>大気中の粒子状物質の濃度を測る</summary><sub>一定時間内のLowパルスの占有時間（Lo Pulse Occupancy time:LPOタイム）により、大気中の粒子状物質の濃度を測ることができます。LPOタイムは粒子状物質の濃度に比例します。このセンサは直径1マイクロメートル以上の粒子に反応します。クリーンルーム内のホコリを検知することも可能です。</sub></details>| TODO | TODO| [公式Wiki](http://wiki.seeed.cc/Grove-Dust_Sensor/) <br>[使用例](http://www.howmuchsnow.com/arduino/airquality/grovedust/)|
| GROVE-シリアルカメラ| <details><summary>カメラ</summary><sub>ワイドアングルレンズが付属します。<br>ワイドアングルレンズは何かをモニタリングする時などに便利。</sub></details>| TODO | TODO| [公式Wiki](http://wiki.seeedstudio.com/Grove-Serial_Camera_Kit/)|
| GROVE-PIRモーション| | [Hello-PirMotion](https://github.com/kdg-hacks/kdg-hacks-examples/tree/master/Hello-PirMotion) | TODO| [公式Wiki](http://wiki.seeed.cc/Grove-PIR_Motion_Sensor/)|
| GROVE-I2Cタッチ| | TODO | TODO| [公式Wiki](http://wiki.seeedstudio.com/Grove-I2C_Touch_Sensor/)|
| GROVE-水| <details><summary>水センサ</summary><sub>出力ピンは1MΩ抵抗でプルアップされており、センサ端子に水滴が付くとGNDとショートして出力の電圧が下がる仕組みです。</sub></details>| [Hello-Water](https://github.com/kdg-hacks/kdg-hacks-examples/tree/master/Hello-Water) | TODO| [公式Wiki](http://wiki.seeed.cc/Grove-Water_Sensor/)|
| GROVE-温湿度| <details><summary>高精度で使いやすい温度湿度センサ</summary><sub>SHT31センサは、相対湿度の誤差±2%以内の最高精度の湿度センサです。<br>温度計としても-40度や125度といった極端な状況でも使用可能で、±0.3度の高精度を保持します。</sub></details>| TODO | TODO| [公式Wiki](http://wiki.seeedstudio.com/Grove-TempAndHumi_Sensor-SHT31/)|
| GROVE-I2C三軸加速度| | [Hello-3Axis](https://github.com/kdg-hacks/kdg-hacks-examples/tree/master/Hello-3Axis) | TODO| [公式Wiki](http://wiki.seeedstudio.com/Grove-3-Axis_Digital_Accelerometer-1.5g/)|
| GROVE-磁気スイッチ| | [Hello-MagSW](https://github.com/kdg-hacks/kdg-hacks-examples/tree/master/Hello-MagSW) | TODO| [公式Wiki](http://wiki.seeed.cc/Grove-Magnetic_Switch/)|
| GROVE-デジタル温度・湿度| | [Hello-TempHumi](https://github.com/kdg-hacks/kdg-hacks-examples/tree/master/Hello-TempHumi) | TODO| [公式Wiki](http://wiki.seeed.cc/Grove-TemperatureAndHumidity_Sensor/)|
| GROVE-GPS| | [Hello-GPS](https://github.com/kdg-hacks/kdg-hacks-examples/tree/master/Hello-GPS) | TODO| [公式Wiki](http://wiki.seeedstudio.com/Grove-GPS/)|
| GROVE-超音波距離| 非接触距離センサ | [Hello-Ultrasonic](https://github.com/kdg-hacks/kdg-hacks-examples/tree/master/Hello-Ultrasonic) | TODO| [公式Wiki](http://wiki.seeedstudio.com/Grove-Ultrasonic_Ranger/)|
| GROVE-発話認識| <details><summary>特定の音声をコマンドとして認識</summary><sub>「Start」「Stop」「Play music」など特定の音声コマンドを認識できます（全22種。[詳しくはwikiをご覧ください](http://wiki.seeed.cc/Grove-Speech_Recognizer/)）。<br>コマンドを認識すると、接続されたスピーカーから該当コマンドをリピートし、規定の値を返します。この値を通して、モーターや音楽プレーヤーなど他のデバイスを制御することが可能です。<br>ボードには、Nuvoton ISD9160（SoC）、マイク、SPIフラッシュ、1 x GROVEコネクタ、1 x スピーカコネクタを搭載。ARM Cortex-M0ベースのNuvoton ISD9160は、費用対効果の高い、強力な音声制御アプリケーション用ソリューションを提供します。内蔵マイクは無指向性なので、発話者の話している方向にかかわらず、安定した信号を記録できます。<br>高精度の認識率と非常に低い誤トリガー率を持ち、音声を使用したインタラクティブなデバイスなど、IoTアプリケーションの中でも最も興味深いものづくりの一つに貢献します。</sub></details>| TODO | TODO| [公式Wiki](http://wiki.seeed.cc/Grove-Speech_Recognizer/)|
| GROVE-テープLEDドライバー| <details><summary>テープLEDドライバ</summary><sub>・カスケード接続可能<br>・テープLEDは5m以下を推奨<br>・PWM出力<br>・256段階の輝度レベル</sub></details>| TODO | TODO| [公式Wiki](http://wiki.seeedstudio.com/Grove-LED_Strip_Driver/)|
| SORACOM Beam(IFTTT)| | [Hello-SORACOM-beam](Hello-SORACOM-beam) |SORACOM Beamを使って、HTTP PostでIFTTTに繋ぐ|[TODO](site)|
| SORACOM Beam(AWS IoT Core| | [Hello-Mqtt](Hello-Mqtt) |SORACOM Beamを使って、AWS IoT CoreにMQTTで繋ぐ|[TODO](site)|
| xxxリモコン| | [Hello-xxxxx](xxxx) |xxxを操作するリモコン|[公式サイト](site)|
| xxxリモコン| | [Hello-xxxxx](xxxx) |xxxを操作するリモコン|[公式サイト](site)|
| xxxリモコン| | [Hello-xxxxx](xxxx) |xxxを操作するリモコン|[公式サイト](site)|
| xxxリモコン| | [Hello-xxxxx](xxxx) |xxxを操作するリモコン|[公式サイト](site)|
