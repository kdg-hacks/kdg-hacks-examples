# kdg-hacks-examples
KDG HACKS 2018向けのサンプルコード集

## `Wio LTE M1/NB1(BG96)` との対応づけ

作成したサンプルコードは、HWに内蔵されたLEDを利用したり、各種センサーを利用しています。

各種センサーには種類が存在し、センサーを接続するポートと、プログラム上で利用するピン番号が決まっています。

- Analog * 2箇所
- Digital * 2箇所
- I2C
- UART

※2箇所存在するものについては、どちらかに接続したサンプルとなっているので、プログラムの最初に定義されているピン番号を確認して接続してください。

![](https://github.com/kdg-hacks/kdg-hacks-examples/blob/images/hw.png)

## サンプルコード

### 内蔵LED

|製品名|製品説明|ディレクトリ|概要|参考URL|
|-----|-------|-------|----|------|
| 内蔵フルカラーLED | | [Hello-LED](Hello-LED) |内蔵フルカラーLEDをLチカする|[公式リファレンス](https://github.com/SeeedJP/Wiki/blob/master/Wio_cell_lib_for_Arduino/reference-ja.md#ledsetrgb)|

### 各種センサー

#### Analog

|製品名|製品説明|ディレクトリ|概要|参考URL|
|-----|-------|-------|----|------|
| GROVE-GSR| <details><summary>皮膚の電気伝導度を検出</summary><sub>睡眠の質のモニタリングなど、感情関連のプロジェクトを実現するのに最適です。<br>GSRは、Galvanic Skin Responseの略で、皮膚の電気伝導度を測定する方法です。<br>汗腺によって分泌される汗の量の変化などを測定すれば、うそ発見器も作成できるかもしれません。</sub></details> | [GSR-Monitor](https://github.com/kdg-hacks/kdg-hacks-examples/tree/master/GSR-Monitor) | TODO |[公式Wiki](http://wiki.seeed.cc/Grove-GSR_Sensor/)|

#### Digital

|製品名|製品説明|ディレクトリ|概要|参考URL|
|-----|-------|-------|----|------|
| GROVE-Button| | [Hello-Button](Hello-Button) |ボタンの状態を取得する|[公式Wiki](http://wiki.seeedstudio.com/Grove-Button/)|
| GROVE-Buzzer| | [Hello-Buzzer](Hello-Buzzer) |ブザーをON/OFFする|[公式Wiki](http://wiki.seeedstudio.com/Grove-Buzzer/)|
| GROVE-光| <details><summary>光量を計測</summary><sub>広範囲の光を感知し、電気信号を出力するアナログセンサモジュールです。<br>出力レンジは制御するボードのADコンバータに依存します（例えば、8 bit ADCなら0〜255を出力します）。</sub></details>| TODO | (TODO:きしだ)|[公式Wiki](http://wiki.seeed.cc/Grove-Light_Sensor/)|
| GROVE-ダスト| <details><summary>大気中の粒子状物質の濃度を測る</summary><sub>一定時間内のLowパルスの占有時間（Lo Pulse Occupancy time:LPOタイム）により、大気中の粒子状物質の濃度を測ることができます。LPOタイムは粒子状物質の濃度に比例します。このセンサは直径1マイクロメートル以上の粒子に反応します。クリーンルーム内のホコリを検知することも可能です。</sub></details>| [Hello-DustSensor](Hello-DustSensor) | 大気中の粒子状物質の濃度を測る | [公式Wiki](http://wiki.seeed.cc/Grove-Dust_Sensor/) <br>[使用例](http://www.howmuchsnow.com/arduino/airquality/grovedust/)|
| GROVE-磁気スイッチ| | [Hello-MagSW](https://github.com/kdg-hacks/kdg-hacks-examples/tree/master/Hello-MagSW) | TODO| [公式Wiki](http://wiki.seeed.cc/Grove-Magnetic_Switch/)|
| GROVE-デジタル温度・湿度| | [Hello-TempHumi](https://github.com/kdg-hacks/kdg-hacks-examples/tree/master/Hello-TempHumi) | TODO| [公式Wiki](http://wiki.seeed.cc/Grove-TemperatureAndHumidity_Sensor/)|
| GROVE-超音波距離| 非接触距離センサ | [Hello-Ultrasonic](https://github.com/kdg-hacks/kdg-hacks-examples/tree/master/Hello-Ultrasonic) | TODO| [公式Wiki](http://wiki.seeedstudio.com/Grove-Ultrasonic_Ranger/)|
| [保留]~~GROVE-テープLEDドライバー~~| <details><summary>テープLEDドライバ</summary><sub>・カスケード接続可能<br>・テープLEDは5m以下を推奨<br>・PWM出力<br>・256段階の輝度レベル</sub></details>| TODO | TODO| [公式Wiki](http://wiki.seeedstudio.com/Grove-LED_Strip_Driver/)|
| GROVE-PIRモーション| <details><summary>モーションセンサ</summary><sub>検出範囲内で動きがあると、SIGピンがHIGHになります。</sub></details>| [Hello-PirMotion](https://github.com/kdg-hacks/kdg-hacks-examples/tree/master/Hello-PirMotion) | 範囲内に人がいるかどうか検出する| [公式Wiki](http://wiki.seeed.cc/Grove-PIR_Motion_Sensor/)|
| GROVE-水| <details><summary>水センサ</summary><sub>出力ピンは1MΩ抵抗でプルアップされており、センサ端子に水滴が付くとGNDとショートして出力の電圧が下がる仕組みです。</sub></details>| [Hello-Water](https://github.com/kdg-hacks/kdg-hacks-examples/tree/master/Hello-Water) | 水滴がついているかどうかを取得する| [公式Wiki](http://wiki.seeed.cc/Grove-Water_Sensor/)|

#### I2C

|製品名|製品説明|ディレクトリ|概要|参考URL|
|-----|-------|-------|----|------|
| GROVE-I2Cカラー| <details><summary>環境光の色度や、物体の色を検出</summary><sub>TCS34725FNを搭載。<br>2行8列のフィルターされたフォトダイオードと16 bitのADコンバータを内蔵しています。<br>16個のフォトダイオードのうち4個は赤色フィルタ、4個は緑色フィルタ、4個は青色フィルタ、4個はフィルタなし（クリア）</sub></details>| [Hello-Color](https://github.com/kdg-hacks/kdg-hacks-examples/tree/master/Hello-Color) | TODO|[公式Wiki](http://wiki.seeed.cc/Grove-I2C_Color_Sensor/)|
| GROVE-I2Cタッチ|<details><summary> 静電容量タッチセンサ</summary> |[Hello-I2CTouch](https://github.com/kdg-hacks/kdg-hacks-examples/tree/master/Hello-Touch) |センサーを紙などで挟んで、何番のセンサーに触れたかを検知します。※導電性材料に直接触れてはいけません。3V-5V（5V推奨）| [公式Wiki](http://wiki.seeedstudio.com/Grove-I2C_Touch_Sensor/)|
| GROVE-I2C三軸加速度| | [Hello-3Axis](https://github.com/kdg-hacks/kdg-hacks-examples/tree/master/Hello-3Axis) | TODO| [公式Wiki](http://wiki.seeedstudio.com/Grove-3-Axis_Digital_Accelerometer-1.5g/)|
| GROVE-温湿度| <details><summary>高精度で使いやすい温度湿度センサ</summary><sub>SHT31センサは、相対湿度の誤差±2%以内の最高精度の湿度センサです。<br>温度計としても-40度や125度といった極端な状況でも使用可能で、±0.3度の高精度を保持します。</sub></details>| [Grove_SHT31_Temp_Humi_Sensor](https://github.com/kdg-hacks/Grove_SHT31_Temp_Humi_Sensor) | TODO| [公式Wiki](http://wiki.seeedstudio.com/Grove-TempAndHumi_Sensor-SHT31/)|
| 音声合成Box| <details><summary>高品質な音声合成デバイス</summary><sub>KDDI総合研究所製音声合成ソフトN2を搭載したBox型音声合成デバイス<br />今回は2種類のBoxを用意、それぞれ別の声質を出すようにしました。</sub></details>| [n2](https://github.com/kdg-hacks/kdg-hacks-examples/tree/master/n2) |2種サンプル：(1)テキストを設定して喋らせる、(2)MQTTプロトコルを利用し、受信したテキストを喋らせる| [KDDI総合研究所/N2](https://www.kddi-research.jp/products/n2.html)|

#### UART

|製品名|製品説明|ディレクトリ|概要|参考URL|
|-----|-------|-------|----|------|
| GROVE-シリアルカメラ| <details><summary>カメラ</summary><sub>ワイドアングルレンズが付属します。<br>ワイドアングルレンズは何かをモニタリングする時などに便利。</sub></details>| TODO | (TODO:きしだ)| [公式Wiki](http://wiki.seeedstudio.com/Grove-Serial_Camera_Kit/)|
| GROVE-GPS| | [Hello-GPS](https://github.com/kdg-hacks/kdg-hacks-examples/tree/master/Hello-GPS) | TODO| [公式Wiki](http://wiki.seeedstudio.com/Grove-GPS/)|
| GROVE-発話認識| <details><summary>特定の音声をコマンドとして認識</summary><sub>「Start」「Stop」「Play music」など特定の音声コマンドを認識できます（全22種。[詳しくはwikiをご覧ください](http://wiki.seeed.cc/Grove-Speech_Recognizer/)）。<br>コマンドを認識すると、接続されたスピーカーから該当コマンドをリピートし、規定の値を返します。この値を通して、モーターや音楽プレーヤーなど他のデバイスを制御することが可能です。<br>ボードには、Nuvoton ISD9160（SoC）、マイク、SPIフラッシュ、1 x GROVEコネクタ、1 x スピーカコネクタを搭載。ARM Cortex-M0ベースのNuvoton ISD9160は、費用対効果の高い、強力な音声制御アプリケーション用ソリューションを提供します。内蔵マイクは無指向性なので、発話者の話している方向にかかわらず、安定した信号を記録できます。<br>高精度の認識率と非常に低い誤トリガー率を持ち、音声を使用したインタラクティブなデバイスなど、IoTアプリケーションの中でも最も興味深いものづくりの一つに貢献します。</sub></details>| [Hello-SpeechRecognizer](https://github.com/kdg-hacks/kdg-hacks-examples/tree/master/Hello-SpeechRecognizer) | 事前登録済みの音声の中から発話した音声を認識する| [公式Wiki](http://wiki.seeed.cc/Grove-Speech_Recognizer/)|

### 外部連携（SORACOMなど外部と連携するサンプル）

|製品名|製品説明|ディレクトリ|概要|参考URL|
|-----|-------|-------|----|------|
| SORACOM metadata| | [Hello-SORACOM-metadata](Hello-SORACOM-metadata) |SORACOM メタサービスデータの取得の仕方|[公式サイト](https://dev.soracom.io/jp/start/metadata/)|
| SORACOM Beam(IFTTT)| | [Hello-SORACOM-beam](Hello-SORACOM-beam) |SORACOM Beamを使って、HTTP PostでIFTTTに接続する（片方向）|[公式サイト](https://dev.soracom.io/jp/start/beam/)|
| SORACOM Beam(AWS IoT Core)| | [Hello-Mqtt](Hello-Mqtt) |SORACOM Beamを使って、AWS IoT CoreにMQTTで接続する（双方向）|[公式サイト](https://dev.soracom.io/jp/docs/aws_iot_guide_console/)|
| SORACOM Funnel(AWS IoT Core)| | [Hello-SORACOM-funnel](Hello-SORACOM-funnel) |SORACOM Funnelを使って、AWS IoT Coreに接続する（片方向）|[公式サイト](https://dev.soracom.io/jp/start/funnel_aws_iot/)|
| 赤外線リモコン(テレビ操作)| <details><summary>赤外線信号でテレビを操作</summary><sub>赤外線信号を送信して、テレビの電源ON/OFF等の制御を実施します。</sub></details> | [Hello-IrRemocon-tv](Hello-IrRemocon-tv) | テレビの電源ON/OFFを操作する赤外線信号を送信 |[公式サイト](https://www.au.com/auhome/device/ura01a/)|
| 赤外線リモコン(エアコン操作)| <details><summary>赤外線信号でエアコンを操作</summary><sub>赤外線信号を送信して、エアコンの冷房ON/暖房ON/OFF等の制御を実施します。</sub></details> | [Hello-IrRemocon-aircon](Hello-IrRemocon-aircon) | エアコンの暖房ON->冷房ON->電源OFFを操作する赤外線信号を送信 |[公式サイト](https://www.au.com/auhome/device/ura01a/)|
| 赤外線リモコン(照明操作)| <details><summary>赤外線信号で照明を操作</summary><sub>赤外線信号を送信して、照明の電源ON/OFF等の制御を実施します。</sub></details> | [Hello-IrRemocon-light](Hello-IrRemocon-light) | 照明の電源ON->電源OFF操作する赤外線信号を送信 |[公式サイト](https://www.au.com/auhome/device/ura01a/)|
| 赤外線リモコン(扇風機操作)| <details><summary>赤外線信号で扇風機を操作</summary><sub>赤外線信号を送信して、扇風機の電源ON/OFF等の制御を実施します。</sub></details> | [Hello-IrRemocon-fan](Hello-IrRemocon-fan) | 扇風機の電源ON->風量変更->電源OFF操作する赤外線信号を送信 |[公式サイト](https://www.au.com/auhome/device/ura01a/)|
| SORACOM LTE-M Button | <details><summary>AWS IoT 1-Clickのサポート対象デバイス</summary><sub>AWS IoT 1-Click のマネジメントコンソール上で設定することにより Eメールや SMSの送信などの簡単なアクションを実行できるほか、AWS Lambda と連携することでクリック時に JavaScript、Java、Python、C# などの言語で記述した独自のビジネスロジックの実行が可能です。</sub></details> | [Hello-SORACOM-lte-m-button](Hello-SORACOM-lte-m-button) | (`Wio LTE M1/NB1(BG96)` とは連携しません)<br> SORACOM LTE-M Button押下にて、イベント内容をSlackへ通知します |[公式サイト](https://soracom.jp/products/gadgets/aws_button/)|

