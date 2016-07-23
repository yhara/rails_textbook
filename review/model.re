
= モデル


この章ではデータの長期保存と、その際に使うモデルについて説明します。



説明に使うアプリは前の章でつくったものを引き続き使います。


== データの永続化


コード中で変数に代入したデータは、変数の有効範囲（スコープと言います）が終わると消えてしまいます。以下のコードで説明しましょう。


//emlist[][ruby]{
def print_hello_world
  x = "Hello world!"
  puts x
end
//}


変数xの有効範囲（スコープ）は、そのメソッドの中だけです（このような変数をローカル変数と呼びます）。この場合、メソッド @<tt>{print_hello_world}の実行が終わると変数xと、それが指すオブジェクトは消えてしまいます。



別の種類の変数として、前の章でも出てきたインスタンス変数（@はじまりの変数）があります。インスタンス変数は、インスタンスオブジェクトがなくなると一緒に消えます。Railsの場合は、1つのリクエスト内が有効範囲だと考えることができます（ここではおおまかに、ブラウザでのあるページを表示するのが1回のリクエストだと考えて差し支えありません。ですので、別のページを表示したり、リロードを行ったりすると、また新しい別のリクエストになります）。@bookのようなインスタンス変数に格納すると、コントローラからビューまで使うことができますが、その後なくなります。



それでも、つくったRailsアプリは別のリクエストでも情報が見れますよね？　新規入力画面で情報を入力して一度登録してしまえば、その後ブラウザから何回アクセスしても、たとえば一覧画面で何回リロードしても表示されます。



つまり、複数のリクエストに渡ってデータが保存されていることが分かります。これはインスタンス変数では実現できません。データがずっと残っているのは「データを保存する」仕事をしている「何かの仕組み」があるからなのです。



その仕組みがこの章の主役、モデル（Model）です。



//image[overview][モデル]{
//}




この章はモデルについて説明します。また、この章でCRUDのcreateの部分を題材に説明します（前の章の続きになります）。



//image[crud-create][この章の題材]{
//}




コードはこの部分です。



//image[create-overview][BooksController create アクション]{
//}




モデルに関する部分はここです。



//image[create-model][モデルを使っている箇所]{
//}




では、モデルの仕事について見ていきましょう。


== モデルの基本的な使い方　その1　保存


モデルを使うとデータを保存することができます。以下の2つの手順を踏むことで保存できます。


//emlist[][ruby]{
book = Book.new(title: "ハチミツとクローバー", memo: "美大を舞台にした青春ラブコメ")
//}


Book.newでBookモデルオブジェクトを作ります。このとき、タイトルとメモの情報を渡すことができます。



なお、モデル名（モデルのクラス名）は英語の単数形、大文字始まりにするルールがあります。ここではBookがモデル名で、単数形で大文字始まりになっています。また、すべて小文字のbookは変数名で、1つのBookモデルオブジェクトが代入されるため単数形を使います。


//emlist[][ruby]{
book.save
//}


Bookモデルオブジェクトのsaveメソッドを呼ぶと保存できます。


== モデルの基本的な使い方　その2　読み込み


さきほど保存したデータを読み込んでみましょう。


//emlist[][ruby]{
books = Book.all.to_a
//}


Book.allで保存されているBookモデルの全データを取得できます。以前に説明した一覧画面（indexアクション）でこのメソッドが使われています。



@<tt>{Book.all.to_a}でArrayにBookオブジェクトが詰まって返ってきます。@<tt>{to_a}はArrayオブジェクトへ変換するメソッドです。代入される変数名は小文字のbooksで、複数のBookオブジェクトが代入されるので複数形を使います。


== モデルの基本的な使い方　その3　検索

//emlist[][ruby]{
book = Book.where(title: "ハチミツとクローバー").first
book.title #=> "ハチミツとクローバー"
book.memo #=> "美大を舞台にした青春ラブコメ"
//}


whereメソッドを使うと検索ができます。タイトルが"ハチミツとクローバー"であるBookオブジェクトが返ります。検索結果が複数になることもあるので、firstメソッドで最初の1つを取得しています（1つなので、変数名bookは単数形になっています）。



取得したBookオブジェクトはtitleメソッドでタイトルを、memoメソッドでメモをそれぞれ返します。


== 実習 : rails consoleでモデルを使う


Railsには "rails cosole" という、Rubyでいうirbのような、1行ずつコードを実行する機能があります。前準備でつくったアプリへ移動して、rails consoleを使ってみましょう。ターミナルで@<tt>{rails c}と実行してみてください（cはconsoleの頭文字です）。


//cmd{
cd books_app
rails c
//}

