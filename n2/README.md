音声合成ソフトウェア「N2」
=========================
KDDI総合研究所で開発・販売している[音声合成ソフトウェアN2](https://www.kddi-research.jp/products/n2.html)は、省メモリで軽量な日本語音声読み上げソフトウェアです。
今回、マイコン版を利用したスピーカー付き小型音声合成Boxを開発し、I2C経由で制御できるガジェットを用意いたしました。
Wio LTE M1/NB1と接続した場合のArduinoソースコードサンプルを公開いたします。

# N2 I2C TTS コマンド仕様(./n2_i2c_20181106.md)

# [n2tts-simple](./tts-simple-sample)
起動時に起動状況を音声で伝えるだけのサンプル、パラメータの取得・設定方法や合成方法のサンプルコード

# [n2tts-mqtt](./tts-mqtt-sample)
MQTTプロトコルを利用し、受信したテキストを音声合成を行う場合のサンプルコード

# その他
## 環境構築
Wio LTE M1/NB1のセットアップや環境構築にあたっては、[こちら](https://github.com/SeeedJP/Wiki/blob/master/Wio_cell_lib_for_Arduino/home-ja.md)をご覧ください。


##実物イメージ
|日本語音声合成スピーカー付き小型Box|n2-BoxとWio LTE M1/NB1の接続|
|---|---|
|![](https://github.com/kdg-hacks/kdg-hacks-examples/blob/images/n2/images/n2tts_box.jpg)|![](https://github.com/kdg-hacks/kdg-hacks-examples/blob/images/n2/images/n2tts_box.jpg)|


