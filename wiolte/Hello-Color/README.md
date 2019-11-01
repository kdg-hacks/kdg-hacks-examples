# Color-sensor-guide
Grove I2C Color Sensor V2.0 サンプルコードのガイド

# 前準備

Grove I2C Color Sensor V2.0 は公式に、Wio LTE M1/NB1をサポートしていないため、以下の手順でライブラリを追加してください。

- [Hello-Color/lib/GroveColorV2.zip](https://github.com/kdg-hacks/kdg-hacks-examples/tree/master/Hello-Color/lib/GroveColorV2.zip)をダウンロードします。
- Arduino IDEを起動します
- 「スケッチ」 → 「ライブラリをインクルード」 → 「.ZIP形式のライブラリをインストール」を選択
- zipファイルを要求されるので、先程ダウンロードした「GroveColorV2.zip」を選択
- 「スケッチ」 → 「ライブラリをインクルード」 → 「Grove - I2C Color Sensor V2 Library  for Wio LTE M1/NB1(BG96)」を選択

# 実行
Hello-Color.inoを開き、Arduino IDEより、マイコンボードに書き込むことで実行されます。

# 動作確認
[Hello-Color/color_tester.html](https://github.com/kdg-hacks/kdg-hacks-examples/tree/master/Hello-Color/color_tester.html)に、指定した色を画面全体に表示するHTMLを付属してます。

# その他ライセンスなど

「Grove - I2C Color Sensor V2 Library  for Wio LTE M1/NB1(BG96)」は、BSD Licenseに則り「Grove_I2C_Color_Sensor_TCS3472」を修正して作成しました。
https://github.com/Seeed-Studio/Grove_I2C_Color_Sensor_TCS3472