//cmd{
Running via Spring preloader in process 53813
Loading development environment (Rails 5.0.0)
irb(main):001:0> #ここにコードを入力します
//}


以下のコードを実行してみてください。


//emlist[][ruby]{
book = Book.new(title: "some title", memo: "some memo") # モデルオブジェクト作成
book.save # 保存
Book.last # 上で保存したデータの表示
//}


前に出てきたwhereでの検索も試してみてください。rails consoleを終了するときはexitと打ってください。



また、rails consoleで保存したデータは、ブラウザで保存したデータと同じ場所に格納され、同じように取り扱われます。ここで保存したデータはブラウザからも見ることができます。


//emlist[][ruby]{
rails s
//}


ブラウザで http://localhost:3000/books へアクセスしてみましょう。


== モデルの仕組み


次は、モデルのコードを見て、モデルの仕組みを解説していきます。モデルのコードはapp/models/以下にあります。Bookモデルのコード @<tt>{app/models/book.rb} を見てみましょう。


//emlist[][ruby]{
class Book < ApplicationRecord
end
//}


Bookモデルにはコードがほとんどありません。



では、saveやallといったメソッドが使えるのはなぜでしょうか？　また、titleやmemoといった要素があることをどこで知るのでしょうか？


=== 問 : saveやallといったメソッドが使えるのはなぜでしょうか？


答えは @<tt>{ApplicationRecord} クラスを継承しているからです。 @<tt>{ApplicationRecord} クラスがモデルの仕事に必要な機能を持っています。それを継承しているBookクラスも同じ機能を持ちます。@<fn>{1}


=== 問 : titleやmemoといった要素があることをどこで知るのでしょうか？


答えは「データベースから情報を得る」です。



ApplicationRecordはデータベースから情報を得て、Bookモデルにtitle、memoという要素があることを知っています（book.titleやbook.memoというメソッドを提供します）。



では、データベースとは何でしょうか？


=== データベースとは？


データベースとは、データを保存したり、読み出したり、検索したりするために特化したプログラムです。



モデルはDBを便利につかうための仕組みでもあります。DBは高機能で堅牢でかつ高速です。しかし、DBへアクセスするには一般に専用の言語（SQLと言います）を用いることが多く、Rubyのコードからは扱いづらい面もあります。モデルはRubyでDBを容易に扱うことができる機能も提供します。



//image[db][データベースとは？]{
//}




では、DBはいつのまに作られたのでしょう？


== データベースはいつ作られたのか？


books appを作る一連のコマンドを入力した際に、以下のコマンドでDBを作成していました@<fn>{2}。


//cmd{
rails g scaffold book title:string memo:text
rails db:migrate
//}


scaffoldコマンドはいろいろなものを作りますが、その1つとしてDBの設計図をつくります。



//image[making_in_scaffold][scaffoldコマンドで作られたDB関連のファイル]{
//}




そして作られた設計図を使い、rails db:migrateコマンドでDBを作ります。では、次は設計図であるmigrationファイルを見ていきましょう。


== DB設計図 - migration


DBの設計図をマイグレーション（migration）ファイルと呼びます。マイグレーションファイルもRails（Ruby）のコードで書かれています。



では、マイグレーションファイルを見てみましょう。



@<tt>{db/migrate/20160214232240_create_books.rb}


//emlist[][ruby]{
class CreateBooks < ActiveRecord::Migration[5.0]
  def change
    create_table :books do |t|
      t.string :title
      t.text :memo

      t.timestamps
    end
  end
end
//}


3行目の @<tt>{create_table :books} でbooksという名前のテーブルを作ります。DBはテーブルという単位でデータを管理します。このアプリの、本に関するデータを保存するために、booksという名前のテーブルを作っています。テーブル名はモデル名の複数形にするというルールがあります。



4行目と5行目はテーブルの要素を作成しています。booksテーブルはtitleという要素と、memoという要素を持ちます（この要素のことをDBの用語でカラムといいます）。stringはデータの型の1つです。文字列を格納します。textもデータの型の1つで（stringよりも多く）文字列を格納します。



それに続く @<tt>{t.timestamps} は、@<tt>{created_at}（作成日時）、@<tt>{updated_at}（更新日時）を記録するカラムを作ります。



DBのテーブルはExcelをイメージすると分かり易いです。



//image[migration_excel][booksテーブルのイメージ]{
//}




DBへデータを格納していくことは、title、memoといった列があるExcelのシートに1行ずつデータを格納していくイメージです。



ところで、 @<tt>{t.string :title} や @<tt>{t.text :memo} に見覚えがありませんか？



