
= 一番小さなRailsアプリづくり


ここではできるだけ小さい構成のRailsアプリを作ってみます。Railsアプリがどのように動作するのかの説明と、Railsが作るファイルがどのような役割なのか、機能と関連づけて説明していきます。


== 一番小さなRailsアプリをつくる

=== アプリの作成


今回も最初にアプリを作ります。ブラウザに"Hello world!"と表示させるアプリです。前の章で作成した @<tt>{my_web_apps} の下に新しいアプリを作ってみましょう。ターミナルを起動して以下のコマンドを打ちます。


//emlist[][bash]{
cd my_web_apps
rails new helloworld
//}

//cmd{
$ rails new helloworld
      create
... (略)
Your bundle is complete!
Use `bundle show [gemname]` to see where a bundled gem is installed.
         run  bundle exec spring binstub --all
* bin/rake: spring inserted
* bin/rails: spring inserted
//}


次に、前の章と同じように以下のコマンドを実行してみましょう。


//emlist[][bash]{
cd helloworld
rails s
//}

//cmd{
$ rails s
=> Booting Puma
=> Rails 5.0.0.beta3 application starting in development on http://localhost:3000
=> Run `rails server -h` for more startup options
=> Ctrl-C to shutdown server
Puma starting in single mode...
* Version 3.2.0 (ruby 2.3.0-p0), codename: Spring Is A Heliocentric Viewpoint
* Min threads: 5, max threads: 5
* Environment: development
* Listening on tcp://localhost:3000
Use Ctrl-C to stop
//}


ブラウザを起動して以下のURLを入力してアクセスしてみます。

 * http://localhost:3000


//image[welcome_rails][Welcome rails]{
//}




前の章と同じように動作しているかと思います（Rails4.2ではWelcome aboardという画面になります）。ここで実行したコマンド @<tt>{rails s} のsはserverの略で、省略したsでも、省略せずにserverでも、同じように動作します。


=== rails gコマンドでページを作る


ひきつづき、以下のコマンドを入力してみましょう。rails serverが起動している場合は、Ctrl-c（controlキーを押しながらcキー）で終了してからコマンドを打ってください。


//emlist[][bash]{
rails g controller hello index
//}

//cmd{
$ rails g controller hello index
Running via Spring preloader in process 82284
      create  app/controllers/hello_controller.rb
       route  get 'hello/index'
      invoke  erb
      create    app/views/hello
      create    app/views/hello/index.html.erb
      invoke  test_unit
      create    test/controllers/hello_controller_test.rb
      invoke  helper
      create    app/helpers/hello_helper.rb
      invoke    test_unit
      invoke  assets
      invoke    coffee
      create      app/assets/javascripts/hello.coffee
      invoke    css
      create      app/assets/stylesheets/hello.css
//}


もしもrails gコマンドを打ち間違えて違うファイルを作ってしまった場合は、打ち間違えたコマンドのgの部分をdにして再実行すると、rails gコマンドで作成したファイルをまとめて削除してくれます。たとえば、@<tt>{rails g controller hell index} とhelloをhellと打ち間違えた場合は、@<tt>{rails d controller hell index} コマンドを実行することで間違えて作ったファイル群を削除することができます（ターミナルでカーソルキーの↑キーを押すと、さきほど入力した内容が出てくるので、それを利用してgをdに直すと楽に実行できます）。



再びrails serverを起動させましょう。


//emlist[][bash]{
rails s
//}

//cmd{
$ rails s
=> Booting Puma
=> Rails 5.0.0.beta3 application starting in development on http://localhost:3000
=> Run `rails server -h` for more startup options
=> Ctrl-C to shutdown server
Puma starting in single mode...
* Version 3.2.0 (ruby 2.3.0-p0), codename: Spring Is A Heliocentric Viewpoint
* Min threads: 5, max threads: 5
* Environment: development
* Listening on tcp://localhost:3000
Use Ctrl-C to stop
//}


ブラウザを使い、以下のURLへアクセスします。

 * http://localhost:3000/hello/index


//image[hello_index][hello/index]{
//}




この画面が出れば、ここまで意図通りに動作しています。さきほど実行したrails gコマンドはこのページ、/hello/indexを作るものでした。どのような仕組みで動作しているかは後ほどまた説明しますので、今はこのページに"Hello world!"と表示させてみることにしましょう。



@<tt>{app/views/hello/index.html.erb} ファイルをエディタで開いてみてください。以下のような内容になっています。


