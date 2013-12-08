<?php  
	$page_class = "blog";
	include "includes/header.php";
	$js = 'js/blog.js';
		
?>

<?php include "./includes/nav.php" ?>

<div class="blog-title light-green">
	<a href="./"><img class="back-arrow" src="./img/backback2.svg"></a>
	<img class="blog-image-inverse" src="./img/processingicon.svg">
</div>

<div class="light-gray main-post">
	
	<div class="row">

		<div class="small-12 large-10 large-offset-1 columns" style="padding-top:60px;">

			<h2>Predictive Processing Beat Detection</h2>

			<p style="text-align:justify;">
				<span style="margin-left:60px;"></span>Several years ago, I had a borderline obsession with audio analysis algorithms and beat detection. At the time, I was building many Arduino LED projects, and using the algorithms to power 'party' effects; the better the algorithm, the better the effects became. After a while, my interests moved on, and the code sat in a dusty file on my hard drive for nearly two years. Not too long ago, <a href="http://www.frogdesign.com" target="_blank">Frog Design</a> contacted me, asking to use the algorithm that I had developed. After pulling up the files, I decided that I could do better: the coding began.<br><br>


		
				<span style="margin-left:60px;"></span>I used the open source language “Processing” (<a href="www.processing.org" target="_blank">www.processing.org</a>) to write a better, highly accurate and predictive beat analysis routine. Frog Design featured my algorithm at the SxSWi kickoff party in 2013. They integrated my code with Adobe AS3 in order to precisely time the slide changes for a crowdsourced DJ system.
			</p>

			

			<p style="text-align:justify;"><br><b>
			NOTE: This sketch represents countless hours of labor, it is free for non-commercial use, but please do me a favor by linking back to this site and crediting my work.</b><br>
			</p>
			<a href="./dl/beatdetection.zip">
				<div>
					<img src="./img/download.svg" style="width:60px;">
					<h4>Download Source</h4>
				</div>
			</a>
			<a class="scroll" href="#usage"><h6 style="margin-bottom:15px;">usage instructions</h6></a>

			<p style="text-align:justify;">
			It helps you out, or you do something cool with it, <a href="mailto:coreyhwalsh@gmail.com?Subject=Processing%20Beat%20Detection" target="_top">let me know!</a> I love to hear feedback!<br>
			</p>

			<p>Check out the GitHub repo: <a href="https://github.com/kctess5/Processing-Beat-Detection">https://github.com/kctess5/Processing-Beat-Detection</a></p>

			<p style="text-align:justify;"><br>

				<span style="margin-left:60px;"></span>The program uses adaptive thresholds to detect “beats” in many (30) bands, and then uses another adaptive threshold to separate a beat from sounds. The video below demonstrates the program in action. The time between registered beats is monitored (graphed on the top) and used to predict when the next beat will occur, greatly improving accuracy. When the background color changes, a beat has been detected.<br>
			</p>

			<div class="video-container">
				<iframe width="460" title="YouTube video player" src="//www.youtube.com/embed/QVX2F6kUaRQ?HD=1;rel=0;showinfo=0;autohide=1;" height="289" frameborder="0"></iframe>
			</div>

			<p style="text-align:justify;">

				<span style="margin-left:60px;"></span>The bottom part of the video shows the Fast Fourier Transform (FFT) with thresholds and averages. The top is a graph showing time between beats, time is on the x axis. As you can see, the program finds the tempo very quickly, especially in songs with pronounced beats.<br>
			</p>

			<div id="usage">
				<h3><b> usage </b></h3>

				<p style="text-align:justify;">
					When you <a href="./dl/beatdetection.zip">download</a> the code, there are a few things you have to do to get it up and running: <br><br>

					1) Ensure that the .pde file is enclosed in a folder of the same name ("beatdetection")<br><br>
					2) If you don't have Processing, you will need to <a href="http://processing.org" target="_blank">install it</a><br><br>
					3) If you don't have Soundflower, <a href="http://soundflower.en.softonic.com/mac" target="_blank">install it</a>. Sorry non-mac users, you will either have to use the built in microphone or figure out some higher quality input or Soundflower alternative. Once you have done that, set both computer audio input and output to "Soundflower (2ch)," this is done through the "Sound" menu on System Preferences. If you did it correctly, when you play some music you should not hear anything. Go into the Soundflower settings by opening Soundflower and setting the output to the correct system audio output, and you should be able to hear again.<br><br>
					4) You may or may not need to install some packages for the sketch to run, if so, <a href="http://wiki.processing.org/w/How_to_Install_a_Contributed_Library" target="_blank">look here</a><br><br>
					5) Run the sketch, assuming everything is working it should look a lot like the above video. Play your favorite songs through your computer and enjoy!
				</p>

			</div>

			

			<div class="code-container">
				<iframe src="./dl/beatdetection.pde" frameborder="0"></iframe>
			</div>

		</div>
	</div>

	<div class="row" style="height:50px;">
		<div class="small-12" >
			&nbsp;
		</div>
	</div>

</div>











<?php include "includes/footer.php"; ?>
		
		