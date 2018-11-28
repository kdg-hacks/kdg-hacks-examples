# SORACOM-lte-m-button-guide
`SORACOM LTE-M Button` のボタン押下にてSlackへ通知するサンプルコードのガイド

## 事前準備
`SORACOM LTE-M Button` を利用する場合、事前準備として以下の設定が必要です。

### `SORACOM LTE-M Button` をSORACOMコンソールへ登録
SORACOMコンソールへログインし、 `SORACOM LTE-M Button` を登録してください。
※ハッカソン参加者の方に配られる `SORACOM LTE-M Button` は既に登録されているため、本作業は不要です。

[参考URL　SORACOM LTE-M Button powered by AWS をソラコムのガジェット管理に登録する](https://dev.soracom.io/jp/start/aws_button_registration/)


### `SORACOM LTE-M Button` をAWS IoT 1-Clickへ登録
AWSコンソールへログインし、 AWS IoT 1-Clickへ `SORACOM LTE-M Button` を登録してください。

[参考URL　ステップ 1: AWS IoT 1-Clickに登録する](https://dev.soracom.io/jp/start/aws_button_slack/#registration)


### `SORACOM LTE-M Button` 用のAWS IoT 1-Clickのプロジェクトを作成
AWSコンソールへログインし、 AWS IoT 1-Clickのプロジェクトを作成してください。

[参考URL　ステップ 2: AWS IoT 1-Click のプロジェクトを作成する](https://dev.soracom.io/jp/start/aws_button_slack/#project)


### `SORACOM LTE-M Button` 用のSlack通知用 AWS Lambdaを作成
AWSコンソールへログインし、 AWS Lambdaを作成してください。

- AWS Lambdaについては同ディレクトリに存在する `Hello-SORACOM-lte-m-button.js` の内容を利用してください
- SlackのWebhook URLについては各自Slackの[Incoming Webhook](https://api.slack.com/incoming-webhooks) を設定して利用してください

[参考URL　ステップ 5: Lambda関数を作成してSlackに通知する](https://dev.soracom.io/jp/start/aws_button_slack/#slack)


## `SORACOM LTE-M Button` とSlack連携確認
`SORACOM LTE-M Button` のボタンを 1回クリック,2回クリック,ロングクリックするとSlackに以下のようなメッセージが通知されます。

![Slack通知例](./Slack通知例.png "Slack通知例")
