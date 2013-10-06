// Console nerfing
if (!window.console) window.console = { log: function() { } };



jQuery('img.lazy').attr('src',jQuery(this).attr('data-src'));

$("img.lazy").lazyload({
     //effect       : "fadeIn"
     threshold : 100
 });

$(".scroll").click(function(event){
     event.preventDefault();
     //calculate destination place
     var headerHeight = parseInt($(".header").css("height"));
     console.log(headerHeight);
     var dest=0;
     if($(this.hash).offset().top > $(document).height()-$(window).height()){
          dest=$(document).height()-$(window).height();
          //dest=$(document).height()-$(window).height()- headerHeight;
     }else{
          dest=$(this.hash).offset().top;
          //dest=$(this.hash).offset().top - headerHeight;
     }
     //go to destination
     $('html,body').animate({scrollTop:dest}, 300,'swing');
 });


$(function() {

	$("img.lazy").each(function() {
		var source = $(this).attr("data-original");
		$(this).attr("src",'./img/place.png');
	});


	// Stick footer to bottom
	var stickFooterToBottomClosure = function() {
	    // Stick footer to bottom of screen.  Only enable this if we 
	    console.log("stickFooterToBottomClosure");
	    var el = $(".change-height-for-footer");
	    // Only add the listener if we found an element.
	    if( $(el).length ) {
//			if( $(el).attr("data-footeroffset") ) {
//				offset = parseInt( $(el).attr("data-footeroffset") );
//				console.log("offset: " + offset);
//			}
			console.log("el found. adding resize event...");
			
			function updateFooter() {
				var h1 = $("#container").height();
				var h2 = $(window).height();
				//console.log( "container: " + h1 + ", viewport: " + h2 );
			    var dif = h2-h1;
		        console.log("setting element height... dif:" + dif);
				var offset = -$("#nav").height()+4;
		        $(el).css("min-height", $(el).height() + dif + offset );
			};
			
			// run once
			updateFooter();
			// add resize event
			$(window).resize(updateFooter);
			
		}
	}();
	
	// Init main nav
	updateNav();
	$("#nav nav li a").click(function(e) {
//		console.log("nav click.");
		if( $(this).hasClass("active") ) {
			if( $(this).text() != "Work" ) {
				// Clicking any active link EXCEPT work.
//				console.log("scroll to top.");
				$.scrollTo(0, 300);
				e.preventDefault();
			} else {
				// Clicking "Work" when it's active
				if( $('#container').hasClass('home') ) {
					// If we're on the homepage
					e.preventDefault();
					$.scrollTo("#work", 300);
					$.address.path("/work");
					// Show nav logo.
					$("#nav .logo").show();
					$("#nav .logo").removeClass("hidden");
				} else if( $('#container').hasClass('work') ) {
					// If we're inside a work item
				}
			}
		}
		// Hide the nav menu after click;
		$("#nav nav a.menu-button").click();
	});
	// Click Menu button to toggle menu (small screens)
	$("#nav nav a.menu-button").click(function(e) {
		e.preventDefault();
		$("#nav nav ul").toggleClass("hidden");
		$(this).toggleClass("active");
		// Scroll down
		var offset = -100;
		if( $(window).scrollTop() < $(this).offset().top+offset ) {
			$.scrollTo( $(this).offset().top+offset, 300 );
		}
	});
	
	// Footer click: back-to-top
	$("#footer .back-to-top").click(function(e) {
		e.preventDefault();
		$.scrollTo(0, 300);
	});
	
	function updateNav() {
		var containerClass = $("#container").attr("class");
		$("#nav nav li a").each(function() {
			var el = $(this);
			var text = $(this).text().toLowerCase();
			containerClass = containerClass.replace(/\s/g, '');
			//console.log("nav init: class: " + containerClass + ", text: " + text);
			if( $("#container").hasClass(text) && (text.length > 0) ) {
				//console.log("match! text:" + $(this).text() );
				$(this).addClass("active");
				//$(this).remove();
				//return false;
			}
		});
	}

	function orbitUpdate() {
		// nav + scrolldown height: 340
		if( $(window).scrollTop() < 10 ) {
			// Get orbit's native height
			var orbitHeight = $(".orbit-container").height();
			var navHeight = 160;
			var maxChop = 200; // Maximum cropping, each side, pixels 
			var windowHeight = parseInt( $(window).height() );
			var navOffset = $('#nav').offset().top;
			// Find current difference between window height and bottom of scrolldown using orbit's native height.
			var dif = (orbitHeight + navHeight) - windowHeight;
			if( dif > maxChop ) { dif=maxChop; };
			if( dif > 0 ) {
				$('.orbit-container').css({
					'position': 'relative',
					'top': -dif/2,
					'margin-bottom': -dif
				});
			} else {
				$('.orbit-container').css({
					'top': 0,
					'margin-bottom': 0
				});
			}
			//console.log("orbitUpdate: orbitHeight: " + orbitHeight + ", dif: " + dif + ", nav offset: " + $('#nav').offset().top );
		}
	}
	
	function makeSticky(el, dir, offset) { 
		// Make something sticky: behaves normal until it's about to scroll off screen, then it sticks to screen edge.
		// el  = Element to make sticky
		// dir = "top" or "bottom"
		// offset = if you want it to jump to screen edge a few pixels sooner/later than default.
		if( !offset ) { offset = 0; }

		// grab the initial top offset of the navigation 
		if( dir != "bottom" && !$(el).hasClass("bottom") ) { dir = "top"; }
		$(el).addClass("sticky");
		$(el).addClass(dir);
		$(el).attr( "data-scrollTop", $(el).offset().top+offset );
		$(el).attr( "data-offset", offset );
	}
	function stickyUpdate() {
		//console.log("stickyUpdate()");
		// our function that decides weather the navigation bar should have "fixed" css position or not.
		$(".sticky").each(function() {
			var el = $(this);
			var scroll_top = $(window).scrollTop(); // our current vertical position from the top
			var sticky_navigation_offset_top = parseInt( $(el).attr("data-scrollTop") );
			var marginTop = parseInt( $(el).find("#nav").attr("data-margin-top") );
//			if( marginTop != 0 ) {
//				sticky_navigation_offset_top += 2*marginTop;
//				console.log("stickyUpdate: adding marginTop: " + marginTop + ", new: " + sticky_navigation_offset_top);
//			}
			if( !$(this).hasClass("bottom") ) {
				// assume sticky top.
				//console.log("stickyUpdate: " + $(el).className + ", scroll_top: " + scroll_top + ", offset: " + sticky_navigation_offset_top);
				if (scroll_top > sticky_navigation_offset_top && !$(el).hasClass("fixed") ) { 
					$(el).addClass("fixed");
					var offset = parseInt( $(el).attr("data-offset") );
					var marginTop = $("#nav").css("margin-top");
					if(offset) {
						var bodyOffset = parseInt( $("body").css("margin-top") );
						$("body").css("margin-top", newOffset);
						//console.log("offset: " + offset + ", bodyOffset: " + bodyOffset + ", newOffset: " + newOffset);
					}
					var marginTop = $("#nav").css("margin-top");
					if( marginTop != 0 ) {
						$("#nav").attr("data-margin-top", marginTop);
						$("#nav").css("margin-top", 0);
					}
				} else if ( scroll_top < sticky_navigation_offset_top && $(el).hasClass("fixed") )  {
					$(el).removeClass("fixed");
					var offset = parseInt( $(el).attr("data-offset") );
					if(offset) {
						var bodyOffset = parseInt( $("body").css("margin-top") );
						var newOffset = bodyOffset + offset + 20;
						$("body").css("margin-top", newOffset);
						//console.log("offset: " + offset + ", bodyOffset: " + bodyOffset + ", newOffset: " + newOffset);
					}
					var marginTop = $("#nav").attr("data-margin-top");
					if( marginTop != 0 ) {
						$("#nav").css("margin-top", marginTop);
					}
				}
			} else {
				scroll_top += $(window).height();
				if (scroll_top < sticky_navigation_offset_top) { 
					$(el).addClass("fixed-bottom");
				} else {
					$(el).removeClass("fixed-bottom"); 
				}
			}
			
		});
	}
		
	// Custom GA events
	$('#nav a').click(function(e) {
		if( $(this).text() ) {
			// Has text. Probably a main top nav link.
			_gaq.push(['_trackEvent', 'Main nav', 'click', $(this).text() ]);
		} else if( $(this).hasClass("facebook") ){	
			// Probably a facebook link
			_gaq.push(['_trackEvent', 'Main nav', 'click', 'facebook']);
		} else if( $(this).hasClass("menu-button") ) {
			// Menu button.  Don't track.
		} else if( $(this).parent().hasClass("logo") ) {
			// Top logo
			_gaq.push(['_trackEvent', 'Main nav', 'click', 'logo']);
		}
	});
	$('#footer a').click(function(e) {
		if( $(this).hasClass('visit-our-friends') ) {
			_gaq.push(['_trackEvent', 'Footer', 'click', 'meringcarson']);
		} else if( $(this).parent().hasClass('back-to-top') ) {
			_gaq.push(['_trackEvent', 'Footer', 'click', 'back to top']);
		}
	});

//	console.log("about to read address...");
//	console.log( $.address.value() );
	
	
});



