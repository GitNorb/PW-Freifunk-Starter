<?php

if(!$useMain) return;

// Set Hompage to use in Theme
$homepage = $pages->get('/');

// Set settings to use in Theme
$settings = $page->get('template=site-setting');

// determine what the ever important browser <title> tag should be
if($page->brower_title) $browserTitle = $page->browser_title;
  else if($page === $homepage) $browserTitle = $page->headline;
  else $browserTitle = $page->title . '&bull;' . $homepage->headline;

// add our stylesheet
$config->styles->add($config->urls->templates.'css/app.css');

// add our javascripts
$config->scripts->add($config->urls->templates.'js/app-dist.js');

/********************************
* Hendle Login
*******************************/
if(!wire('user')->isLoggedin()){
	if($input->post->user && $input->post->pass) {
		$u = $sanitizer->username($input->post->user);
		$pass = $input->post->pass;

		if($session->login($u, $pass)) {
			// login successful
			if($session->redirectUrl){
        $session->redirect($session->redirectUrl, false);
        $session->remove('redirectUrl');
      } else {
			   $session->redirect($page->path, false);
       }
		}  else {
			$session->login_error = '<strong>Login fehlgeschlagen!</strong> Bitte versuche es noch einmal oder benutze die \'Passwort vergessen\' Funktion.';
		}
	}
}

?>

