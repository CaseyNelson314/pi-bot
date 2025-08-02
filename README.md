# pi-bot

## 移動量、アームの角度の送信方法

移動量、アームの角度等の指令値は、WebSocket を用いてロボットへ送信します。接続の際には Raspberry Pi 上に起動された WebSocket サーバーの URL が必要です。また指令値を送信する PC は Raspberry Pi と同一の LAN に接続されている必要があります。

WebSocket サーバーの URL は次の通りです。

```txt
ws://raspberrypi.local:9000
```

指令値は JSON 形式の文字列で送信し、形式は次の通りです。

```json
{
    "wheel": {
        "x": 0.0,    // X移動量 (-1~1)
        "y": 0.3,    // Y移動量 (-1~1)
        "turn": 0.1  // 旋回量  (-1~1)
    },
    "arm": {
        "axis1": 3.14,    // 第1関節 (rad)
        "axis2": 0.23,    // 第2関節 (rad)
        "axis3": -0.3,    // 第3関節 (rad)
        "axis4": 0.51     // 第4関節 (rad)
    }
}
```

### WebSocket サーバーの動作確認

デバッグの際に、Unity 側に問題があるのか、Raspberry Pi 側に問題があるのか、混乱するかと思いますので、WebSocket サーバーを単体で動作検証する方法を示します。

WebSocket クライアントアプリである wscat を用いて動作検証します([wscat インストール先](https://github.com/websockets/wscat)) 。次のコマンドでサーバーに接続できます。

```sh
wscat -c ws://raspberrypi.local:9000  # URL:ポート番号
```

接続されると次のように送信値の入力を求められます。接続できない場合、Raspberry Pi 側に問題があります。

```sh
Connected (press CTRL+C to quit)
>
```

例として次のように指令値を入力します。y 方向に 0.5 の出力値で移動する指令値です。

```
> { "wheel": { "x": 0, "y": 0.5, "turn": 0 }, "arm": { "axis1": 0, "axis2": 0, "axis3": 0, "axis4": 0, "axis5": 0 }  }
```

問題なくロボットへ送信できた場合、OK とレスポンスが返ります。

```sh
< [ OK ]
```

## 一から構築する手順

Raspberry Pi Zero 2 W に SSH で接続。ターミナルが使えればよいので、HDMI を接続して画面を出力させ、ターミナルを起動しても大丈夫です。

```sh
sudo apt update
sudo apt upgrade
```

ツールチェーンをインストール

```sh
sudo apt install cmake
```

本プロジェクトをクローン

```sh
git clone https://github.com/CaseyNelson314/pi-bot.git
cd ./pi-bot/core_daemon/
```

ビルド

```sh
cmake -S . -B build
cmake --build build
```

実行

```sh
sudo ./build/pibot 9000
```
