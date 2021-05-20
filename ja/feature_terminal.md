# ターミナル

<!---
  original document: 0.8.147:docs/feature_terminal.md
  git diff 0.8.147 HEAD -- docs/feature_terminal.md | cat
-->

> この機能は現在のところ*巨大*であり、おそらく大量のメモリを搭載したキーボード、または楽しみのためにのみ配置する必要があります。

ターミナル機能はテキストエディタを介してキーストロークで通信するように設計されたコマンドラインのようなインタフェースです。エディタで自動インデント機能をオフにすることは有益です。

有効にするには、以下を `rules.mk` または `Makefile` に貼り付けます:

    TERMINAL_ENABLE = yes

そして、オンまたはオフにするために、`TERM_ON` および `TERM_OFF` キーコードを使います。

有効な場合、`> ` プロンプトが現れ、ここでコマンドやバックスペース(オーディオが有効な場合は、先頭に到達するとベルが鳴ります)を入力することができ、エンターを入力するとコマンドを送信します。矢印キーは現在のところ無効なため、混乱することはありません。マウスでカーソルを移動することはお勧めしません。

`#define TERMINAL_HELP` は、このページでは実際には必要のない他の出力ヘルパーを有効にします。

"上矢印" および "下矢印" により、過去に入力した5つのコマンドを順に切り替えることができます。

## 今後のアイデア

* キーボード/ユーザ拡張可能なコマンド
* より小さなフットプリント
* 矢印キーのサポート
* コマンド履歴 - 完了
* SD カードのサポート
* バッファディスプレイのための LCD サポート
* キーコード -> 名称の対応表
* レイヤー状態
* *アナログ/デジタル ポートの読み込み/書き込み*
* RGB モード関連機能
* マクロ定義
* EEPROM の読み込み/書き込み
* オーディオ制御

## 現在のコマンド

### `about`

現在の QMK のバージョンとビルドした日の出力:

```
> about
QMK Firmware
  v0.5.115-7-g80ed73-dirty
  Built: 2017-08-29-20:24:44
```


### `print-buffer`

最後に入力した5つのコマンドの出力

```
> print-buffer
0. print-buffer
1. help
2. about
3. keymap 0
4. help
5. flush-buffer
```

### `flush-buffer`

コマンドバッファをクリア
```
> flush-buffer
Buffer cleared!
```


### `help`


利用可能なコマンドの出力:

```
> help
commands available:
  about help keycode keymap exit print-buffer flush-buffer
```

### `keycode <layer> <row> <col>`

特定のレイヤー、行および列のキーコード値の出力:

```
> keycode 0 1 0
0x29 (41)
```

### `keymap <layer>`

特定のレイヤーの全てのキーマップの出力

```
> keymap 0
0x002b, 0x0014, 0x001a, 0x0008, 0x0015, 0x0017, 0x001c, 0x0018, 0x000c, 0x0012, 0x0013, 0x002a,
0x0029, 0x0004, 0x0016, 0x0007, 0x0009, 0x000a, 0x000b, 0x000d, 0x000e, 0x000f, 0x0033, 0x0034,
0x00e1, 0x001d, 0x001b, 0x0006, 0x0019, 0x0005, 0x0011, 0x0010, 0x0036, 0x0037, 0x0038, 0x0028,
0x5cd6, 0x00e0, 0x00e2, 0x00e3, 0x5cd4, 0x002c, 0x002c, 0x5cd5, 0x0050, 0x0051, 0x0052, 0x004f,
>
```

### `exit`

ターミナルの終了 - `TERM_OFF` と同じ。