<!doctype html>
<html class="no-js" lang="de">
<head>

  <style>
    html,
    body {
      height: 100%;
    }

    *,
    *:before,
    *:after {
      -webkit-box-sizing: border-box;
      -moz-box-sizing: border-box;
      box-sizing: border-box;
    }

    html,
    body {
      font-size: 100%;
    }

    body {
      background: #fff;
      color: #222;
      font-family: "Helvetica Neue",Helvetica,Roboto,Arial,sans-serif;
      font-style: normal;
      font-weight: normal;
      line-height: 1.5;
      margin: 0;
      padding: 0;
      position: relative;
    }

    img {
      max-width: 100%;
      height: auto;
    }

    img {
      -ms-interpolation-mode: bicubic;
    }

    .right {
      float: right !important;
    }

    img {
      display: inline-block;
      vertical-align: middle;
    }

    .row {
      margin: 0 auto;
      max-width: 73.125rem;
      width: 100%;
    }

    .row:before,
    .row:after {
      content: " ";
      display: table;
    }

    .row:after {
      clear: both;
    }

    .columns {
      padding-left: .9375rem;
      padding-right: .9375rem;
      width: 100%;
      float: left;
    }

    @media only screen and (min-width: 40.0625em) {
      .columns {
        position: relative;
        padding-left: .9375rem;
        padding-right: .9375rem;
        float: left;
      }

      .medium-7 {
        width: 58.33333%;
      }

      .columns.medium-centered {
        margin-left: auto;
        margin-right: auto;
        float: none;
      }

      .columns.medium-centered:last-child {
        float: none;
      }
    }

    @media only screen and (min-width: 64.0625em) {
      .columns {
        position: relative;
        padding-left: .9375rem;
        padding-right: .9375rem;
        float: left;
      }

      .large-7 {
        width: 58.33333%;
      }

      .large-12 {
        width: 100%;
      }

      .columns.large-centered {
        margin-left: auto;
        margin-right: auto;
        float: none;
      }

      .columns.large-centered:last-child {
        float: none;
      }
    }

    button {
      -webkit-appearance: none;
      -moz-appearance: none;
      border-radius: 0;
      border-style: solid;
      border-width: 0;
      font-family: "Helvetica Neue",Helvetica,Roboto,Arial,sans-serif;
      font-weight: normal;
      line-height: normal;
      margin: 0 0 1.25rem;
      position: relative;
      text-align: center;
      text-decoration: none;
      display: inline-block;
      padding: 1rem 2rem 1.0625rem 2rem;
      font-size: 1rem;
      background-color: #009ee0;
      border-color: #007eb3;
      color: #fff;
    }

    button::-moz-focus-inner {
      border: 0;
      padding: 0;
    }

    @media only screen and (min-width: 40.0625em) {
      button {
        display: inline-block;
      }
    }

    .f-dropdown {
      display: none;
      left: -9999px;
      list-style: none;
      margin-left: 0;
      position: absolute;
      background: #fff;
      border: solid 1px #ccc;
      font-size: .875rem;
      height: auto;
      max-height: none;
      width: 100%;
      z-index: 89;
      margin-top: 2px;
      max-width: 200px;
    }

    .f-dropdown>*:first-child {
      margin-top: 0;
    }

    .f-dropdown>*:last-child {
      margin-bottom: 0;
    }

    .f-dropdown:before {
      border: inset 6px;
      content: "";
      display: block;
      height: 0;
      width: 0;
      border-color: transparent transparent #fff transparent;
      border-bottom-style: solid;
      position: absolute;
      top: -12px;
      left: 10px;
      z-index: 89;
    }

    .f-dropdown:after {
      border: inset 7px;
      content: "";
      display: block;
      height: 0;
      width: 0;
      border-color: transparent transparent #ccc transparent;
      border-bottom-style: solid;
      position: absolute;
      top: -14px;
      left: 9px;
      z-index: 88;
    }

    .f-dropdown.content {
      display: none;
      left: -9999px;
      list-style: none;
      margin-left: 0;
      position: absolute;
      background: #fff;
      border: solid 1px #ccc;
      font-size: .875rem;
      height: auto;
      max-height: none;
      padding: 1.25rem;
      width: 100%;
      z-index: 89;
      max-width: 200px;
    }

    .f-dropdown.content>*:first-child {
      margin-top: 0;
    }

    .f-dropdown.content>*:last-child {
      margin-bottom: 0;
    }

    .f-dropdown.small {
      max-width: 300px;
    }

    form {
      margin: 0 0 1rem;
    }

    input[type="text"],
    input[type="password"] {
      -webkit-appearance: none;
      -moz-appearance: none;
      border-radius: 0;
      background-color: #fff;
      border-style: solid;
      border-width: 1px;
      border-color: #ccc;
      box-shadow: inset 0 1px 2px rgba(0,0,0,0.1);
      color: rgba(0,0,0,0.75);
      display: block;
      font-family: inherit;
      font-size: .875rem;
      height: 2.3125rem;
      margin: 0 0 1rem 0;
      padding: .5rem;
      width: 100%;
      -webkit-box-sizing: border-box;
      -moz-box-sizing: border-box;
      box-sizing: border-box;
    }

    ::-webkit-input-placeholder {
      color: #666;
    }

    :-moz-placeholder {
      color: #666;
    }

    ::-moz-placeholder {
      color: #666;
    }

    :-ms-input-placeholder {
      color: #666;
    }

    [data-magellan-expedition] {
      background: #fff;
      min-width: 100%;
      padding: 10px;
      z-index: 50;
    }

    [data-magellan-expedition] .sub-nav {
      margin-bottom: 0;
    }

    [data-magellan-expedition] .sub-nav dd {
      margin-bottom: 0;
    }

    [data-magellan-expedition] .sub-nav a {
      line-height: 1.8em;
    }

    .sub-nav {
      display: block;
      margin: -.25rem 0 1.125rem;
      overflow: hidden;
      padding-top: .25rem;
      width: auto;
    }

    .sub-nav dd {
      color: #999;
      float: left;
      font-family: "Helvetica Neue",Helvetica,Roboto,Arial,sans-serif;
      font-size: .875rem;
      font-weight: normal;
      margin-left: 1rem;
      margin-bottom: 0;
    }

    .sub-nav dd a {
      color: #999;
      padding: .1875rem 1rem;
      text-decoration: none;
    }

    .contain-to-grid {
      width: 100%;
      background: #dc0067;
    }

    .contain-to-grid .top-bar {
      margin-bottom: 0;
    }

    .fixed {
      position: fixed;
      top: 0;
      width: 100%;
      z-index: 99;
      left: 0;
    }

    .top-bar {
      background: #dc0067;
      height: 2.8125rem;
      line-height: 2.8125rem;
      margin-bottom: 0;
      overflow: hidden;
      position: relative;
    }

    .top-bar ul {
      list-style: none;
      margin-bottom: 0;
    }

    .top-bar .title-area {
      margin: 0;
      position: relative;
    }

    .top-bar .name {
      font-size: 16px;
      height: 2.8125rem;
      margin: 0;
    }

    .top-bar .name h2 {
      font-size: 1.125rem;
      line-height: 2.8125rem;
      margin: 0;
    }

    .top-bar .name h2 a {
      color: #fff;
      display: block;
      font-weight: bold;
      padding: 0 .9375rem;
      width: 75%;
    }

    .top-bar .toggle-topbar {
      position: absolute;
      right: 0;
      top: 0;
    }

    .top-bar .toggle-topbar a {
      color: #fff;
      display: block;
      font-size: .8125rem;
      font-weight: bold;
      height: 2.8125rem;
      line-height: 2.8125rem;
      padding: 0 .9375rem;
      position: relative;
      text-transform: uppercase;
    }

    .top-bar .toggle-topbar.menu-icon {
      margin-top: -16px;
      top: 50%;
    }

    .top-bar .toggle-topbar.menu-icon a {
      color: #fff;
      height: 34px;
      line-height: 33px;
      padding: 0 2.5rem 0 .9375rem;
      position: relative;
    }

    .top-bar .toggle-topbar.menu-icon a span::after {
      content: "";
      display: block;
      height: 0;
      position: absolute;
      margin-top: -8px;
      top: 50%;
      right: .9375rem;
      box-shadow: 0 0 0 1px #fff,0 7px 0 1px #fff,0 14px 0 1px #fff;
      width: 16px;
    }

    .top-bar-section {
      left: 0;
      position: relative;
      width: auto;
    }

    .top-bar-section ul {
      display: block;
      font-size: 16px;
      height: auto;
      margin: 0;
      padding: 0;
      width: 100%;
    }

    .top-bar-section ul li {
      background: #dc0067;
    }

    .top-bar-section ul li>a {
      color: #fff;
      display: block;
      font-family: "Helvetica Neue",Helvetica,Roboto,Arial,sans-serif;
      font-size: .8125rem;
      font-weight: bold;
      padding-left: .9375rem;
      padding: 12px 0 12px .9375rem;
      text-transform: none;
      width: 100%;
    }

    .top-bar-section ul li.active>a {
      background: #fed136;
      color: #fff;
    }

    .top-bar-section .has-dropdown {
      position: relative;
    }

    .top-bar-section .has-dropdown>a:after {
      border: inset 5px;
      content: "";
      display: block;
      height: 0;
      width: 0;
      border-color: transparent transparent transparent rgba(255,255,255,0.4);
      border-left-style: solid;
      margin-right: .9375rem;
      margin-top: -4.5px;
      position: absolute;
      top: 50%;
      right: 0;
    }

    .top-bar-section .dropdown {
      clip: rect(1px, 1px, 1px, 1px);
      height: 1px;
      overflow: hidden;
      position: absolute !important;
      width: 1px;
      display: block;
      padding: 0;
      position: absolute;
      top: 0;
      z-index: 99;
      left: 100%;
    }

    .top-bar-section .dropdown li {
      height: auto;
      width: 100%;
    }

    .top-bar-section .dropdown li a {
      font-weight: normal;
      padding: 8px .9375rem;
    }

    @media only screen and (min-width: 40.0625em) {
      .top-bar {
        background: #dc0067;
        overflow: visible;
      }

      .top-bar:before,
      .top-bar:after {
        content: " ";
        display: table;
      }

      .top-bar:after {
        clear: both;
      }

      .top-bar .toggle-topbar {
        display: none;
      }

      .top-bar .title-area {
        float: left;
      }

      .top-bar .name h2 a {
        width: auto;
      }

      .contain-to-grid .top-bar {
        margin: 0 auto;
        margin-bottom: 0;
        max-width: 73.125rem;
      }

      .top-bar-section {
        left: 0 !important;
      }

      .top-bar-section ul {
        display: inline;
        height: auto !important;
        width: auto;
      }

      .top-bar-section ul li {
        float: left;
      }

      .top-bar-section li:not(.has-form) a:not(.button) {
        background: #dc0067;
        line-height: 2.8125rem;
        padding: 0 .9375rem;
      }

      .top-bar-section li.active:not(.has-form) a:not(.button) {
        background: #fed136;
        color: #fff;
        line-height: 2.8125rem;
        padding: 0 .9375rem;
      }

      .top-bar-section .has-dropdown>a {
        padding-right: 2.1875rem !important;
      }

      .top-bar-section .has-dropdown>a:after {
        border: inset 5px;
        content: "";
        display: block;
        height: 0;
        width: 0;
        border-color: rgba(255,255,255,0.4) transparent transparent transparent;
        border-top-style: solid;
        margin-top: -2.5px;
        top: 1.40625rem;
      }

      .top-bar-section .dropdown {
        left: 0;
        background: transparent;
        min-width: 100%;
        top: auto;
      }

      .top-bar-section .dropdown li a {
        background: #dc0067;
        color: #fff;
        line-height: 2.8125rem;
        padding: 12px .9375rem;
        white-space: nowrap;
      }

      .top-bar-section .dropdown li:not(.has-form):not(.active)>a:not(.button) {
        background: #dc0067;
        color: #fff;
      }

      .top-bar-section .right li .dropdown {
        left: auto;
        right: 0;
      }
    }

    .text-center {
      text-align: center !important;
    }

    div,
    dl,
    dd,
    ul,
    li,
    h2,
    form {
      margin: 0;
      padding: 0;
    }

    a {
      color: #008CBA;
      line-height: inherit;
      text-decoration: none;
    }

    a img {
      border: none;
    }

    h2 {
      color: #222;
      font-family: "Helvetica Neue",Helvetica,Roboto,Arial,sans-serif;
      font-style: normal;
      font-weight: normal;
      line-height: 1.4;
      margin-bottom: .5rem;
      margin-top: .2rem;
      text-rendering: optimizeLegibility;
    }

    h2 {
      font-size: 1.6875rem;
    }

    ul,
    dl {
      font-family: inherit;
      font-size: 1rem;
      line-height: 1.6;
      list-style-position: outside;
      margin-bottom: 1.25rem;
    }

    ul {
      margin-left: 1.1rem;
    }

    ul li ul {
      margin-left: 1.25rem;
      margin-bottom: 0;
    }

    dl dd {
      margin-bottom: .75rem;
    }

    @media only screen and (min-width: 40.0625em) {
      h2 {
        line-height: 1.4;
      }

      h2 {
        font-size: 2.3125rem;
      }
    }

    .second-nav {
      margin-top: 2.8125rem;
      z-index: 89 !important;
    }

    #slider img {
      min-width: 100%;
    }

    .container {
      padding-top: 2.8125rem;
    }

    .slider-image {
      position: relative;
      width: 100%;
      text-align: center;
    }

    .slider-image h2 {
      position: absolute;
      bottom: 30%;
      width: 100%;
    }

    .slider-image h2 span {
      color: white;
      letter-spacing: -1px;
      padding: 10px;
      background: #000;
      background: rgba(0,0,0,0.7);
    }

    .img-responsive {
      display: block;
      max-width: 100%;
      height: auto;
    }
  </style>
  <link rel="icon" type="image/png" href='<?= $config->urls->templates. 'img/favicon.png' ?>'>
  <meta charset="utf-8" />
  <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0">

