# 2Dシューティングゲーム
勉強のためにOpenGL+SDLを使った2Dシューティングゲームを作りました。

このリポジトリはソースコードの公開のためのリポジトリです。また、本リポジトリ内にはアプリをビルドするのに必要なファイルがいくつか含まれていませんのでご注意ください。

## ゲーム内容
プレイヤーは右からやってくる敵のUFOをレーザーで倒します。WASDで移動、スペースキーでレーザーの発射が可能です。プレイヤーが敵のUFOと衝突するか、敵が1体でも画面の左端に到達してしまったらゲームオーバーとなります。どれだけ長く敵の侵攻を食い止められるかがこのゲームの楽しみ方です。

https://yubeshicat.hatenablog.com/entry/2022/01/08/004613

## 工夫点
このゲームはある書籍を参考にして実装しました。しかし、その書籍で紹介されていたUIの設計、特にUIパーツの扱いはあまり綺麗ではありませんでした。そこで、少しは使いやすくしたいと思い、自分でUIシステムの設計をすることにしました。

簡潔に書くと以下のような仕組みになっています。

<img src="class_diagram/UISystem.png">

UIScreenというUIパーツを配置するためのキャンバスとなるクラスがあり、新規UI画面を作るごとにUIScreenクラスを継承した新しいスクリーンクラスを作成します。

ゲーム内に存在するUIScreenの派生クラスとしては
- StartUpScreen
- TitleScreen
- PauseScreen
- ResultScreen
- CopyrightScreen

があります。それぞれのコンストラクタではUIパーツが生成され、生成されたUIパーツはスクリーンに保持されます。

UIパーツはテキスト、画像、ボタンの3種類が存在し、これらのパーツは UIComponent クラスから派生しています。基底クラスとなるUIComponentクラスはUIパーツの座標やスケール、角度といった情報を保持していて、派生クラスではテキストや画像、ボタンクリック時のイベントハンドラといったそれぞれのUI要素に関連するメンバ変数を持ちます。

UIScreenクラスには2つの仮想関数が存在し、それぞれ入力処理時、ゲームループの更新時に呼ばれます。必要に応じてオーバーライドさせることで、それぞれのスクリーンが保持するUIパーツの状態を変化させることができるようになっています。たとえば、マウスのドラッグを検知してUIパーツの表示位置を変更させることで画面のスクロールを実現したりしています。

UIScreenの派生クラスのインスタンスはゲームループを管理するGameクラスによって保持されています。新しくスクリーンのインスタンスが作られる度にインスタンスがスタックに積まれます。入力データはスタックのトップのスクリーンにのみ渡るようになっていて、これによりポーズメニューを開いている間にゲームプレイ画面でのUIを操作できないようにしたりすることができます。

## 権利表記

[The OpenGL Extension Wrangler Library]

Copyright (C) 2002-2007, Milan Ikits <milan ikits[]ieee org>
Copyright (C) 2002-2007, Marcelo E. Magallon <mmagallo[]debian org>
Copyright (C) 2002, Lev Povalahev
All rights reserved.

Redistribution and use in source and binary forms, with or without 
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, 
  this list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright notice, 
  this list of conditions and the following disclaimer in the documentation 
  and/or other materials provided with the distribution.
* The name of the author may be used to endorse or promote products 
  derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
THE POSSIBILITY OF SUCH DAMAGE.





[OpenGL Mathematics (GLM)]

The MIT License

Copyright (c) 2005 - G-Truc Creation

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.



[Simple DirectMedia Layer (SDL)]

Copyright (C) 1997-2022 Sam Lantinga <slouken@libsdl.org>

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required. 
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.




[SDL_ttf]

SDL_ttf:  A companion library to SDL for working with TrueType (tm) fonts
Copyright (C) 1997-2019 Sam Lantinga <slouken@libsdl.org>

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
  claim that you wrote the original software. If you use this software
  in a product, an acknowledgment in the product documentation would be
  appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
  misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.





[Simple-OpenGL-Image-Library (SOIL)]

Public domain.

https://github.com/paralin/soil






Sprites

See license.txt in the Assets folder.


Sound:
- SE

  The SEs in this game are provided by OtoLogic and licensed under the CC BY 4.0.

  https://otologic.jp

- BGM

  The BGM used in this game was borrowed from MusMus.

  https://musmus.main.jp



Sound middleware

Made with FMOD Studio by Firelight Technologies Pty Ltd.

Audio Engine: FMOD Studio by Firelight Technologies Pty Ltd.

<br>
<br>
<img src="src/Assets/fmod_logo_white_back.png" width=60%>
<br>
<br>

[OGG VORBIS CODEC]

FMOD uses the Ogg Vorbis codec © 2002, Xiph.Org Foundation.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

Redistributions of source code must retain the above copyright notice, the list of conditions and the following disclaimer.
Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other material provided with the distribution.
Neither the name of the Xiph.org Foundation nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS “AS IS” AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.



[RESONANCE AUDIO SDK]

FMOD includes Resonance Audio SDK, licensed under the Apache Licence, Version 2.0 (the Licence); you may not use this file except in compliance with the License. You may obtain a copy of the License at:

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an “AS IS” BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License.
