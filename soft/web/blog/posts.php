<?php  
	$page_class = "blog";
	include "./includes/header.php";
	$js = './js/blog.js';
	// $path = "../"

	$link = $_GET["p"];

	if(!file_exists('./posts.json') ) {
		bail();
	}

	if(!is_string($link) ) {
		bail();
	}

	$json = file_get_contents('./posts.json');
	$obj = json_decode($json);
	if(!isset($obj->posts->$link)) {bail();}
	$post = $obj->posts->$link;
	// print_r($post);
	
	$body = $post->body;
	$color = $post->color;
	$icon = $post->icon;
	$postdate = $post->postdate;

	function bail() {
		echo '<META HTTP-EQUIV="Refresh" Content="0; URL=./index.php">';
		exit();
	}
		
?>

<?php include "./includes/nav.php" ?>

<div class="blog-title <?php echo $color ?>">
	<a href="./"><img class="back-arrow" src="./img/backback2.svg"></a>
	<img class="blog-image-inverse" src="./img/<?php echo $icon ?>">
	<img class="date-image" src="./img/<?php echo $postdate ?>">
</div>

<div class="light-gray main-post">
	<div class="row">
		<div class="small-12 large-10 large-offset-1 columns" style="padding-top:35px;">

			<?php echo $body ?>

		</div>
	</div>

	<div class="row" style="height:50px;">
		<div class="small-12" >
			&nbsp;
		</div>
	</div>

</div>

<?php include "./includes/footer.php"; ?>
		
		