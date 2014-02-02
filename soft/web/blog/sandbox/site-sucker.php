<?php  
	$page_class = "blog dark-blue";
	include "includes/header.php";
	$js = 'js/blog.js';
	$siteSuckerDate = "7/22/13";
	$siteSuckerTitle = "";
	$siteSuckerSubtitle = "";
	$siteSuckerExerpt = "";
		
?>

<?php include "./includes/nav.php" ?>

<div class="blog-title">
	<a href="./"><img class="back-arrow" src="./img/backback2.svg"></a>
	<img class="blog-image-inverse" src="./img/vacuumicon.svg">
	<!-- <p class="date"><?php echo $siteSuckerDate?></p> -->
</div>

<div class="window light-gray main-post">

	<div class="row">
		<div class="small-12 large-10 large-offset-1 columns" style="padding-top:60px;">
			<p style="text-align:justify;">
				<span style="margin-left:60px;"></span>People like to check up on other people, and web designers are no exception. When I see a beautiful website, the first thing that I usually do is view page source to see if the underlying code is similarly beautiful.<br><br>

				<span style="margin-left:60px;"></span>Step one in almost every website design is to look at other people's work, just to get a feel for the functionality and design principles that are desired. While doing this, I happened upon a great free tool that makes tinkering with and understanding other people's code an absolute breeze, and hopefully it can help you out as well. <br><br>

				<span style="margin-left:60px;"></span>It is called <a href="http://sitesucker.us/home.html" target="_blank">Site Sucker</a>, and let me tell you, it doesn't suck. It allows you to download entire websites, including the file structure. Why would you do this you might ask? Rather navigating thousands of lines of code in an internet browser, you can just host the whole site locally and use your favorite code editor like <a href="http://www.sublimetext.com" target="_blank">Sublime Text</a>! With a virtual server like <a href="http://www.apachefriends.org/en/xampp.html" target="_blank">xampp</a> all you have to do is put the downloaded files into xampp's root directory, then you can view it in your browser like a normal website, except that you can edit any part of the code.<br><br></p>

				<p style="text-align:center;">Download it from the website here:</p>
			

				<a href="http://sitesucker.us/home.html" target="_blank"><div>
					<img src="./img/download.svg" style="width:60px;">
					<h4>Site Sucker</h4>
				</div></a>

				<p style="text-align:center; font-size:15px; margin-bottom:60px;">If it helps you, be sure to give a shoutout to the creater who gave up hours of time for free!</p>

			<p style="text-align:justify;">
				<span style="margin-left:60px;"></span>Once you finish downloading, install and launch the app. Then to use it, just type in the domain of the website that you want to download, click 'Download,' wait a minute or two, then check your downloads folder! Move the downloaded folder into your virtual server's root directory, then go to http://localhost/[insert folder name here].<br><br>

				<span style="margin-left:60px;"></span>You should be warned that because sitesucker is pulling the files from the servers responses, server side scripts will <i>not</i> be 'sucked.' Generally with little to no effort you can get any normal sized website running locally in just a minute or two.<br>
			</p>

			<p style="text-align:center; ">Share and enjoy!<br><br><br></p>

		</div>
	</div>

</div>
<?php include "includes/footer.php"; ?>
		
		