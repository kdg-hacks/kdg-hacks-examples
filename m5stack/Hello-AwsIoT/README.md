# M5StackをAWS IoTにつなぐサンプル

基本的に、[こちらのブログ(M5Stackを利用したAWS IoTの簡単な使い方)](http://kyokucho1989.chillout.jp/2019/08/19/m5stack%E3%82%92%E5%88%A9%E7%94%A8%E3%81%97%E3%81%9Faws-iot%E3%81%AE%E7%B0%A1%E5%8D%98%E3%81%AA%E4%BD%BF%E3%81%84%E6%96%B9/)を参考にすれば実行可能でした。
この記事は念の為、ダウンロードして`html`ディレクトリに格納しております。

5秒おきに、messageを`publish`し、指定したトピックに対して`subscribe`を行うサンプルになっております。

## 記事実行時の注意点

### ルートCAについて

記事の途中でルートCAをダウンロードする箇所があるが、リンク先が記事の時と変わっているようだったので、下記のURLから`Amazon ルートCA 1`ダウンロードすると良いです。
<https://docs.aws.amazon.com/ja_jp/iot/latest/developerguide/managing-device-certs.html>

### トピックの購読(Subscribe)について

記事のサンプルコードでは、`mqttCallback` がありますが、`subscribe`していなかったためこの関数が呼ばれないようです。
そのため、本サンプルでは`sub01`というトピックに対して`subscribe(mqttClient.subscribe(subTopic, 0);)`するように変更を行なっております。

```Hello-AwsIoT.ino
void loop() {
  if (!mqttClient.connected()) {
    connect_awsiot();
  }

  // subscribeのトピックを指定。これがないとmqttCallbackに入ってこない模様。
  // https://dotstud.io/blog/nefry-bt-connect-mqtt/
  mqttClient.subscribe(subTopic, 0);

  ...
```

### Upload(m5stackにソースを流し込む)時にたまに起きるエラーについて

コンパイルが成功するが、アップロード時に`A fatal error occurred: Timed out waiting for packet content` が起きることがありました。

[これはESP32のバグのようです。](https://dotstud.io/docs/nefrybt-error-handling-2/)

`Upload Speed`を遅くしたり、ケーブルの抜き差しを行うと解消しました。
