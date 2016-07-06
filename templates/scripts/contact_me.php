<?php
// Check for empty fields
if(empty($_POST['name'])  		||
   empty($_POST['email']) 		||
   empty($_POST['message'])	||
   !filter_var($_POST['email'],FILTER_VALIDATE_EMAIL))
   {
	echo "No arguments Provided!";
	return false;
   }

$name = $_POST['name'];
$email_address = $_POST['email'];
$phone = $_POST['phone'];
$message = $_POST['message'];

// Create the email and send the message
$to = 'test@freifunk.net'; // Add your email address inbetween the '' replacing yourname@yourdomain.com - This is where the form will send a message to.
$email_subject = "Kontaktanfrage von  $name";
$email_body = "Eine neue Nachricht wurde über das Kontaktformular versendet.\n Bitte antworte in Kopie an die Mailinglist damit alle wissen das die Frage beantwortet wurde \n\n"."Hier die Details:\n\nName: $name\n\nE-Mail: $email_address\n\nTelefon: $phone\n\nNachricht:\n$message";
$headers = "From: kontakt@freifunk-myk.de\n"; // This is the email address the generated message will be from. We recommend using something like noreply@yourdomain.com.
$headers .= "Reply-To: $email_address";
mail($to,$email_subject,$email_body,$headers);
return true;
?>
