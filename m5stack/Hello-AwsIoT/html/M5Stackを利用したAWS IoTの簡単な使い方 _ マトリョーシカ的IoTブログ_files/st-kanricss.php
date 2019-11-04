@charset "UTF-8";




.post h2,
.post h2 span,
.post h3,
.post h3 span,
.entry-title,
.post .entry-title {
	font-family: Helvetica , "游ゴシック" , "Yu Gothic" , sans-serif;
}




	/*アコーディオンメニュー追加ボタン2*/
	#s-navi dt.trigger .op-st2 {
		max-width:80%;
	}



/*media Queries タブレットサイズ（959px以下）
----------------------------------------------------*/
@media only screen and (max-width: 959px) {


}

/*media Queries タブレットサイズ（600px以上）
----------------------------------------------------*/
@media only screen and (min-width: 600px) {




	/*-- ここまで --*/
}

/*media Queries PCサイズ（960px以上）
----------------------------------------------------*/
@media only screen and (min-width: 960px) {

	/*--------------------------------
	全体のサイズ
	---------------------------------*/

	
	#st-menuwide, /*メニュー*/
	nav.smanone,
	nav.st5,
	#st-menuwide div.menu,
	#st-menuwide nav.menu,
	#st-header, /*ヘッダー*/
	#content, /*コンテンツ*/
	#footer-in /*フッター*/
	 { 
		max-width:1060px;
	}

	#headbox
	 { 
		max-width:1040px;
	}


	/*--------------------------------
	PCのレイアウト（右サイドバー）
	---------------------------------*/

	#contentInner {
		float: left;
		width: 100%;
		margin-right: -300px;
	}

	main {
		margin-right: 320px;
		margin-left: 0px;
		background-color: #fff;
		border-radius: 4px;
		-webkit-border-radius: 4px;
		-moz-border-radius: 4px;
		padding: 30px 50px 30px;
	}

	#side aside {
		float: right;
		width: 300px;
		padding: 0px;
	}



/**
 * サイト名とキャッチフレーズ有無の調整
 */



	#header-r .footermenust {
		margin: 0;
	}





	/*-- ここまで --*/
}