//emlist[][erb]{
<h1>Hello#index</h1>
<p>Find me in app/views/hello/index.html.erb</p>
//}


これを以下のように変更して、ブラウザで同じURLへアクセスしてみてください。-の行を削除して、+の行を追加してください。先頭の-や+は入力しません。（rails sは起動したままで大丈夫です。もしもrails sを一度終了していた場合は、rails sコマンドでもう一度起動してからアクセスしてください）。


//emlist[][diff]{
- <h1>Hello#index</h1>
- <p>Find me in app/views/hello/index.html.erb</p>
+ <p>Hello world!</p>
//}


//image[helloworld][Hello world]{
//}




"Hello world!"の文字が表示されましたか？これで一番小さなRailsアプリができあがりました。ここへ、少しだけRubyのコードを書いて、現在時刻を表示する機能を追加してみましょう。以下のように、+の行を追加してください。


//emlist[][diff]{
<p>Hello world!</p>
+ <p>現在時刻: <%= Time.now %></p>
//}


//image[time_now][現在時刻表示]{
//}




表示されましたか？ブラウザをリロードすると、現在時刻が更新されます。アクセスしたそのときの時刻が表示されるアプリになりました。



最後に、このままでもいいのですが、コードのロジックの部分をビューに書くのではなく、コントローラで書くことにしましょう。動作は同じまま、コードを書き換えます。



コントローラを次のように変更します。



@<tt>{app/controllers/hello_controller.rb}


//emlist[][diff]{
class HelloController < ApplicationController
  def index
+   @time = Time.now
  end
end
//}


そして、ビューを変更します。



@<tt>{app/views/hello/index.html.erb}


//emlist[][diff]{
- <p>現在時刻: <%= Time.now %></p>
+ <p>現在時刻: <%= @time %></p>
//}


これでブラウザからアクセスすると、先ほどと同じように現在時刻が表示されているかと思います。



次の節から、このアプリがどのように動作しているのかを説明していきます。


== Webアプリはどのように動作しているか


