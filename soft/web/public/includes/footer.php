			<!-- <div></div> -->
			<div id="footer">
				<div class="copyright">draw_bot <span style="font-size:.8em; line-height:1em;">&diams;</span> drawbot@hzldv.com</div>
			</div>
		</div> <!-- end #container -->
		
		<script>
		document.write('<script src=' +
		('__proto__' in {} ? '<?php echo $path ?>js/vendor/zepto' : 'js/vendor/jquery') +
		'.js><\/script>')
		</script>
		
		<!--<script type="text/javascript">
		  console.log('init GA...');
		  var _gaq = _gaq || [];
		  _gaq.push(['_setAccount', 'UA-35060825-1']);
		  _gaq.push(['_trackPageview']);
		
		  (function() {
		    var ga = document.createElement('script'); ga.type = 'text/javascript'; ga.async = true;
		    ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
		    var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(ga, s);
		  })();
		  console.log('GA initted.');
		</script> -->
		
		<!-- Add custom youtube events to Google Analytics -->
		
<!--		<script src="<?php echo $path ?>js/vendor/jquery-1.9.1.min.js"></script>-->
		<script src="<?php echo $path ?>js/vendor/jquery.js"></script>
		<script src="<?php echo $path ?>js/vendor/jquery.lazyload.js"></script>
		
<!--		<script src="<?php echo $path ?>js/vendor/jquery.address-1.6.min.js"></script>-->
		
		<script src="<?php echo $path ?>js/foundation/foundation.js"></script>
		
<!--		<script src="js/foundation/foundation.alerts.js"></script>-->
		
		<script src="<?php echo $path ?>js/foundation/foundation.clearing.js"></script>
		
		<script src="<?php echo $path ?>js/foundation/foundation.cookie.js"></script>
		
<!--		<script src="js/foundation/foundation.dropdown.js"></script>-->
		
<!--		<script src="js/foundation/foundation.forms.js"></script>-->
		
<!--		<script src="js/foundation/foundation.joyride.js"></script>-->
		
<!--		<script src="js/foundation/foundation.magellan.js"></script>-->
		
<!--		<script src="js/foundation/foundation.orbit.js"></script>-->
		
<!--		<script src="js/foundation/foundation.placeholder.js"></script>-->
		
<!--		<script src="js/foundation/foundation.reveal.js"></script>-->
		
<!--		<script src="js/foundation/foundation.section.js"></script>-->
		
<!--		<script src="js/foundation/foundation.tooltips.js"></script>-->
		
<!--		<script src="js/foundation/foundation.topbar.js"></script>-->
		
		<script src="<?php echo $path ?>js/app.js"></script>
		
		<script src="<?php echo $path ?>js/global.js"></script>
		<script type="text/javascript" src="js/draw.js"></script>

		
		<?php
			if ( isset($js) ) {
				echo '<script src="' . $js . '"></script>';
			}
			
		?>
		
		<script>
		$(document).foundation();
		
		$(function() {

		});
		
		</script>
	</body>
</html>
