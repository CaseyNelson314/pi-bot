# pibot

## ロボットとの通信方法

### 移動量、アームの角度の送信

移動量、アームの角度等の指令値は、WebSocket を用いてロボットへ送信します。指令値を送信する PC は Raspberry Pi と同一の LAN に接続されている必要があります。

接続の際には Raspberry Pi 上に起動された WebSocket サーバーの URL が必要で、サーバーの URL、ポートは次の通りです。

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
        "axis4": 0.51,    // 第4関節 (rad)
        "axis5": 0.51     // 第5関節 (rad)
    }
}
```

WebSocket クライアントアプリである wscat を用いて動作検証できます([wscat インストール先](https://github.com/websockets/wscat)) 。次のコマンドでサーバーに接続できます。

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

### カメラ映像の受信

カメラの映像は WebRTC を用いて受信します。WebRTC サーバーの URL は次の通りです。

```txt
ws://raspberrypi.local:8000/ws
```

momo というソフトウエアを用いて配信しており、正常に配信出来ているか確認できるウェブページも同時に配信されています。次のURLから閲覧できます。Raspberry Pi と同一 LAN に存在する PC のブラウザで開いてください。momo の公式ページは[こちら](https://momo.shiguredo.jp/)です。

<http://raspberrypi.local:8080/html/test.html>

## 一から構築する手順

Raspberry Pi Zero 2 W に SSH で接続します。Raspberry Pi のターミナルが使えればよく、HDMI 接続でも実行可能です。

以下コマンドは全て Raspberry Pi 上で実行するコマンドです。また本プロジェクトはホームディレクトリに配置される前提で制作しています。

### 1. ツールチェーンインストール

```sh
sudo apt update
sudo apt upgrade
sudo apt install cmake
```

### 2. アクチュエーター制御用サーバー構築

本プロジェクトをクローン

```sh
git clone https://github.com/CaseyNelson314/pibot.git
cd ~/pibot/actuator_ctrl_server/
```

ビルド

```sh
cmake -S . -B build
cmake --build build
```

起動時に実行されるように systemd に登録

```sh
sudo cp ~/pibot/actuator_ctrl_server/actuator.service /etc/systemd/system/
sudo systemctl start  actuator.service
sudo systemctl enable actuator.service
```

> 単体で実行する場合 (9000番ポートでサーバーを起動)
> 
> ```sh
> sudo ~/pibot/actuator_ctrl_server/build/pibot 9000
> ```

### 3. カメラ映像配信サーバー構築

```sh
cd ~/pibot/camera_streaming_server/
```

起動時に実行されるように systemd に登録

```sh
sudo cp ~/pibot/camera_streaming_server/camera_streaming_server.service /etc/systemd/system/
sudo systemctl start  camera_streaming_server.service
sudo systemctl enable camera_streaming_server.service
```

> 本プロジェクトには momo の実行バイナリを直接含んでいますが、最新バイナリは[リリースページ](https://github.com/shiguredo/momo/releases)から取得できます。
