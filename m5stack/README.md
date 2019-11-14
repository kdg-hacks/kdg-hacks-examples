# M5Stack FIRE
KDG HACKS向けの `M5Stack Fire` のサンプルコード集

## M5Stack 概要
M5Stackはモジュール積み重ねるタイプの開発デバイスです。
M5Stackの名前はModuleのM、5x5cmサイズの5、積み重ねるを意味するStackからきています。

M5Stackは、開発の際の煩わしさやストレスを軽減し、あなたがあなた自身の新しい発明やアイデアを具現化することに集中出来るように設計されています。M5Stackはいくつかのセンサー、Wi-Fi、Bluetooth、スクリーン、電源を自身に備えており、従来のブレッドボードでの煩雑な配線作業を行わなくても、拡張モジュールを積み重ねたり、Groveコネクタを介して拡張ユニットを簡単に接続することが可能です。

M5Stack Coreモジュールは ESP32 チップをベースに開発されています。

[参考](https://github.com/m5stack/m5-docs)

## 環境構築手順
各OSごとの[手順](https://docs.m5stack.com/#/ja/quick_start/m5core/m5stack_core_quick_start)に従い、開発環境を整えてください。

## サンプルコード
KDGHACKS向けに用意したセンサー、API等のサンプルコードです。

各種センサーには種類が存在し、センサーを接続するポートが決まっています。
センサーを利用する際には、接続するポートを確認してください。

<img src="./images/m5_fire_06.png" width="640">

### M5Stack組み込みセンサー

|製品名|製品説明|ディレクトリ|概要|参考URL|
|-----|-------|:-------:|:----:|------|
| ボタン x 3 | M5Stack上部の3つのボタン | - | 各ボタンに対応したクリックイベントを取得できます | [公式サンプル](https://github.com/m5stack/M5Stack/tree/master/examples/Basics/Button) |
| 液晶ディスプレイ | M5Stack上部のLCD | - | ディスプレイに文字やグラフィックを表示できます | [公式サンプル](https://github.com/m5stack/M5Stack/tree/master/examples/Basics/Display) |
| RGBバー | M5Stack側面のRGB LED | - | TODO | TODO |

### Analog/Digital (PORT B)
|製品名|製品説明|ディレクトリ|概要|参考URL|
|-----|-------|:-------:|:----:|------|
| UNIT BUTTON | ボタン | - | TODO | [公式Docs](https://docs.m5stack.com/#/en/unit/button) |
| UNIT Dual-BUTTON | ボタン x 2 | - | TODO | [公式Docs](https://docs.m5stack.com/#/en/unit/dual_button) |
| UNIT PIR | モーションセンサー | - | TODO | [公式Docs](https://docs.m5stack.com/#/en/unit/pir) |
| UNIT IR | 赤外線送受信センサー | - | TODO | [公式Docs](https://docs.m5stack.com/#/en/unit/ir) || UNIT LIGHT | 光センサー | - | TODO | [公式Docs](https://docs.m5stack.com/#/en/unit/light) |
| Grove - Water Sensor | 水検知センサー | [Hello-WaterSensor](https://github.com/kdg-hacks/kdg-hacks-examples/tree/master/m5stack/Hello-WaterSensor) | センサーが水に浸かっているかどうかを検知できます | [公式Docs](http://wiki.seeedstudio.com/Grove-Water_Sensor) |

### I2C (PORT A)
|製品名|製品説明|ディレクトリ|概要|参考URL|
|-----|-------|:-------:|:----:|------|
| UNIT JOYSTICK | ジョイスティック | - | TODO | [公式Docs](https://docs.m5stack.com/#/en/unit/joystick) |
| UNIT THERMAL | サーモセンサー | - | TODO | [公式Docs](https://docs.m5stack.com/#/en/unit/thermal) |
| UNIT ENV | 温湿度センサー | - | TODO | [公式Docs](https://docs.m5stack.com/#/en/unit/env) |
| UNIT TOF | 距離センサー | - | TODO | [公式Docs](https://docs.m5stack.com/#/en/unit/tof) |
| UNIT HEART | 心拍センサー | - | TODO | [公式Docs](https://docs.m5stack.com/#/en/unit/heart) |
| UNIT COLOR | 色センサー | - | TODO | [公式Docs](https://docs.m5stack.com/#/en/unit/color) |
| UNIT MUSIC | Makey Makey | - | TODO | [公式Docs](https://docs.m5stack.com/#/en/unit/makey) |
| GROVE-温湿度| <details><summary>高精度で使いやすい温度湿度センサ</summary><sub>SHT31センサは、相対湿度の誤差±2%以内の最高精度の湿度センサです。<br>温度計としても-40度や125度といった極端な状況でも使用可能で、±0.3度の高精度を保持します。</sub></details>| [Hello-SHT31](Hello-SHT31) | 1秒間隔で温度と湿度を取得し、シリアルに出力します | [公式Wiki](http://wiki.seeedstudio.com/Grove-TempAndHumi_Sensor-SHT31/)|
| GROVE-温湿度 | デジタル温度・湿度センサ(DHT11) |  [Hello-DHT11](Hello-DHT11)|1秒間隔で温度と湿度を取得し、シリアルに出力します| [公式Wiki](http://wiki.seeedstudio.com/Grove-TemperatureAndHumidity_Sensor/)
| GROVE-Buzzer| <details><summary> ブザー </summary><sub>音を鳴らすことができます。センサーの値等を判定して音を鳴らして通知する等に活用できます。 </sub></details> | [Hello-Buzzer](Hello-Buzzer) |100ms間をブザーをONにして、1000ms間ブザーをOFFすることを繰り返す|[公式Wiki](http://wiki.seeedstudio.com/Grove-Buzzer/)|
v

### UART (PORT C)
|製品名|製品説明|ディレクトリ|概要|参考URL|
|-----|-------|:-------:|:----:|------|
| UNIT FINGER | 指紋センサー | - | TODO | [公式Docs](https://docs.m5stack.com/#/en/unit/finger) |
| UNIT GPS | GPSセンサー | - | TODO | [公式Docs](https://docs.m5stack.com/#/en/unit/gps) |

### Module
|製品名|製品説明|ディレクトリ|概要|参考URL|
|-----|-------|:-------:|:----:|------|
| MODULE PLUS | 指紋センサー | - | TODO | [公式Docs](https://docs.m5stack.com/#/en/unit/finger) |
| MODULE GPS | GPSセンサー | - | TODO | [公式Docs](https://docs.m5stack.com/#/en/module/gps) |

### 外部連携 (SORACOM, AWSなど外部と連携するサンプル)
|製品名|製品説明|ディレクトリ|概要|参考URL|
|-----|-------|:-------:|:----:|------|
| HTTP GET リクエスト | HTTP GETプロトコルで、Webサーバからデータを取得する | [Hello-HttpGet](https://github.com/kdg-hacks/kdg-hacks-examples/tree/master/m5stack/Hello-HttpGet) | TODO | - |
| HTTP POST リクエスト | HTTP GETプロトコルで、Webサーバからデータを取得する | [Hello-HttpPost](https://github.com/kdg-hacks/kdg-hacks-examples/tree/master/m5stack/Hello-HttpPost) | TODO | - |
| SORACOM XXX | SORACOM XXX | [TODO](https://github.com/kdg-hacks/kdg-hacks-examples/tree/master/todo) | TODO | - |
| AWS XXX | AWS XXX | [TODO](https://github.com/kdg-hacks/kdg-hacks-examples/tree/master/todo) | TODO | - |
| 赤外線リモコン操作 | 赤外線リモコン操作 | [TODO](https://github.com/kdg-hacks/kdg-hacks-examples/tree/master/todo) | TODO | - |
| 赤外線リモコンセンサー値取得 | 赤外線リモコンセンサー値取得 | [TODO](https://github.com/kdg-hacks/kdg-hacks-examples/tree/master/todo) | TODO | - |

## 参考