//Create HTML5 elements for IE's sake
//document.createElement("article");
//document.createElement("section");

function init_imgParallax(el) {
	$window = $(window);
	
	if( $window.width < 640) { return false; }

	// Cache document height (this assumes height does not change, which might be a problem later.)
	var documentHeight = $(document).height();
	// Cache window height
	var window_height;
	var scrollTop = $(window).scrollTop();
	updateWindowHeight();

	// On window resize, re-fetch window height.
	$(window).resize(updateWindowHeight);

	$(window).scroll(function() {
		scrollTop = $(window).scrollTop();
		update_imgParallax();
	});


	function updateWindowHeight() {
		window_height = $(window).height();
	}

	$(el).each(function() {
		// Save the initial "top" inline style for later
		$(this).data("start_y", parseInt($(this).css("top")));
		$(this).data("offset", parseInt($(this).offset().top));
		// Add "imgParallax" class so we can find it later
		$(this).addClass("imgParallax");
	});

	function update_imgParallax() {
		var headerHeight = 164;
		// Only compute changes for elements in view
		// Requires jquery.viewport.js, which I've pasted into app.js.
		$(".imgParallax:in-viewport").each(function() {
			// Calculate new Y position
			var newY;
			// percentage: distance from center of screen/total document height * 100
			var indexOfDifference;
			var indexOfDifference = (scrollTop + ((window_height + headerHeight) / 4) - $(this).data("offset"))/documentHeight*100;
			
			newY = 	(indexOfDifference * $(this).data("speed") + $(this).data("start_y"));
			//sets newY to the top attribute of this element
			$(this).css("top", newY);
		});
	}
};

