console.log("home.js...");

function PreloadImage(imgSrc, callback){
  var objImagePreloader = new Image();

  objImagePreloader.src = imgSrc;
  if(objImagePreloader.complete){
    callback();
    objImagePreloader.onload=function(){};
  }
  else{
    objImagePreloader.onload = function() {
      callback();
      //    clear onLoad, IE behaves irratically with animated gifs otherwise
      objImagePreloader.onload=function(){};
    }
  }
}

$(function(){
	
	var win = $(window);
	var docHeight 	= $(document).height();	
	var winHeight 	= $(window).height();	

	var navHeight = 100;

	$('.main-post').addClass('active');
	
	
	bgHeight();

	win.resize(function(){ 
		bgHeight();
	});

	win.scroll(function(){
	
		winTop = win.scrollTop();

		updateStickyNav();
		
	});
	
	
	
    win.scroll(function () {
    
    	if ($('body').hasClass('bumped') && win.height() + win.scrollTop() >= $(document).height()) {}
    	
    	else if ($('body').hasClass('bumped') && win.height() + win.scrollTop() -20 <= $(document).height()) {
    		$('body').removeClass('bumped');
    	}
    
        else if (win.height() + win.scrollTop() >= $(document).height()) {
        	$('body').addClass('bumped');
        }
        //updateStickyNav();
        
        
    });
	
	
	// FUNCTIONS
	
	
	function bgHeight() {
		winHeight 	= $(window).height();
		$('.fullwindow').css('height', winHeight+"px");
		$('.halfwindow').css('height', winHeight/2+"px");
		//$('.halfwindow#contact-me').css('height', winHeight/2-20+"px");
		
		$('.window').css('min-height', winHeight+"px");
		//console.log("setting height to " + height);
	};
});




// function updateStickyNav() {
// 	// our function that decides weather the navigation bar should have "fixed" css position or not.
// 		var el = $("#nav");
// 		//var navHeight = $("#nav").height();
// 		var slideshowBottom = $("#slides").height();
// 		var scroll_top = $(window).scrollTop(); // our current vertical position from the top
		
// 		if( $("#container").hasClass("static-nav") && (scroll_top > slideshowBottom) ) {
// 			$("#container").removeClass("static-nav");
// 		} else if ( !$("#container").hasClass("static-nav") && (scroll_top < slideshowBottom) ) {
// 			$("#container").addClass("static-nav");
// 		}
// }

function updateStickyNav_old() {
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

function updateStickyNav() {
	var slideshowBottom = $("#splash").height();
	var scroll_top = $(window).scrollTop(); // our current vertical position from the top
	
	if(  scroll_top > slideshowBottom ) {
		$(".header").css("position","fixed");
	} else if (  (scroll_top < slideshowBottom) ) {
		$(".header").css("position","relative");
	}
}

$('#splash #scrolly').bind('inview', function(event, isInView, visiblePartX, visiblePartY) {
	if (isInView) {
		$('.main').removeClass('dark-green light-green light-gray dark-blue light-blue dark-blue');
		$('.main').addClass('red');
		//$('.header').removeClass('active');
	} 
});

$('#services #scrolly').bind('inview', function(event, isInView, visiblePartX, visiblePartY) {
	if (isInView) {
		$('.main').removeClass('dark-green red light-gray dark-blue light-blue dark-blue');
		$('.main').addClass('light-green');
		$('.header #services-button').addClass('active');
		$('.header').addClass('active');
		//$('.header').addClass('active');
	} 
	else{
		$('.header #services-button').removeClass('active');
	}
});

$('#work #scrolly').bind('inview', function(event, isInView, visiblePartX, visiblePartY) {
	if (isInView) {
		$('.main').removeClass('dark-green red light-gray dark-blue light-blue dark-blue');
		$('.main').addClass('light-green');
		$('.header #work-button').addClass('active');
		//$('.header').addClass('active');
	} 
	else{
		$('.header #work-button').removeClass('active');
	}
});

$('#process #scrolly').bind('inview', function(event, isInView, visiblePartX, visiblePartY) {
	if (isInView) {
		$('.main').removeClass('dark-green light-green red light-gray light-blue dark-blue');
		$('.main').addClass('dark-blue');
		$('.header #process-button').addClass('active');
		$('.header').addClass('active');
	} 
	else{
		$('.header #process-button').removeClass('active');
	}
});

$('#about-me #scrolly').bind('inview', function(event, isInView, visiblePartX, visiblePartY) {
	if (isInView) {
		$('.main').removeClass('dark-green light-green red light-gray light-blue dark-blue');
		$('.main').addClass('dark-blue');
		$('.header #contact-button').addClass('active');
		$('.header').addClass('active');
	} 
	else{
		$('.header #contact-button').removeClass('active');
	}
});


