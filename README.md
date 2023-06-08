# IVRC2022_Heartbeat
IVRC2022の心臓を掴まれる~掌~で使用したソフトウェア部分

- comxxは、使用するPC毎に指定が異なる。Arduino IDEなどで使用するポートなどを確認すること

### heart_beat_left.ino
- 心臓鼓動部左側部品。
- 右側部分と併せて使用する
- 左右部品でシリアル通信はしていない。（間に合わなかった）
- PC本体とのシリアル通信もしていない（独立で動く）

### heart_beat_right.ino
- 心臓鼓動部分右側部品。
- ほかの説明は heart_beat_left.ino と同様


### heart_crank.ino
- 胸に提示装置をぶつけるクランク機構の動作コード
- python コードとあわせて使用する

### sensing_heart_beat.ino
- 圧力センサーで特定の閾値以上の値がでたことを検知するコード
- python コードと併せて使用する

### heart_grabber.ino
- ヘッドマッサージのやつで心臓をひねるモーター制御用
- python コードと併せて使用する

### serialcon_to_arduino.py
- sensing_heart_beat.ino, heart_crank.ino, heart_grabber.ino のシリアル通信を制御するコード
- Arduinoを3台以上連結するのに面倒くさいので使った。
- Anaconda 3で実機は動作（python 3.xでも動くかも？）
- serial通信のライブラリ(pyserial)を手動インポート必須
