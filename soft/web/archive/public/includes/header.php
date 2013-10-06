<!DOCTYPE html>
<!--[if IE 8]> 				 <html class="no-js lt-ie9" lang="en"> <![endif]-->
<!--[if gt IE 8]><!--> <html class="no-js" lang="en"> <!--<![endif]-->

<?php
if ( !isset($path) ) {
	$path = "./";
}

$sitename = 'draw_bot';
$tagline = 'a modular computer controlled drawing platform';
if ( isset($pagetitle) ) {
	// Subpages:
	$pagetitle = $pagetitle . ' &middot; ' . $sitename;
	// • &bull; ‹ &lsaquo; · &middot; – &ndash;
} else {
	// Homepage:
	$pagetitle = $sitename . ': ' . $tagline;
}
?>

<head>
	<meta charset="utf-8" />
  <meta name="viewport" content="width=device-width" />
  
  <!-- Google Meta Tag Boilerplate: http://support.google.com/webmasters/bin/answer.py?hl=en&answer=79812 -->
  <!-- Important for Google snippet -->
  <meta name="description" content="A modular internet based computer controlled drawing platform." />
  <meta name="author"        content="Corey H. Walsh" />
  <meta name="publisher"     content="Corey H. Walsh" />
  <meta name="copyright"     content="2013 Corey H. Walsh" />
  <!-- Enable Google Chrome Frame -->
  <!-- We can also use X-UA-Compatible to force IE to render as an older version of IE -->
  <meta http-equiv="X-UA-Compatible" content="chrome=1" /> 
  <meta charset="utf-8">
  <meta http-equiv="content-type"    content="text/html; charset=utf-8" />
  <!-- Ask search engines to not cache -->
<!--  <meta http-equiv="cache-control"   content="no-cache" />-->
  <meta name="language"      content="english" />
  <meta name="distribution"  content="global" />
  <!-- Robots tag, default is "index, follow".  Options: index, noindex, follow, nofollow -->
  <!-- "index" allows indexing.  "follow" allows following links to other pages on your site -->
  <!-- http://www.robotstxt.org/meta.html -->
<!--  <meta name="robots"        content="index, follow" />-->
  <meta name="revisit-after" content="2 days" />
<!--  <meta name="fb:app_id"     content="" />-->
  <!-- Canonical Link.  If you have deep links with mostly duplicated content, Google can penalize you for duplicate content. Provide a canonical link with stripped customizations (ie. &color=red). http://davidwalsh.name/canonical-link-rel -->
  <!-- <link rel="canonical" href="" /> -->
  
  <!-- Open Graph Boilerplate: http://ogp.me/ -->
  <!-- Four Required Properties: -->
  <meta property="og:title" content="<?php echo $pagetitle ?>"/>
  <meta property="og:type" content="website"/>
  <!-- Image when shared. Square, JPG/PNG, 50x50px minimum. -->
  <!-- <meta property="og:image" content="http://designemcee.com/apple-touch-icon-144x144-precomposed.png"/> -->
  <!-- Canonical Link -->
  <meta property="og:url" content="">
  <!-- Optional Properties: -->
  <!-- <meta property="og:site_name" content="<?php echo $sitename ?>"/> -->
  <!-- <meta property="og:description" content="" /> -->
  
  
  <title><?php echo $pagetitle ?></title>

  <link rel="stylesheet" href="<?php echo $path ?>css/normalize.css" />
  
  <link rel="stylesheet" href="<?php echo $path ?>css/app.css" />

  <link rel="shortcut icon" href="http://hazelnutdev.com/favicon.ico">

<!--  <script src="<?php echo $path ?>js/vendor/custom.modernizr.js"></script>-->
  	<!-- css transforms -->
	<script src="<?php echo $path ?>js/modernizr.custom.37575.js"></script>

 <script>
//   (function(i,s,o,g,r,a,m){i['GoogleAnalyticsObject']=r;i[r]=i[r]||function(){
//   (i[r].q=i[r].q||[]).push(arguments)},i[r].l=1*new Date();a=s.createElement(o),
//   m=s.getElementsByTagName(o)[0];a.async=1;a.src=g;m.parentNode.insertBefore(a,m)
//   })(window,document,'script','//www.google-analytics.com/analytics.js','ga');

//   ga('create', 'UA-42462015-1', 'hzldv.com');
//   ga('send', 'pageview');

 </script>

  
</head>
<body>

	<div id="container" class=
		<?php
			echo '"';
			if ( isset($page_class) ) {
				echo $page_class . ' ';
			}
			echo '"';
		?>
	
	>
