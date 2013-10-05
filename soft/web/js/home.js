console.log("home.js...");

$(function(){

	InitThis();

	var macOffset = $('#mac-image').offset().top + parseInt($('#mac-image').css('width'))/2;
	var macSpeed = $('#mac-image').data("speed"); 
	


	var describedClass = 'self-described';
	$('.self-describing').focus(function(){
		if (this.value==this.title) this.value="";
		$(this).removeClass(describedClass);
	}).blur(function(){
		if (!this.value || this.value==this.title){
			this.value=this.title;
			$(this).addClass(describedClass);
		}
	}).blur();

	
	var win = $(window);
	var docHeight 	= $(document).height();	
	var winHeight 	= $(window).height();	
	var navHeight = 100;
	
	
	bgHeight();

	win.resize(function(){ 
		bgHeight();
	});

	win.scroll(function(){
	
		winTop = win.scrollTop();
		var macIndex = 100*(winTop + winHeight/2 - macOffset) / docHeight;
		updateStickyNav();
		$('#mac-image.active').css('margin-left', macIndex * macSpeed + "px" );

	});
	
	
	
	// FUNCTIONS
	
	
	function bgHeight() {
		winHeight 	= $(window).height();
		$('.fullwindow').css('height', winHeight+"px");
		$('.halfwindow').css('height', winHeight/2+"px");
		$('.window').css('min-height', winHeight+"px");
		if (winHeight > 1000) {
			$('.window#process').css('min-height', "1000px");
		}
		
	};
});



function updateStickyNav() {
	var slideshowBottom = $("#splash").height();
	var scroll_top = $(window).scrollTop(); // our current vertical position from the top
	
	if(  scroll_top > slideshowBottom ) {
		$(".header").css("position","fixed");
		$(".top-text").css("padding-top", $(".header").css("height") );
	} else if (  (scroll_top < slideshowBottom) ) {
		$(".header").css("position","relative");
		$(".top-text").css("padding-top","0px");
	}

}

$('#splash #scrolly').bind('inview', function(event, isInView, visiblePartX, visiblePartY) {
	if (isInView) {
		$('.main').removeClass('dark-green light-green light-gray dark-blue light-blue dark-blue');
		$('.main').addClass('red');
		//$('.header').removeClass('active');
	} 
});

$('#services').bind('inview', function(event, isInView, visiblePartX, visiblePartY) {
	if (isInView) {
		$('#mac-image').addClass('active');
	} 
	else{
		$('#mac-image').removeClass('active');
	}
});

$('#services #scrolly').bind('inview', function(event, isInView, visiblePartX, visiblePartY) {
	if (isInView) {
		$('.main').removeClass('dark-green red light-gray dark-blue light-blue dark-blue');
		$('.main').addClass('light-green');
		$('.header #services-button').addClass('active');
		$('.header').addClass('active');
		$('#mac-image').addClass('active');
		//$('.header').addClass('active');
	} 
	else{
		$('.header #services-button').removeClass('active');
		$('#mac-image').removeClass('active');
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
		$('img').addClass('active');
	} 
	else{
		$('.header #process-button').removeClass('active');
		$('img').removeClass('active');
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



$("#contact-form").submit(function() {
    $.post('email.php', 
    {
    	name: $('#name').val(), 
    	email: $('#email').val(), 
    	message: $('#message').val(),
    	namestate: $('#name').hasClass('self-described'),
    	emailstate: $('#email').hasClass('self-described'),
    	messagestate: $('#message').hasClass('self-described'), 
    }, 
    function(data) 
    {
        $("#formResponse").html(data).fadeIn('80');

        if ( data.indexOf("A carrier pigeon has been dispached!") >= 0 ) {
        	//only happens if the message is successful
        	$('.self-describing').each(function() {
	        	this.value=this.title;
	        });
        	$('#contact-form').hide();
        }

        $('.self-described').each(function() {
        	this.value=this.title;
        });

    }, 
    'text');   
    
    return false;
});


function objToString (obj) {
    var str = '';
    for (var p in obj) {
        if (obj.hasOwnProperty(p)) {
            str += p + '::' + obj[p] + '\n';
        }
    }
    return str;
}