実はscaffoldで指定していたのはこの部分です。



//image[migration_scaffold_explain][scaffoldの説明]{
//}




scaffoldで指定していたのはテーブル名とカラム、データの型でした。stringはデータの型です。文字列を格納できます。
textもデータの型で（stringよりも多く）文字列を格納できます。



ここまでで、scaffoldはDB設計図（migration）を作ることを説明しました。



//image[migration_summary][scaffold は migration を作る]{
//}




では、migrationから実際にDBを作るにはどうすれば良いでしょうか？



//image[migration_how_to_make_db][migrationからDBを作るには？]{
//}




DB設計図（migration）からDBを作るのが @<tt>{rails db:migrate} コマンドです。



//image[migration_rails_db_migrate][rails db migrate コマンドがmigrationからDBを作る]{
//}



== 保存したあとの処理


では、コントローラの処理の話に戻りましょう。@<tt>{@book.save} した後の動作を見て行きます。以下の2.本のデータを保存する処理のあと、保存の結果が成功か失敗かによって処理が分岐します。成功した場合は3a. show画面へ、失敗した場合は3b. 失敗したらnew画面へ分岐します。



//image[create-overview_2][BooksController create アクション]{
//}




プログラムが少し長いので、着目するところだけ残して短くしましょう。まず、@<tt>{respond_to do |format|}はリクエストされたレスポンスの形式によって分岐させる文です。ブラウザでnew画面に内容を入力してリクエストを飛ばした場合は@<tt>{format.html}が選ばれます（もう一方のjsonはデータ形式の1つで、たとえばスマートフォンアプリ開発時など、ブラウザ以外で表示させる場合に利用されます）。formatに関する処理を除くと以下のようになります。


//emlist[][ruby]{
@book = Book.new(book_params)
if @book.save
  redirect_to @book, notice: 'Book was successfully created.'
else
  render :new
end
//}


@<tt>{@book.save} は成功するとtrue 、失敗するとfalseを返します。 @<tt>{@book.save} の前に書いてあるifは分岐のための命令です。ifのあとに続く文（ここでは @<tt>{@book.save}）がtrueのときはその後ろからelseの前までを、falseのときはelse以降endまでを実行します。



@<tt>{@book.save}に成功すると@<tt>{redirect_to @book, notice: 'Book was successfully created.'}が実行されます。保存した本の詳細ページ（BooksControllerのshowアクションになります）を表示します。redirect_toはリダイレクト（新たにリクエストを発行して画面遷移させる）指示で、ここではshowアクションへのリクエストが発生します。後ろのnotice部は画面に表示させる文を設定しています。



//image[redirect_to_show][リダイレクト後のshowアクション画面とnoticeの表示]{
//}




@<tt>{@book.save}に失敗した場合はfalseを返すので、if文のelse節、@<tt>{render :new}が実行されます。renderはコントローラの次の処理であるビューを指定するための文です。ここでは@<tt>{app/views/books/new.html.erb}がビューとして使われ、新規入力画面（入力していたページです）が表示されます。



