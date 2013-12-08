<?php 
	$page_class = "blog";
	include "includes/header.php";
	$js = 'js/blog.js'; 	
?>

<?php include "./includes/nav.php" ?>

<div class="blog-title red">
	<h1>blog</h1>
</div>

<div class="light-gray window"> 


<?php

$json = file_get_contents('./posts.json');
$obj = json_decode($json);
foreach ($obj->posts as $post => $info) {

	echo ' 
		<div class="row blog-link-container">
			<div class="small-4 large-3 columns" style="text-align:right;">
				<a href="./'. $post .'"><img class="blog-image" src="./img/'. $info->icon .'"></a>
			</div>
			<div class="small-8 large-9 columns blog-link" style="text-align:left;">
				<a href="./'. $post .'"><h1>'. $info->title .'</h1></a>
			</div>
		</div>
	';

}?>



	<div class="row hide-for-small" style="height:70px;">
		<div class="small-12" >
			&nbsp;
		</div>
	</div>
	<div class="row" style="height:50px;">
		<div class="small-12" >
			&nbsp;
		</div>
	</div>

</div>

<?php include "includes/footer.php"; ?>


		
		