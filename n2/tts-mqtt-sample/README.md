MQTTプロトコルを利用したn2日本語音声合成スピーカー付き小型Box連携サンプル
=========================
サンプル内容自体はコードをご確認いただくとして、ここでは、簡易動作環境構築方法について記載いたします。

# MQTTブローカー環境構築をawsで
MQTTブローカー自体をサービス提供している事業者もおりますが、今回はawsのec2を利用しました。
インスタンスに[]オープンソースMosquitto](https://github.com/eclipse/mosquitto)をインストールして利用します。

## aws環境について
基本的な情報は、[こちら](https://aws.amazon.com/jp/blogs/news/how-to-bridge-mosquitto-mqtt-broker-to-aws-iot/)のページをご覧いただければ十分ですが、現時点(2018/11/14)で若干情報が変わっている点などがありますので、その補足を行います。
ちなみにブリッジ環境でもないので、より簡単になります。

###Role設定はスキップ
いきなりですが、IAM Role作成について記載がありますが、これは不要です。
インスタンス生成（10以降）からご覧ください。
先に進むとRoll設定部分もありますが、デフォルトのままでOKです。

###インスタンス作成
上部メニューの、サービス->EC2
インスタンスの作成ボタンクリック
「Amazon Linux 2 AMI (HVM), SSD Volume Type」（無償枠）を選択
してください。

### セキュリティグループ設定
インバウンド向けのポートとして8883と記載されていますが、1883としてください。ブリッジのためにポート番号が異なりますが、通常MQTTが利用する1883としておけば良いです。

### プライベートキー生成
上記参照webに特に記載がありませんが、途中でプライベートキー生成要求があるので、生成してダウンロードしておく。(例として、~/.aws/MosquittoBroker_kddiresearch.pemという名称・場所に保存して、以下のように設定することで、`ssh mosquitto`でsshログインができます)
ホスト名称は、インスタンス生成後に管理画面から当該インスタンスを選択して上部にある「接続」ボタンをクリックすると表示される。
```
# ~/.ssh/config
host mosquitto
	Hostname ec2-xx.xx.xx.xx.us-east-2.compute.amazonaws.com
	User ec2-user
	Port 22
	IdentityFile ~/.aws/MosquittoBroker_kddiresearch.pem
```

## mosquittoのインストール手順

```/bin/bash
$ curl -OL http://download.opensuse.org/repositories/home:/oojah:/mqtt/CentOS_CentOS-7/home:oojah:mqtt.repo
$ sudo mv home\:oojah\:mqtt.repo /etc/yum.repos.d/mqtt.repo

$ sudo yum install mosquitto mosquitto-clients
　うまくいかない。。依存関係で失敗

$ sudo yum install epel-release
　これもダメ
$ sudo amazon-linux-extras install epel
　これでやれとメッセージが出たので、

これでOK
$ sudo yum install libwebsockets
$ sudo yum install mosquitto mosquitto-clients

動作確認
$ mosquito -d
$ mosquitto_sub -d -t orz

別の端末、PC等から
$ mosquitto_pub -d -t orz -m 'hello mosquitto' -h ec2-xx-xx-xx-xx.us-east-2.compute.amazonaws.com

mosquitto_subを行った画面にhello mosquitto が表示されればOK
```

## Arduino用Mosquittoクライアントライブラリ
Arduino IDEに登録済みのクライアントライブラリではなく、[SeeedJPさんのpubsubclient](https://github.com/SeeedJP/pubsubclient)を利用します。[ZIP形式のライブラリインストール方法](https://www.mgo-tec.com/arduino-ide-lib-zip-instal)を参考に、githubからzipファイルをダウンロードし、スケッチメニューから
ライブラリをインクルード->　.ZIP形式のライブラリをインストールを選択して、ダウンロード
したファイルを選択するだけとなります。

## 動作確認方法
mosquitto クライアントを利用すれば良いのですが、
Chrome ExtensionやiOSアプリなど
いくつか試したところ、想定通りの動作にならないクライアントが結構ありましたので、
念のため、こちらで確認したアプリをご紹介いたします。
[Mpttt by Chenhsin Wong](https://appadvice.com/app/mqttt/1217080708)で、動作画面イメージは以下の通りです。
|起動画面|メッセージ送信画面|
|---|---|
|![](https://github.com/kdg-hacks/kdg-hacks-examples/blob/images/n2/images/Screen Shot 2018-11-13 at 18.49.46.png)|![](https://github.com/kdg-hacks/kdg-hacks-examples/blob/images/n2/images/Screen Shot 2018-11-13 at 19.14.35.png)|