失敗する理由としてはDBへの接続エラーなどもありますが、モデルにある検証機能「バリデーション」を使うと想定外の入力に対して保存を失敗させることができます。たとえば、郵便番号入力欄に数字以外の文字が入力されるようなケースは、バリデーションを実装することで入力画面へ戻しユーザーに再入力を促すことができます。バリデーションについてはここでは説明しませんが、便利な機能なので @<href>{http://railsguides.jp/active_record_validations.html,Rails Guides : Active Record バリデーション} などの説明を参考に使ってみてください。


== まとめ

=== scaffoldで作られるmodel、migration


では、scaffoldで作られるmodel、migrationをまとめます。



//image[summary_scaffold_make_files][scaffoldコマンドがファイルを作る]{
//}




//image[summary_rake_db_migrate][rails db migrate コマンドがDBを作る]{
//}




//image[summary_model_db][model と DB でアプリは動く]{
//}



=== モデルの使い方

//emlist[][ruby]{
book = Book.new(title: "ハチミツとクローバー",
                memo: "美大を舞台にした青春ラブコメ")
//}


Book.newでBook Modelオブジェクトを作ります。モデル名は英語の単数形にするルールがあります。引数でtitle、modelといった各カラムのデータを渡せます。


//emlist[][ruby]{
book.save
//}


saveメソッドを呼ぶと保存できます。


//emlist[][ruby]{
books = Book.all.to_a
//}


Book.allでDBに保存されているBook Modelの全データを取得できます。Book.all.to_aを実行すると、ArrayにBookオブジェクトが詰まって返ってきます。


//emlist[][ruby]{
book = Book.where(title: "ハチミツとクローバー")
book.title #=> "ハチミツとクローバー"
book.memo #=> "美大を舞台にした青春ラブコメ"
//}


whereメソッドを使うと検索ができます。タイトルが"ハチミツとクローバー"であるBookオブジェクトが返ります。検索で取れたBookオブジェクトは、titleメソッドでタイトルを、memoメソッドでメモをそれぞれ取得できます。


=== ポイントまとめ


ポイントをまとめると以下のようになります。

 * DBはデータの保存、読み込み、検索に特化したプログラム
 * モデルはDBを便利に使うための道具。DBとモデルはセットで使われる
 * マイグレーション（migration）ファイルはDBを作るための設計図
 * rails db:migrateはマイグレーションファイルからDBを作るコマンド

== さらに学びたい場合は


モデルはとても多機能です。RailsGuidesにもたくさんの説明ページがあります。うまく使うことで便利な機能を簡単に作ることができるのです。

 * @<href>{http://railsguides.jp/active_record_basics.html,Rails Guides : Active Record の基礎}
 ** モデルに関する詳しい説明です。
 * @<href>{http://railsguides.jp/active_record_migrations.html,Rails Guides : Active Record マイグレーション}
 ** DBのマイグレーションに関する詳しい説明です。
 * @<href>{http://railsguides.jp/active_record_querying.html,Rails Guides : Active Record クエリインターフェイス}
 ** モデルの中で、検索に関する詳しい説明です。
 * @<href>{http://railsguides.jp/active_record_validations.html,Rails Guides : Active Record バリデーション}
 ** モデルには「バリデーション」と呼ばれる、便利な値のチェック機能がついています。実際のアプリを作る際によく使う機能なので、ぜひチャレンジしてみてください。
 * @<href>{http://railsguides.jp/association_basics.html,Rails Guides : Active Record の関連付け}
 ** 複数のモデルを結び付ける「関連付け」の機能は強力でアプリを作る際に大変便利です。ちょっととっつき難いですが、ぜひチャレンジしてみてください。

== 応用編：既存のDBテーブルにカラムを増やすには？


既存のDBテーブルにカラムを増やすにはどうすれば良いでしょうか？前に作ったmigrationファイルを編集してもうまくいきません。 migration各ファイルは1回だけ実行される仕組みなので、すでに存在しているmigrationファイルを変更しても、そのファイルは実行されないからです。そこで、新しいカラムを追加するには、新しいmigrationファイルを作ります。



rails gコマンドにmigrationを指定するとmigrationファイルだけを生成できます。たとえば、booksテーブルにstring型のauthorを加えるには以下のようにします。


//emlist[][bash]{
rails g migration AddAuthorToBooks author:string
//}

//cmd{
$ rails g migration AddAuthorToBooks author:string
      invoke  active_record
      create    db/migrate/20160215230716_add_author_to_books.rb
//}


rails g migrationコマンドの基本形は以下になります。


//quote{
$ rails g migration Addカラム名Toテーブル名 カラム名:型名

//}


作成されたmigrationファイルは以下のようになっています。


//emlist{
20160215230716_add_author_to_books.rb
//}

//emlist[][ruby]{
class AddAuthorToBooks < ActiveRecord::Migration[5.0]
  def change
    add_column :books, :author, :string
  end
end
//}


生成されたmigrationファイルには、booksテーブルへauthorカラムをstring型で追加する指示が書かれています。



migrationファイルを作成したら、@<tt>{rails db:migrate}コマンドでDBへ内容を反映します。


//emlist[][bash]{
$ rails db:migrate
//}

//cmd{
== 20160215230716 AddAuthorToBooks: migrating =================================
-- add_column(:books, :author, :string)
   -> 0.0039s
== 20160215230716 AddAuthorToBooks: migrated (0.0040s) ========================
//}


これで、DBのbooksテーブルへauthorカラムが追加されました。



ここまでの作業をまとめると、以下のようになります。



//image[migration_new_column_author][booksテーブルにstring型のauthorを加えるmigration]{
//}




ちなみに、Railsのgenerate機能は開発をアシストする機能なので、使わないで0から手でコードを書いても同様に動きます。rails gを使ってファイルを作っても、0から手でコードを書いても同じ結果になります。以下の図を参考にしてください。



//image[migration_generate_or_write][generateしても、0から書いても良い]{
//}



== 応用編：新しいモデルとmigrationを一緒に作るには？


rails gコマンドにmodelを指定するとmodelとmigrationを生成できます。


//emlist[][ruby]{
rails g model book title:string memo:text
//}

//cmd{
db/migrate/20160216060032_create_books.rb
app/models/book.rb
//}

== 応用編：rails gコマンドまとめ


rails gコマンドの一覧をまとめます。



migration


//emlist[][bash]{
$ rails g migration AddAuthorToBooks author:string
//}


model + migration


//emlist[][bash]{
$ rails g model book title:string memo:text
//}


routes + controller + view


//emlist[][bash]{
$ rails g controller books index
//}


scaffold = model + migration + routes + controller + view


//emlist[][bash]{
$ rails g scaffold book title:string memo:text
//}

== 応用編：scaffoldでつくったMigration、Model、Controllerへカラムを追加するには？


すでにあるbooksテーブルにstring型のauthorを加えて、ブラウザから入力できるようにしてみましょう。


=== booksテーブルにstring型のauthorを加える

//emlist[][bash]{
$ rails g migration AddAuthorToBooks author:string
//}

//cmd{
$ rails g migration AddAuthorToBooks author:string
      invoke  active_record
      create    db/migrate/20160215230716_add_author_to_books.rb
//}


作成されたファイルは以下のようになっています。



@<tt>{db/migrate/20160215230716_add_author_to_books.rb}


//emlist[][ruby]{
class AddAuthorToBooks < ActiveRecord::Migration[5.0]
  def change
    add_column :books, :author, :string
  end
end
//}

=== migrationからDBを作る

//emlist[][bash]{
$ rails db:migrate
//}

//cmd{
== 20160215230716 AddAuthorToBooks: migrating =================================
-- add_column(:books, :author, :string)
   -> 0.0039s
== 20160215230716 AddAuthorToBooks: migrated (0.0040s) ========================
//}

=== viewを修正

==== フォームパーシャル


@<tt>{app/views/books/_form.html.erb}


//emlist[][diff]{
<%= form_for(book) do |f| %>
...
  <div class="field">
    <%= f.label :title %>
    <%= f.text_field :title %>
  </div>

  <div class="field">
    <%= f.label :memo %>
    <%= f.text_area :memo %>
  </div>

+  <div class="field">
+    <%= f.label :author %><br>
+    <%= f.text_field :author %>
+  </div>

  <div class="actions">
    <%= f.submit %>
  </div>
<% end %>
//}

==== 詳細表示画面


@<tt>{app/views/books/show.html.erb}


//emlist[][diff]{
<p id="notice"><%= notice %></p>

<p>
  <strong>Title:</strong>
  <%= @book.title %>
</p>

<p>
  <strong>Memo:</strong>
  <%= @book.memo %>
</p>

+<p>
+  <strong>Author:</strong>
+  <%= @book.author %>
+</p>

<%= link_to 'Edit', edit_book_path(@book) %> |
<%= link_to 'Back', books_path %>
//}

==== 一覧表示画面


@<tt>{app/views/books/index.html.erb}


//emlist[][diff]{
<p id="notice"><%= notice %></p>

<h1>Books</h1>

<table>
  <thead>
    <tr>
      <th>Title</th>
      <th>Memo</th>
+      <th>Author</th>
      <th colspan="3"></th>
    </tr>
  </thead>

  <tbody>
    <% @books.each do |book| %>
      <tr>
        <td><%= book.title %></td>
        <td><%= book.memo %></td>
+        <td><%= book.author %></td>
        <td><%= link_to 'Show', book %></td>
        <td><%= link_to 'Edit', edit_book_path(book) %></td>
        <td><%= link_to 'Destroy', book, method: :delete, data: { confirm: 'Are you sure?' } %></td>
      </tr>
    <% end %>
  </tbody>
</table>

<br>

<%= link_to 'New Book', new_book_path %>
//}

=== controllerを修正


@<tt>{app/controllers/books_controller.rb}


//emlist[][diff]{
class BooksController < ApplicationController
...
    # Never trust parameters from the scary internet, only allow the white list through.
    def book_params
-      params.require(:book).permit(:title, :memo)
+      params.require(:book).permit(:title, :memo, :author)
    end
end
//}

=== 動作確認


//image[add_author_new][新規入力画面]{
//}




//image[add_author_show][詳細画面]{
//}




//image[add_author_index][一覧画面]{
//}




各画面にAuthor欄が追加されて、登録できるようになりました。


//footnote[1][Rails 4.2の場合、@<tt>{ApplicationRecord}の替わりに@<tt>{ActiveRecord::Base}が使われていますが、考え方は同じです。]

//footnote[2][Rails4.2以前では @<tt>{rails db:migrate} の替わりに @<tt>{bin/rake db:migrate} となります。]