</head>
<body>
  <header id="header" class="fixed contain-to-grid">
    <?php include_once('_nav.inc'); ?>
  </header><!-- #sticky -->

  <?php if($page->id != 1){ ?>
  <div class="contain-breadcrumbs">
    <ul class="breadcrumbs">
      <?php
        foreach($page->parents("template!=home")->append($page) as $parent) {
            echo ($page->id === $parent->id ? "<li class='current'><a href='{$parent->url}'>{$parent->title}</a></li>" : "<li><a href='{$parent->url}'>{$parent->title}</a></li>");
        }
        ?>
    </ul>
  </div>
  <?php } ?>

  <section id="container" class="<?php echo $page->template .' id-'. $id; ?>">
    <?php
      if($input->post->user && $input->post->pass) {
        echo "<div class='alert-box warning' data-alert>" . $session->login_error . "<a href='#' class='close'>&times;</a></div>";
        }
      ?>
    <?php
    // Homepage (Landingpage) wird direkt im container
    echo ($page->id === 1 || $fullwidth == true ? $content :   '<div id="content" class="row">'.$content.'</div>');
    ?>
  </section>
<section>
</section>
  <footer id="footer" class="footer">
    <div class="row">
      <div class="small-12 medium-4 medium-push-8 columns">
        <ul class="inline-list social">
          <li><a href="https://twitter.com/freifunkmyk"><i class="fa fa-2x fa-twitter-square"></i></a></li>
          <li><a href="https://github.com/FreifunkMYK"><i class="fa fa-2x fa-github-square"></i></a></li>
          <li><a mailto="info@freifunk-myk.de"><i class="fa fa-2x fa-envelope"></i></a></li>
        </ul>
        <p class="copywrite">&copy; <?=date("Y")?> <?=$homepage->headline?></p>
      </div>
      <div class="small-12 medium-8 medium-pull-4 columns">
        <p>
          <?php //if($user->id == $page->createdUser->id){ echo "true";}?>
        </p>
        <ul class="inline-list">
          <li><a href="#">Home</a></li>
          <li><a href="#">Blog</a></li>
          <li><a href="#">About</a></li>
          <li><a href="#">Faq</a></li>
          <li><a href="#">Kontakt</a></li>
        </ul>
        <p class="copywrite">Erstellt mit <a href="http://de.processwire.com/">ProcessWire</a> und <a href="http://foundation.zurb.com/">Foundation Zurb</a>. Zu finden auf <a href="https://github.com/FreifunkMYK/PW-Freifunk-Starter">GitHub</a>.
      </div>
    </div>
    <div class="row">
      <div class="small-12 medium-2 medium-push-10 columns">
      </div>
      <div class="small-12 medium-10 medium-pull-2 columns">
      </div>
    </div>
  </footer>

  <?php
	 #if($modules->isInstalled("AllInOneMinify")){
      /*	if(false){
		foreach($config->scripts as $key => $file) $scriptfiles[] = str_replace($config->urls->templates, "", $file);
      	print_r($scriptfiles);?>
      		<script src="<?php echo AIOM::JS($scriptfiles); ?>"> </script><?php
    	} else {
      		// Include the style Files
      		foreach($config->scripts as $file) echo "\n\t<script src='$file'></script>";
    } */
  ?>

  <script type="text/javascript">
    (function() {
        var s = document.createElement('script');
        s.type = 'text/javascript';
        s.async = true;
        s.src = '<?php echo $config->urls->templates.'js/app-dist.js';?>';
        var x = document.getElementsByTagName('script')[0];
        x.parentNode.insertBefore(s, x);
    })();

    function loadCSS(href){
        var ss = window.document.createElement('link'),
            ref = window.document.getElementsByTagName('head')[0];

        ss.rel = 'stylesheet';
        ss.href = href;

        // temporarily, set media to something non-matching to ensure it'll
        // fetch without blocking render
        ss.media = 'only x';

        ref.parentNode.insertBefore(ss, ref);

        setTimeout( function(){
          // set media back to `all` so that the stylesheet applies once it loads
          ss.media = 'all';
        },0);
      }
    loadCSS('<?php echo $config->urls->templates.'css/app.css'; ?>');

    // Foundation JavaScript
  	// Documentation can be found at: http://foundation.zurb.com/docs
    $(document).foundation();
  </script>
  <noscript>
    <script src="<?php echo $config->urls->templates.'js/app-dist.js';?>"></script>
    <link rel="stylesheet" href="<?php echo $config->urls->templates.'css/app.css'; ?>">
  </noscript>
</body>
</html>