ここで、みなさんが普段ブラウザからつかっているWebアプリがどのように動作しているかを見てみましょう。アドレス入力欄にURLを入力してエンターキーを押すと、「リクエスト」がURL先のサーバへ向けて飛んでいきます。たとえば @<tt>{http://cookpad.com/} と入力した場合は、クックパッドのサーバへ向けてリクエストが飛んでいきます。リクエストは追って説明していきますが、ざっくりと「そのページを見たいという要求（リクエスト）」とイメージしてもらえばOKです。



//image[request][リクエスト]{
//}




Webサーバ上で動作しているWebアプリはリクエストを受け取ると、「レスポンス」としてHTMLで書かれたテキストを作ってブラウザへ返します。レスポンスは「Webアプリが返してきた情報群（HTMLで書かれた表示するの情報を含む）」とイメージできます。HTMLはHyperText Markup Languageのことで、Webページを記述するための言語です。ブラウザはHTMLを解釈して、私たちの見易い、いつも見慣れたWebページを表示します。



//image[response][レスポンス]{
//}




コラム：Webサーバ
Webサーバとはなにものなのでしょうか？Webサーバは「Webサービスを提供する場合に必要な共通の機能を提供するもの」と言えます。Webアプリはブラウザとのやりとりで必要な機能のうち、どのサービスでも使う機能はWebサーバに仕事をまかせ、自分のサービスで必要なオリジナルな機能を提供することになります。Rubyには標準でWEBrickというWebサーバが用意されていて、rails sをしたときに起動するようになっています。実際のWebサービスを運用して提供する場合は、nginxやApacheといったWebサーバを使うことが多いです。



HTMLはブラウザからも見ることができます。Chromeの場合は、どこかのサイト（たとえば @<tt>{http://cookpad.com/}）へアクセスしたあと、右クリックメニューから「ページのソースを表示」を選ぶとHTMLで書かれたそのページを閲覧することができます。



//image[right_click][右クリック]{
//}




//image[html][HTML(抜粋)]{
//}




ここまで説明してきた以下の2つが、ブラウザの主な仕事です。

 * リクエストをWebサーバへ投げる
 * レスポンスで返ってきたHTMLを解釈して表示する

== インターネットの向こう側とこちら側


ブラウザからWebサービスにアクセスするとき、通常、Webアプリはインターネット上にあります。ブラウザだけが自分のPCにあります。



//image[internet_and_local][インターネット上のサービスにアクセス]{
//}




しかし、開発中は自分が作っているアプリをわざわざインターネット上へ置く必要はなく、自分のPCでWebアプリを動作させ、同じく自分のPCにあるブラウザからアクセス可能です。



//image[local][開発中は自分のPCでつくることができる]{
//}



== 今回つくったRailsアプリの動作まとめ


今回つくったRailsアプリの動作を図に描いてみました。



//image[smallest_app][今回つくったRailsアプリの動作]{
//}




ブラウザのURL欄にアドレスを入力してEnterを押すとリクエストが飛びます。リクエストを受け取ったRailsアプリはHTMLをつくり、レスポンスとして返します。レスポンスを受け取ったブラウザはHTMLを解釈し、画面に表示します。


== Railsでの開発の進め方


Railsでの基本的な開発の進め方は以下の2つを繰り返すサイクルになります。

 * ひな形になるファイル（ソースコードや設定ファイル）の生成
 * つくっているアプリ用にファイルを変更、追記


実は、さきほどつくったアプリもこの手順で進めていました。


//emlist[][bash]{
rails new helloworld
rails g controller hello index
//}


これらのコマンドは「ひな形になるファイルの生成」を行っていました。そのあと、@<tt>{app/views/hello/index.html.erb} を編集して、


//emlist[][erb]{
<p>Hello world!</p>
//}


という内容に変更しました。このように、rails gコマンドなどでひな形となるファイルを生成し、それをそのアプリで使いたい形へ変えていく、Railsアプリ開発ではこれを繰り返してつくっていきます。



rails gコマンドはひな形を作成しますが、場合によってはこの手順を飛ばして、ゼロから手で書いても構いません。どちらの手順をつかっても、アプリをつくることが可能です。多くの場合、rails gコマンドを使った方が、楽につくれたり、ミスをしづらくなるので便利です。


== Railsが生成するファイル

=== rails newコマンド


では、Railsはどのようなファイルを生成するのでしょうか。最初のrails newコマンドを実行したとき、以下のようにcreate ...という表示がずらっとされたと思います。railsが生成したファイルとフォルダの名前を表示していたのです。


//cmd{
$ rails new helloworld
create
create  README.rdoc
create  Rakefile
create  config.ru
create  .gitignore
create  Gemfile
create  app
create  app/assets/javascripts/application.js
create  app/assets/stylesheets/application.css
create  app/controllers/application_controller.rb
create  app/helpers/application_helper.rb
create  app/views/layouts/application.html.erb
create  app/assets/images/.keep
create  app/mailers/.keep
create  app/models/.keep
... (略)
//}


これらのファイル群によって、rails newをしただけで（何もコードを書かなくても）Webアプリとして動作します。たくさんのファイルがつくられていますね。Railsアプリの基本的なフォルダとファイル群は以下の図のものです。いきなりすべてを説明するのは難しいので、順番に説明していきます。役割ごとにフォルダが分かれています。それぞれの役割についてはこの後説明していきます。



//image[rails_files][Railsアプリの基本的なフォルダ・ファイル群]{
//}



=== rails gコマンド


次に実行したrails gコマンドで作られたファイルを見てみましょう。


//emlist[][bash]{
rails g controller hello index
//}

//cmd{
$ rails g controller hello index
create  app/controllers/hello_controller.rb
 route  get 'hello/index'
invoke  erb
create    app/views/hello
create    app/views/hello/index.html.erb
invoke  test_unit
create    test/controllers/hello_controller_test.rb
invoke  helper
create    app/helpers/hello_helper.rb
invoke    test_unit
create      test/helpers/hello_helper_test.rb
invoke  assets
invoke    coffee
create      app/assets/javascripts/hello.js.coffee
invoke    scss
create      app/assets/stylesheets/hello.css.scss
//}


ここで実行したrails g controllerコマンドは、URLのパスが/hello/indexであるページを表示するためのファイル群を生成します。gはgenerateの略です。rails g controllerの後ろのhelloとindexが、生成するページのパスを指定していることが分かります。



ちなみに、前にやったrails g scaffoldもgenerateの種類の1つです。scaffoldは編集、更新、削除といったたくさんの機能を一度につくりますが、rails g controllerの場合は生成するページをつくるシンプルなものです。そのほかにもいくつかのgenerateコマンドが用意されています。もしも、コマンドを間違えて生成したファイルをまとめて削除したい場合は、gをdに替えたコマンドを実行すると、まとめて削除することができます。dはdestroyの略です。



ここで生成されたファイルのうち、特に重要なのは以下の3つのファイルです。

 * app/controllers/hello_controller.rb
 * app/views/hello/index.html.erb
 * config/routes.rb


//image[rails_g_controller][rails g controller hello index コマンドで生成されるファイル]{
//}




これらのファイルがどのような働きをしているのかを、次の節でRailsがリクエストを受けてからレスポンスを返すまでの基本的な処理の順序を追いかけながら説明していきます。


== Railsアプリの処理の流れ


ブラウザからアクセスしたときに、Railsアプリはどのように動作しているのでしょうか？以下の図は、今回つくったRailsアプリの動作を示したものです。前に出てきた動作の図から少しだけ詳しく書き加えてあります。



//image[rails_app_semantics][Railsアプリの動作]{
//}




ここでは、この図のRailsAppの部分について詳しく説明していきます。ここから、対象箇所を抜き出したのが次の図です。



//image[rails_app_request_to_response][Railsアプリがリクエストを受けてレスポンスを返すまで]{
//}




リクエストを受けたRailsアプリは、Routes, Controller, Viewの各所で処理を行い、レスポンスとしてHTMLを生成して返します。各所ではそれぞれ仕事の分担が決まっていて、自分の担当の処理を行います。Routes, Controller, Viewでそれぞれどのような処理が行われているのか、順に見ていきましょう。


=== Routes


Routesは「リクエストのURLとHTTPメソッド」に応じて次に処理を行う先を決めるのが仕事です。URLは前に出てきましたが、HTTPメソッドとは何でしょうか？

 * リクエスト
 ** URL : http://localhost:3000/hello/index
 ** HTTPメソッド：GET


リクエストを構成する要素のうち、重要なものがURLとHTTPメソッドです。URLはアドレスということもあるように、インターネット上の住所を表します。URLでアクセスする先を指定するのです。もう一方のHTTPメソッドは、そのURLに対して「何をするか」を指示するものです。ブラウザのアドレス欄へURLを入力しEnterを押すと、HTTPメソッド "GET" でリクエストが飛びます。GETは「ページを取得する」の意です。GETのほかにも、HTTPメソッドはいくつかあり、Railsアプリでよく使うものは4つほどです。GET以外のHTTPメソッドは次の章以降で説明していきます。



まとめると、リクエストは「URL」でアクセス先を、「HTTPメソッド」で行うことを指定します。



//image[routes_mapping][Routes]{
//}




Routesの処理を、HTTPメソッドを加えてもう少し詳しくみてみましょう。最初に説明した通り、Routesは「リクエストのURLとHTTPメソッド」に応じて次に処理を行う先を決めるのが仕事です。RailsではRoutesの処理が終わると、次はControllerのアクションへ処理が移ります。



アクションとはControllerのメソッドのうち、publicなメソッドのことです（「Routesから呼び出せるもの」とも言えます）。RoutesはリクエストのURLとHTTPメソッドから、処理の進み先であるContollerのアクションを決定します。RoutesはリクエストとControllerのアクションとの対応表と言えます。



では、Routesの対応表を見て見ましょう。rails serverを起動させて以下へアクセスすると、Routesの対応表が表示されます。（図参照）

 * http://localhost:3000/rails/info/routes


//image[routes][Routes対応表]{
//}




表中の "HTTP Verb" がHTTPメソッドです。"Path"はURLの後半部分に相当します。URLが"http://localhost:3000/hello/index"である場合、パスは"/hello/index"になります。(表示されたPathの後半部分の`"(.:format)"は省略できる記述で、レスポンスで返すフォーマットを指定するための機能です。省略した場合はHTMLを返すのが普通です。)



右端の"Controller#Action"が処理の移るコントローラとアクションを示しています。ここでは "hello#index" と書かれていますが、#より左側がコントローラ名、右側がアクション名です。この場合は、「HelloControllerのindexアクション」を示しています。



まとめると、この対応表は「リクエストのHTTPメソッドが"GET"、パスが"/hello/index"のとき、次の処理は"HelloController"の"index"アクションになる」という意味になります。



ここで表示されたRoutesは@<tt>{config/routes.rb}ファイルから生成されます。このファイルを開くと以下のような記述があります。


//emlist[][ruby]{
get 'hello/index'
//}


これがRoutesのコード部分で、この1行からさきほど説明した対応表が生成されています。「パス"hello/index"へのGETでのアクセスでHelloControllerのindexアクションが呼ばれる」という文です。Routesの書き方はまた追って説明していきます。



それでは次に、処理が進む先となるコントローラをみてみましょう。


=== コントローラ


コントローラはさまざまな処理を行い、次のビューに処理を渡します。コントローラのファイルは@<tt>{app/controllers/}へ置きます。さきほどのRoutesで指定されたHelloControllerは@<tt>{app/controller/hello_controller.rb} というファイルです。


//emlist[][ruby]{
class HelloController < ApplicationController
  def index
    @time = Time.now
  end
end
//}


HelloControllerのindexアクションが呼び出されます。@<tt>{def index}から@<tt>{end}までがindexアクションです。ここでは @timeというインスタンス変数に現在時刻を代入しています。



変数は荷札のようなもので、あとから代入したものにアクセスできるように名前をつける仕組みです。変数のうち、@はじまりの変数のことをインスタンス変数といいます。インスタンス変数を使うと、コントローラから（このあと処理する箇所である）ビューへ情報を伝えることができます。ちなみに、@はじまりではない変数はローカル変数と呼ばれるもので、このメソッド（アクション）を抜けると役目を終えて参照できなくなります。つまり、ローカル変数はビューから参照することができません。ビューから参照するためには@はじまりのインスタンス変数を利用します。



//image[instance_variable][インスタンス変数を使うとビューへ情報を渡すことができる]{
//}




どのビューへ処理が進むかはコントローラで指定可能ですが、今回のように何も指定が無い場合は、コントローラおよびアクションと同名のビューを選択します。今回はHelloControllerのindexアクションなので、対応するビューのファイルはapp/views/hello/index.html.erbになります。



//image[controller][コントローラの動作]{
//}



=== ビュー


ビューではHTMLをつくります。ビューでの処理が終わると、ここで作られたものからレスポンスを作り、ブラウザへ送ることなります。



index.html.erbは、HTMLのもとになるファイルです。ブラウザで表示させるための言語HTMLをそのまま書くことができます。さらに、普通のHTMLと違いとして、Rubyのコードを実行した結果を埋め込むことができます。（このようなファイルをテンプレートと呼びます。ここではerbという種類のテンプレートが使われています）。書かれているHTMLと、埋め込まれたRubyのコードを実行した結果をあわせてHTMLを作ります。では、さきほど書いた実際のビューファイルを見てみましょう。



@<tt>{app/views/hello/index.html.erb}


//emlist[][erb]{
<p>現在時刻: <%= @time %></p>
//}


HTMLのpタグがあります。その中にHTMLにはない @<tt>{<%=} と @<tt>{%>} というタグがあります。これがRubyのコードを実行するためのタグです。ここではその中にはある @<tt>{@time} が実行されます。@timeはコントローラのところで作られたインスタンス変数です。実行すると、変数が指しているもの、つまりコントローラで実行された @<tt>{Time.now} の結果で置き換えられます。このビューで作られたHTMLは、ブラウザで確認することができます。さきほどブラウザから見たように、現在時刻が表示されます（実際には、ビューが作ったHTMLに、Railsがその他の加工を加えて送出します）。



//image[time_now][ブラウザからビューがつくったHTMLを確認]{
//}




ビューについての動作をまとめると以下のようになります。



//image[view][ビュー]{
//}



=== まとめ


最小構成のRailsアプリをつくり、リクエストを受けてレスポンスを返すまでの動作について説明しました。ポイントをまとめると以下のようになります。

 * Routes、コントローラ、ビューの順番で処理を行い、HTMLを作ってブラウザへレスポンスを返す
 * RoutesはリクエストのURLとHTTPメソッドに応じて、処理をするコントローラとアクションを決める対応表
 * コントローラはさまざまな処理を行い、ビューに処理を渡す
 * ビューはテンプレートに埋め込んであるRubyのコードを実行してHTMLを作る
 * コントローラからビューへ情報を伝える場合は@はじまりのインスタンス変数を使う


//image[rails_app_request_to_response][Railsアプリがリクエストを受けてレスポンスを返すまで]{
//}



== さらに学びたい場合は
 * @<href>{http://railsguides.jp/action_view_overview.html,Rails Guides : Action View の概要}
 ** ビューについての詳しい解説です。
