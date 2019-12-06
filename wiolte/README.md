# kdg-hacks-examples
KDG HACKS 向けのサンプルコード集

## 開発環境準備
* デバイスの[セットアップ](https://github.com/SeeedJP/Wiki/blob/master/Wio_cell_lib_for_Arduino/setup-ja.md)


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
| 内蔵フルカラーLED | <details><summary>`Wio LTE M1/NB1(BG96)`上のフルカラーLED </summary><sub>RGB各256段階の組合せで最大1677万色の表示が可能です。</sub></details> | [Hello-LED](Hello-LED) |１秒毎に、内蔵LEDを赤色にON/OFFにする|[公式リファレンス](https://github.com/SeeedJP/Wiki/blob/master/Wio_cell_lib_for_Arduino/reference-ja.md#ledsetrgb)|

### 各種センサー

#### Analog

|製品名|製品説明|ディレクトリ|概要|参考URL|
|-----|-------|-------|----|------|
| GROVE-GSR| <details><summary>皮膚の電気伝導度を検出</summary><sub>睡眠の質のモニタリングなど、感情関連のプロジェクトを実現するのに最適です。<br>GSRは、Galvanic Skin Responseの略で、皮膚の電気伝導度を測定する方法です。<br>汗腺によって分泌される汗の量の変化などを測定すれば、うそ発見器も作成できるかもしれません。</sub></details> | [GSR-Monitor](GSR-Monitor) | 5ミリ秒毎に10回取得した値の平均値を取得し、シリアルに出力します。機器に付属している可変抵抗をプラスドライバーで回すことで出力される値が大きく変更します。 |[公式Wiki](http://wiki.seeed.cc/Grove-GSR_Sensor/)|
| GROVE-光| <details><summary>光量を計測</summary><sub>広範囲の光を感知し、電気信号を出力するアナログセンサモジュールです。<br>出力レンジは制御するボードのADコンバータに依存します（例えば、8 bit ADCなら0〜255を出力します）。</sub></details>| [Hello-LightSensor](Hello-LightSensor) | 1秒毎に光量を取得し、シリアルに出力します。光量は0(暗い)〜4095(明るい)までの値で取得できます。 |[公式Wiki](http://wiki.seeed.cc/Grove-Light_Sensor/)|

#### Digital

|製品名|製品説明|ディレクトリ|概要|参考URL|
|-----|-------|-------|----|------|
| GROVE-Button| <details><summary> ボタンスイッチ </summary><sub>ボタン押下(ON)、非押下(OFF)の2種類の状態取得が可能です。ボタンを起因にサービスやセンサーを動作させる等に活用できます。</sub></details> | [Hello-Button](Hello-Button) |１秒毎に、ボタンの状態を取得する|[公式Wiki](http://wiki.seeedstudio.com/Grove-Button/)|
| GROVE-Buzzer| <details><summary> ブザー </summary><sub>音を鳴らすことができます。センサーの値等を判定して音を鳴らして通知する等に活用できます。 </sub></details> | [Hello-Buzzer](Hello-Buzzer) |100ms間をブザーをONにして、1000ms間ブザーをOFFすることを繰り返す|[公式Wiki](http://wiki.seeedstudio.com/Grove-Buzzer/)|
| GROVE-ダスト| <details><summary>大気中の粒子状物質の濃度を測る</summary><sub>一定時間内のLowパルスの占有時間（Lo Pulse Occupancy time:LPOタイム）により、大気中の粒子状物質の濃度を測ることができます。LPOタイムは粒子状物質の濃度に比例します。このセンサは直径1マイクロメートル以上の粒子に反応します。クリーンルーム内のホコリを検知することも可能です。</sub></details>| [Hello-DustSensor](Hello-DustSensor) | ３０秒間測定した、大気中の粒子状物質の濃度を出力する。安定した値を取得するには３分間以上動作させること | [公式Wiki](http://wiki.seeed.cc/Grove-Dust_Sensor/) <br>[使用例](http://www.howmuchsnow.com/arduino/airquality/grovedust/)|
| GROVE-磁気スイッチ| <details><summary> 磁石や磁気をもつものが近づいたことを検知 </summary><sub>磁石や磁気をもつものが近づいたことを検知して、近づくとスイッチがONになります。 </sub></details> | [Hello-MagSW](Hello-MagSW) | １秒毎に、磁石が近づいているか？近づいていないか？を検知する| [公式Wiki](http://wiki.seeed.cc/Grove-Magnetic_Switch/)|
| GROVE-デジタル温度・湿度| <details><summary> 温度や湿度を測定 </summary><sub>付近の温度や湿度を測定し結果を相対湿度および絶対温度の値を取得できます。 </sub></details> | [Hello-TempHumi](Hello-TempHumi) | DHT11というセンサーから、２秒毎に、湿度と温度を取得する| [公式Wiki](http://wiki.seeed.cc/Grove-TemperatureAndHumidity_Sensor/)|
| GROVE-超音波距離| <details><summary> 超音波で距離を測定 </summary><sub>超音波(40KHz)を利用して、付近の物体への距離を計測し、値を取得できます。 </sub></details> | [Hello-Ultrasonic](Hello-Ultrasonic) | 200ms毎に、センサーからの距離を取得する。取得可能な範囲は2-350cmで、取得単位は、cm| [公式Wiki](http://wiki.seeedstudio.com/Grove-Ultrasonic_Ranger/)|
| [保留]~~GROVE-テープLEDドライバー~~| <details><summary>テープLEDドライバ</summary><sub>・カスケード接続可能<br>・テープLEDは5m以下を推奨<br>・PWM出力<br>・256段階の輝度レベル</sub></details>| TODO | TODO| [公式Wiki](http://wiki.seeedstudio.com/Grove-LED_Strip_Driver/)|
| GROVE-PIRモーション| <details><summary>モーションセンサ</summary><sub>検出範囲内で動きがあると、SIGピンがHIGHになります。</sub></details>| [Hello-PirMotion](Hello-PirMotion) | 範囲内に人がいるかどうか検出する| [公式Wiki](http://wiki.seeed.cc/Grove-PIR_Motion_Sensor/)|
| GROVE-水| <details><summary>水センサ</summary><sub>出力ピンは1MΩ抵抗でプルアップされており、センサ端子に水滴が付くとGNDとショートして出力の電圧が下がる仕組みです。</sub></details>| [Hello-Water](Hello-Water) | 水滴がついているかどうかを取得する| [公式Wiki](http://wiki.seeed.cc/Grove-Water_Sensor/)|

#### I2C

|製品名|製品説明|ディレクトリ|概要|参考URL|
|-----|-------|-------|----|------|
| GROVE-I2Cカラー| <details><summary>環境光の色度や、物体の色を検出</summary><sub>TCS34725FNを搭載。<br>2行8列のフィルターされたフォトダイオードと16 bitのADコンバータを内蔵しています。<br>16個のフォトダイオードのうち4個は赤色フィルタ、4個は緑色フィルタ、4個は青色フィルタ、4個はフィルタなし（クリア）</sub></details>| [Hello-Color](Hello-Color) | センサーを近づけた対象の色情報(RGBA)を0 ～ 65,535の間で取得します。 |[公式Wiki](http://wiki.seeed.cc/Grove-I2C_Color_Sensor/)|
| GROVE-I2Cタッチ|<details><summary> 静電容量タッチセンサ</summary> |[Hello-I2CTouch](Hello-Touch) |センサーを紙などで挟んで、何番のセンサーに触れたかを検知します。※導電性材料に直接触れてはいけません。3V-5V（5V推奨）| [公式Wiki](http://wiki.seeedstudio.com/Grove-I2C_Touch_Sensor/)|
| GROVE-I2C三軸加速度| <details><summary>加速度による方向、ジェスチャ、動きを検出</summary><sub>加速度により、X,Y,Zの3軸の動きを検出し、値を取得できます。</sub></details> | [Hello-3Axis](Hello-3Axis) | 200ms毎に、X軸、Y軸、Z軸の加速度を取得する。取得可能な数値は、最大±1.5gまで| [公式Wiki](http://wiki.seeedstudio.com/Grove-3-Axis_Digital_Accelerometer-1.5g/)|
| GROVE-温湿度| <details><summary>高精度で使いやすい温度湿度センサ</summary><sub>SHT31センサは、相対湿度の誤差±2%以内の最高精度の湿度センサです。<br>温度計としても-40度や125度といった極端な状況でも使用可能で、±0.3度の高精度を保持します。</sub></details>| [Hello-SHT31](Hello-SHT31) | 1秒間隔で温度と湿度を取得し、シリアルに出力します | [公式Wiki](http://wiki.seeedstudio.com/Grove-TempAndHumi_Sensor-SHT31/)|

#### UART

|製品名|製品説明|ディレクトリ|概要|参考URL|
|-----|-------|-------|----|------|
| GROVE-シリアルカメラ| <details><summary>カメラ</summary><sub>ワイドアングルレンズが付属します。<br>ワイドアングルレンズは何かをモニタリングする時などに便利。</sub></details>|[Hello-CAMERA](Hello-CAMERA) | シリアルカメラで写真を撮影し、Base64の文字列化を行う。| [公式Wiki](http://wiki.seeedstudio.com/Grove-Serial_Camera_Kit/)|
| GROVE-GPS| <details><summary> GPSによる位置情報を検出 </summary><sub>NMEAおよびu-blox 6プロトコルのGPS電波を利用して、現在の場所を検出し、位置情報を取得できます。 </sub></details> | [Hello-GPS](Hello-GPS) | GPSセンサーから日時、緯度、経度を取得する| [公式Wiki](http://wiki.seeedstudio.com/Grove-GPS/)|
| GROVE-発話認識| <details><summary>特定の音声をコマンドとして認識</summary><sub>「Start」「Stop」「Play music」など特定の音声コマンドを認識できます（全22種。[詳しくはwikiをご覧ください](http://wiki.seeed.cc/Grove-Speech_Recognizer/)）。<br>コマンドを認識すると、接続されたスピーカーから該当コマンドをリピートし、規定の値を返します。この値を通して、モーターや音楽プレーヤーなど他のデバイスを制御することが可能です。<br>ボードには、Nuvoton ISD9160（SoC）、マイク、SPIフラッシュ、1 x GROVEコネクタ、1 x スピーカコネクタを搭載。ARM Cortex-M0ベースのNuvoton ISD9160は、費用対効果の高い、強力な音声制御アプリケーション用ソリューションを提供します。内蔵マイクは無指向性なので、発話者の話している方向にかかわらず、安定した信号を記録できます。<br>高精度の認識率と非常に低い誤トリガー率を持ち、音声を使用したインタラクティブなデバイスなど、IoTアプリケーションの中でも最も興味深いものづくりの一つに貢献します。</sub></details>| [Hello-SpeechRecognizer](Hello-SpeechRecognizer) | 事前登録済みの音声の中から発話した音声を認識する| [公式Wiki](http://wiki.seeed.cc/Grove-Speech_Recognizer/)|

### 外部連携（SORACOMなど外部と連携するサンプル）

|製品名|製品説明|ディレクトリ|概要|参考URL|
|-----|-------|-------|----|------|
| HTTP GETリクエスト| <details><summary> HTTP GETプロトコルで、Webサーバからデータを取得する </summary><sub>SSL通信は出来ない場合があるので、http通信のみが望ましい</sub></details> | [Hello-HttpGet](Hello-HttpGet) |１分毎に、IPアドレスを取得することができるWebサービスにアクセスして、IPアドレスをJSON形式で取得する|[公式サイト](https://github.com/SeeedJP/Wiki/blob/master/Wio_cell_lib_for_Arduino/reference-ja.md#httpget)|
| SORACOM Harvest| <details><summary>  SORACOM Harvest(以下、Harvest) は、IoTデバイスからのデータを収集、蓄積するサービスです。 </summary><sub> 保存されたデータには受信時刻や SIM の ID が自動的に付与され、「SORACOM」のユーザーコンソール内で、グラフ化して閲覧したり、API を通じて取得することができます。</sub></details> | [Hello-SORACOM-harvest](Hello-SORACOM-harvest) |１秒ごとに、カウントアップした数値をHarvestに送る|[公式サイト](https://dev.soracom.io/jp/start/harvest/)|
| SORACOM metadata| <details><summary> SORACOM Air のメタデータ情報の取得および更新 </summary><sub> SORACOM Airのデバイスが利用しているSIM等の情報を取得および更新できます。 </sub></details> | [Hello-SORACOM-metadata](Hello-SORACOM-metadata) |２分毎に、メタサービスからデータを取得する|[公式サイト](https://dev.soracom.io/jp/start/metadata/)|
| SORACOM Beam(IFTTT)| <details><summary>  デバイスが利用する暗号化等の高負荷処理や接続先の設定を管理 </summary><sub> デバイスが利用する外部サービスへの接続先管理、プロトコル変換、暗号化処理等を実施できます。例えばHTTPをHTTPSプロトコルに変換し外部サービスと連携するなどが可能です。 </sub></details> | [Hello-SORACOM-beam](Hello-SORACOM-beam) |２分毎に、SORACOM Beamを使って、HTTP PostでIFTTTにデータを送る|[公式サイト](https://dev.soracom.io/jp/start/beam/)|
| SORACOM Beam(AWS IoT Core)| <details><summary>  デバイスが利用する暗号化等の高負荷処理や接続先の設定を管理 </summary><sub> デバイスが利用する外部サービスへの接続先管理、プロトコル変換、暗号化処理等を実施できます。例えばHTTPをHTTPSプロトコルに変換し外部サービスと連携するなどが可能です。 </sub></details> | [Hello-Mqtt](Hello-Mqtt) |２分毎に、SORACOM Beamを使って、AWS IoT CoreにMQTTで送信する。|[公式サイト](https://dev.soracom.io/jp/docs/aws_iot_guide_console/)|
| SORACOM Funnel(AWS IoT Core)| <details><summary> デバイスから特定のクラウドサービスへデータ等を直接転送するアダプター </summary><sub> デバイスから以下のクラウドサービスへのアダプターを提供します。<br>・AWS IoT<br>・Amazon Kinesis<br>・Amazon Kinesis Firehose<br>・Microsoft Azure Event Hubs<br>・Google Cloud Pub/Sub<br>・Amazon Kinesis Video Streams </sub></details> | [Hello-SORACOM-funnel](Hello-SORACOM-funnel) |２分毎に、SORACOM Funnelを使って、AWS IoT Coreにデータを送信する|[公式サイト](https://dev.soracom.io/jp/start/funnel_aws_iot/)|
| 赤外線リモコン(テレビ操作)| <details><summary>赤外線信号でテレビを操作</summary><sub>赤外線信号を送信して、テレビの電源ON/OFF等の制御を実施します。</sub></details> | [Hello-IrRemocon-tv](Hello-IrRemocon-tv) | テレビの電源ON/OFFを操作する赤外線信号を送信 |[公式サイト](https://www.au.com/auhome/device/ura01a/)|
| 赤外線リモコン(エアコン操作)| <details><summary>赤外線信号でエアコンを操作</summary><sub>赤外線信号を送信して、エアコンの冷房ON/暖房ON/OFF等の制御を実施します。</sub></details> | [Hello-IrRemocon-aircon](Hello-IrRemocon-aircon) | エアコンの暖房ON->冷房ON->電源OFFを操作する赤外線信号を送信 |[公式サイト](https://www.au.com/auhome/device/ura01a/)|
| 赤外線リモコン(照明操作)| <details><summary>赤外線信号で照明を操作</summary><sub>赤外線信号を送信して、照明の電源ON/OFF等の制御を実施します。</sub></details> | [Hello-IrRemocon-light](Hello-IrRemocon-light) | 照明の電源ON->電源OFF操作する赤外線信号を送信 |[公式サイト](https://www.au.com/auhome/device/ura01a/)|
| 赤外線リモコン(扇風機操作)| <details><summary>赤外線信号で扇風機を操作</summary><sub>赤外線信号を送信して、扇風機の電源ON/OFF等の制御を実施します。</sub></details> | [Hello-IrRemocon-fan](Hello-IrRemocon-fan) | 扇風機の電源ON->風量変更->電源OFF操作する赤外線信号を送信 |[公式サイト](https://www.au.com/auhome/device/ura01a/)|
| SORACOM LTE-M Button | <details><summary>AWS IoT 1-Clickのサポート対象デバイス</summary><sub>AWS IoT 1-Click のマネジメントコンソール上で設定することにより Eメールや SMSの送信などの簡単なアクションを実行できるほか、AWS Lambda と連携することでクリック時に JavaScript、Java、Python、C# などの言語で記述した独自のビジネスロジックの実行が可能です。</sub></details> | [Hello-SORACOM-lte-m-button](Hello-SORACOM-lte-m-button) | (`Wio LTE M1/NB1(BG96)` とは連携しません)<br> SORACOM LTE-M Button押下にて、イベント内容をSlackへ通知します |[公式サイト](https://soracom.jp/products/gadgets/aws_button/)|
| SORACOM LTE-M Button Plus | <details><summary>ボタンおよび接点入力を備えたデバイス</summary><sub>クリック情報をSORACOM Harvestで可視化したり、SORACOM Beamでサーバーに転送し、AWSサービスと連携することで、JavaScript、Java、Python、C# などの言語で記述した独自のビジネスロジックの実行が可能です。</sub></details> | [Hello-SORACOM-lte-m-button-plus](Hello-SORACOM-lte-m-button-plus) | (`Wio LTE M1/NB1(BG96)` とは連携しません)<br> Buttonクリック、接点入力により、クリックイベントを送信します |[公式サイト](https://soracom.jp/products/gadgets/button_plus/)|
| MODEMパラメータ | <details><summary>SIMの情報を取得する</summary><sub>IMEI,IMSIを取得する</sub></details> | [LTE-Param](LTE-Param) | IMEI,IMSIを取得する|[公式サイト](https://github.com/SeeedJP/Wiki/blob/master/Wio_cell_lib_for_Arduino/reference-ja.md#getimei)|
