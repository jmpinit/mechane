<?php 
	$page_class = "home work static-nav";
	include "includes/header.php";
	$js = 'js/home.js';
		
?>

<div class="main red"> 

	<div class="fullwindow" id="splash">
		<div id="scrolly" style="position:absolute; top:50%; height:100% display:none;">&nbsp;</div>

		<div id="site-title">
			<h1>draw_bot</h1>
		</div>		
		<div id="profile-picture">
			<noscript><img src="./img/pen.svg" style="width:20%; min-width:200px;"></noscript>
			<img class="lazy" data-original="./img/pen.svg" style="width:20%; min-width:200px;">
		</div>

		<div class="fade">
			<a class="scroll" href="#services"><img class="lazy" id="scroll" data-original="./img/arrow.svg" height="32" width="32"></a>
		</div>	
		
	</div>

	<?php include "includes/nav.php" ?>

	<div id="services">
		<div id="scrolly" style="position:absolute; top:50%; height:100% display:none;">&nbsp;</div>
		
		<h1 class="top-text hide-for-small">Slide</h1>
		<h1 class="top-text show-for-small">Slide</h1>

		<img class="lazy" id="mac-image" data-speed="2" data-original="./img/macsublime.svg">
		
		<h1><em class="hide-for-small">...Section</em></h1>
		<h1><em class="show-for-small">...Section</em></h1>
	</div>

	<div id="work">
		<div id="scrolly" style="position:absolute; top:30%; height:100% display:none;">&nbsp;</div>
		<h1>Draw Here<h1>


	<div id="draw" align="center">
        <canvas id="myCanvas" width="700" height="400" style="border:0px solid black"></canvas>
        <br/>
        <div id="controls">
	        <button id="clearArea">Clear Area</button>
	        <button onclick="">Draw</button>

	        <div style="display:none;">
		        Line width : <select id="selWidth">
		            <option value="1">1</option>
		            <option value="3">3</option>
		            <option value="5">5</option>
		            <option value="7">7</option>
		            <option value="9" selected="selected">9</option>
		            <option value="11">11</option>
		        </select> 
		        Color : <select id="selColor">
		            <option value="black">black</option>
		            <option value="blue" selected="selected">blue</option>
		            <option value="red">red</option>
		            <option value="green">green</option>
		            <option value="yellow">yellow</option>
		            <option value="gray">gray</option>
		        </select>
		    </div>
	    </div>
	    <div id="coordsResponse" style="display: none;"></div>
    </div>


	</div>

	<div class="window" id="process" >
		<div id="scrolly" style="position:absolute; top:70%; height:100% display:none;">&nbsp;</div>
		<div style="text-align:center;"><h1>Section 2</h1></div>

		<div class="row process-bullet">
			<div class="small-12 large-9 small-centered columns" >
				<div class="row">
					<div class="large-3 large-offset-1 small-4 columns" style="text-align:center;">
						<div class="icon-wrapper">
							<img class="lazy" data-original="./img/planicon.svg" width="100%">
							<noscript><img src="./img/planicon.svg" width="100%"></noscript>
						</div>
					</div>
				</div>
			</div>
		</div>

		<div class="row process-bullet">
			<div class="small-12 large-9 small-centered columns" >
				<div class="row">
					<div class="large-3 large-offset-1 small-4 columns" style="text-align:center;">
						<div class="icon-wrapper">
							<noscript><img src="./img/designicon.svg"></noscript>
							<img class="lazy" data-original="./img/designicon.svg">
						</div>
					</div>
				</div>

			</div>
		</div>

		<div class="row process-bullet">
			<div class="small-12 large-9 small-centered columns">
				<div class="row">
					<div class="large-3 large-offset-1 small-4 columns" style="text-align:center;">
						<div class="icon-wrapper">
							<noscript><img src="./img/buildicon.svg"></noscript>
							<img class="lazy" data-original="./img/buildicon.svg">
						</div>
					</div>
				</div>
			</div>
		</div>

		<div class="row process-bullet">
			<div class="small-12 large-9 small-centered columns">
				<div class="row">
					<div class="large-3 large-offset-1 small-4 columns" style="text-align:center;">
						<div class="icon-wrapper">
							<noscript><img src="./img/refineicon.svg"></noscript>
							<img class="lazy" data-original="./img/refineicon.svg">
						</div>
					</div>
				</div>
			</div>
		</div>
	</div>

	<div id="about-me">
		<div id="scrolly" style="position:absolute; top:100%; height:100% display:none;">&nbsp;</div>
			<h1>half width</h1>
			<div class="row">

			</div>
	</div>

	<!-- <div class="halfwindow" id="contact-me"> -->
	<div id="contact-me">

		<h2>contact</h2>

		<form id="contact-form" method="POST" action="email.php">


			<div class="row">
				<div class="small-12 large-4 columns">

					<div class="row">
						<div class="small-12 columns">
							<input class="self-describing contact-info" title="name" type="text" id="name" name="name">
						</div>
					</div>

					<div class="row">
						<div class="small-12 columns">
							<input class="self-describing contact-info" title="email" type="text" id="email" name="email">
						</div>
					</div>

					<div class="row hide-for-small">
						<div class="small-12 columns" >
							<input type="submit" name="email" value="Submit" class="submit-button">
						</div>
					</div>

				</div>

				<div class="small-12 large-8 columns">
					<textarea class="self-describing" title="message" type="text" id="message" name="message" style="cursor: text;"></textarea>
				</div>

				<div class="small-12 show-for-small columns">
					<input type="submit" name="email" value="Submit" class="submit-button">
				</div>

			</div>


		</form>
		<br>
		<div id="formResponse" style="display: none;"></div>
	</div>
	

<!-- <div style="font-size:3em;">
	<div style="font-family:quicksandbold_oblique;">This is a test sentence, I hope that you like this font!</div>
	<div style="font-family:quicksandbold;">This is a test sentence, I hope that you like this font!</div>
	<div style="font-family:quicksandbook_oblique;">This is a test sentence, I hope that you like this font!</div>
	<div style="font-family:'quicksandbook';">This is a test sentence, I hope that you like this font!</div>
	<div style="font-family:'quicksanddash';">This is a test sentence, I hope that you like this font!</div>
	<div style="font-family:'quicksandlight_oblique';">This is a test sentence, I hope that you like this font!</div>
	<div style="font-family:'quicksandlight';">This is a test sentence, I hope that you like this font!</div>
</div> -->

</div><!-- end .main -->
		
<?php include "includes/footer.php"; ?>
		
		