function init_bkgParallax(el) {
	$window = $(window);

	if( $window.width() < 640) { 
		$(el).each(function() {
			$(this).css("background-position", $(this).css("background-position").split(" ")[0] + " 0px");
			console.log($(this).css("background-position").split(" ")[0] + " auto");
		});
		return false; 
	}

	// run updateparalla
	$(window).scroll(function() {
		scrollTop = $(window).scrollTop();
		update_bkgParallax();
	});

	var documentHeight = $(document).height();
	var window_height;
	updateWindowHeight();
	$(window).resize(updateWindowHeight);

	function updateWindowHeight() {
		window_height = $(window).height();
		
		if ($(window).width() > 1600) {
			$("#brand-background").each(function() {	
				$(this).css("background-size", "cover");
			});
		}
		else {
			$("#brand-background").each(function() {
				$(this).css("background-size", "auto 800px");
			});
		}
	}

	$(el).each(function() {
		// Save the initial "top" inline style for later
		console.log($(this).css("background-position"));
		$(this).data("start_y", parseInt($(this).css("background-position").split(" ")[1]) );
		$(this).data("offset", parseInt($(this).offset().top));
		//$(this).data("offset", parseInt($(this).offset().top));
		// Add "imgParallax" class so we can find it later
		$(this).addClass("bkgParallax");
	});

	function update_bkgParallax() {
		$(".bkgParallax:in-viewport").each(function() {
			// Calculate new Y position
			var newY;
			var headerHeight = 164;
			// percentage: distance from center of screen/total document height * 100
			var indexOfDifference;
			var indexOfDifference = scrollTop / documentHeight * 100;
			
			newY = 	(indexOfDifference * $(this).data("speed") + $(this).data("start_y"));
			//sets newY to the top attribute of this element
			$(this).css("background-position", $(this).css("background-position").split(" ")[0] + " " + newY + "px");
		});
	}
};