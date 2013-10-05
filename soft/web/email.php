<?php
if(isset($_POST['email'])) {

	$email_to = "chwalsh@mit.edu";
    $email_subject = "draw_bot";

    function died($error) {
        echo "<p>".$error."</p>";  
        die();
    }
    
    if(!isset($_POST['name']) ||
        !isset($_POST['email']) ||
        !isset($_POST['message'])) {
        died('Your form is a bit funky!');       
    }

    $name = $_POST['name']; // required
    $email_from = $_POST['email']; // required
    $message = $_POST['message']; // required

    $error_message = "";
    $email_exp = '/^[A-Za-z0-9._%-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,4}$/';

	if(!preg_match($email_exp,$email_from)) {
		$error_message .= "Bro! There's something wrong with your email address!<br />";
	}
	    $string_exp = "/^[A-Za-z .'-]+$/";
	if(!preg_match($string_exp,$name)) {
		$error_message .= "Woaahhh there, let's keep names within the alphabet!<br/>";
	}
	if(strlen($message) < 2 || strlen($name) < 1 || strlen($email_from) < 1 || $_POST['namestate'] == 'true' || $_POST['emailstate'] == 'true' || $_POST['messagestate'] == 'true' ) {
		$error_message = "Forgetting something?";
	}


	if(strlen($error_message) > 0) {
		died($error_message);
	}

	$email_message = "";
     
    function clean_string($string) {
      $bad = array("content-type","bcc:","to:","cc:","href");
      return str_replace($bad,"",$string);
    }
     
    $email_message .= clean_string($message)."\n\n";
    $email_message .= clean_string($name)."\n";
    $email_message .= clean_string($email_from);


    $headers = 'From: '.$email_from."\r\n".
		'Reply-To: '.$email_from."\r\n" .
		'X-Mailer: PHP/' . phpversion();

	@mail($email_to, $email_subject, $email_message, $headers);

    echo '<h3>A carrier pigeon has been dispached!</h3>';

}
?>






