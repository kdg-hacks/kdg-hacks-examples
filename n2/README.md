音声合成ソフトウェア「N2」
=========================
KDDI総合研究所で開発・販売している[音声合成ソフトウェアN2](https://www.kddi-research.jp/products/n2.html)は、省メモリで軽量な日本語音声読み上げソフトウェアです。
今回、スピーカー付き小型音声合成Boxを開発しました。本Boxは、I2C経由で制御可能で、
Wio LTE M1/NB1と接続した場合のArduinoソースコードサンプルを公開いたします。

# [N2 I2C TTS コマンド仕様](./n2_i2c_20181106.md)
こちらの仕様とサンプルを見比べることで理解が深まると思います。

# [n2tts-simple](./tts-simple-sample)
起動時に起動状況を音声で伝えるだけのサンプル、パラメータの取得・設定方法や合成方法のサンプルコード

# [n2tts-mqtt](./tts-mqtt-sample)
MQTTプロトコルを利用し、受信したテキストを音声合成を行う場合のサンプルコード

# その他
## 環境構築
Wio LTE M1/NB1のセットアップや環境構築にあたっては、[こちら](https://github.com/SeeedJP/Wiki/blob/master/Wio_cell_lib_for_Arduino/home-ja.md)をご覧ください。


## 実物イメージ

|2種類のスピーカー付き小型音声合成Box|n2-BoxとWio LTE M1/NB1の接続|
|---|---|
|<img src="https://github.com/kdg-hacks/kdg-hacks-examples/blob/images/n2/images/n2tts_box2.jpg" width=320><br />左（黒）:ビジネスウーマン, address=0x4E<br />右（灰）:アニメ声, address: 0x4F|<img src="https://github.com/kdg-hacks/kdg-hacks-examples/blob/images/n2/images/wio_n2tts_box.jpg" width=320>|


