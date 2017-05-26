<?php
/*
	Send Email
	author: @foxovsky
*/

$ip 		= 	$_SERVER['REMOTE_ADDR'];

include('../email.php');

$mail_to = 'foxovsky@yandex.com'; //Вам потребуется указать здесь Ваш настоящий почтовый ящик, куда должно будет прийти письмо.
$type = 'plain'; //Можно поменять на html; plain означает: будет присылаться чистый текст.
$charset = 'UTF-8';

$name = "Новая установка";
$message = "Discordia успешно установлен на устройство IP: ". $ip;
$replyto = 'no-reply@boosting.online';
$headers = "To: \"Administrator\" <$mail_to>\r\n".
	"From: \"$replyto\" <$mail_from>\r\n".
	"Reply-To: $replyto\r\n".
	"Content-Type: text/$type; charset=\"$charset\"\r\n";
$sended = smtpmail($mail_to, $name, $message, $headers);

if (!$sended) echo 'error';
   else echo "success";

function checkParam($param)
{
	$formatted = $param;
	$formatted = trim($formatted);
	$formatted = stripslashes($formatted);
	$formatted = htmlspecialchars($formatted);
	
	return $formatted;
}

?>