// SORACOM LTE-Button サンプル
// SORACOM LTE-Button -> IoT 1-Click -> AWS Lambda -> Slackへのメッセージ通知の例
// 参考リンク：https://dev.soracom.io/jp/aws_button/getting-started/

const https = require('https');
const url = require('url');
const defaultSlackUrl=process.env['SLACK_URL']
const defaultMessage={
  "SINGLE": "Single Click",
  "DOUBLE": "Double Click",
  "LONG": "Long Click"
}

exports.handler = (event, context, callback) => {
  console.log('Received event:', JSON.stringify(event, null, 2));

  // SlackのWebhook URLをAWS Lambdaの環境変数から取得
  var slackUrl = (event.placementInfo.attributes.slackUrl)? event.placementInfo.attributes.slackUrl:defaultSlackUrl
  if(!slackUrl){
    console.log('SlackのWebhook URLが設定されていません。AWS Lambdaの[環境変数:SLACK_URL]に設定してください。');
    return;
  }
  var slackReqOptions = url.parse(slackUrl);
  slackReqOptions.method = 'POST';
  slackReqOptions.headers = { 'Content-Type': 'application/json' };

  // Slack通知メッセージにSORACOM LTE-M Buttonのボタン操作に応じたメッセージを送信
  //  1回クリック：Single Click
  //  2回クリック：Double Click
  //  ロングクリック：Long Click
  var text = defaultMessage[event.deviceEvent.buttonClicked.clickType]
  var payload = {'text': text, "attachments":[{"text":JSON.stringify(event,null,2)}] }

  // IoT 1-Click のプレイスメント:usernameからSlackメッセージを投稿するユーザ名を設定
  if (event.placementInfo.attributes.username) {
    payload.username = event.placementInfo.attributes.username;
  }

  // Slack通知
  var body = JSON.stringify(payload);
  slackReqOptions.headers = {
    'Content-Type': 'application/json',
    'Content-Length': Buffer.byteLength(body),
  };
  var req = https.request(slackReqOptions, function(res) {
    if (res.statusCode === 200) {
      console.log('Posted to slack');
      callback(null, {"result":"ok"});
    } else {
      callback(false, {"result":"ng", "reason":'Failed to post slack ' + res.statusCode})
    }
    return res;
  });
  req.write(body);
  req.end();
};
