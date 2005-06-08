<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>
  <meta content="text/html; charset=UTF-8" http-equiv="content-type">
  <title>Př&iacute;stup byl odepřen</title>
  <style>
body,html,table,td {
font-family: Tahoma;
font-size: 11px;
}
h1 {
font-size: 16px;
}
h2 {
font-size: 14px;
}
a:link,a:visited {
color: #060;
text-decoration: underline;
}
a:hover {
color: #060;
text-decoration: none;
}
ul { padding: 2px 0px 2px 10px;
margin: 2px 0px 2px 10px;
list-style: square;
}
li { padding: 0px 0px 0px 10px;
margin: 0px 0px 0px 10px;
}
  </style>
</head>
<body>
<?php $ip = getenv ("REMOTE_ADDR");

$requri = getenv ("REQUEST_URI");
$servname = getenv ("SERVER_NAME");
$combine = $ip . " tried to load " . $servname . $requri ;
$combine1 = $servname . $requri ;

$httpref = getenv ("HTTP_REFERER");
$httpagent = getenv ("HTTP_USER_AGENT");

$today = date("D M j Y g:i:s a T"); 

$combine4 = "REMOTE_ADDR: " . $ip . 
"\r\nSERVER_NAME: " . $servname . 
"\r\nREMOTE_ADDR: ". $requri . 
"\r\nHTTP_REFERER: ". $httppref . 
"\r\nHTTP_USER_AGENT: ". 
$httpagent ."\r\nTODAY: ". $today;
$to = "ondrejd@gmail.com";
$subject = "dav.cz 404 Error Page";

$headers="Content-Type: text/html; charset=utf-8;\r\nTo: $to\r\nSubject: $subject\r\n";
iglu_mail(null,null,$combine4,$headers)
?>
<table style="width: 100%; text-align: left;" border="0" cellpadding="2"
 cellspacing="2">
  <tbody>
    <tr>
      <td>
      <h1>www.dav.cz - př&iacute;stup byl
odepřen (chyba 403)<br>
      </h1>
      </td>
      <td><br>
      </td>
    </tr>
    <tr>
      <td>Omlouv&aacute;me se,
ale na V&aacute;mi požadovanou URL&nbsp; (<a
 href="%3C?php%20echo%20$combine1;%20?%3E"><?php echo $combine1; ?></a>
) V&aacute;m (<?php echo $ip ?>) byl <span style="font-weight: bold;">odepřen
př&iacute;stup</span>.
Zkontrolujte si pros&iacute;m zadanou URL a v
př&iacute;padě přetrv&aacute;vaj&iacute;c&iacute;ch
probl&eacute;mů kontaktujte <a href="mailto:ondrejd@gmail.com">administr&aacute;tora</a>
těchto str&aacute;nek.<br>
      <br>
Snad V&aacute;m v lep&scaron;&iacute; orientaci pomůže
tento č&aacute;stečn&yacute; seznam str&aacute;nek tohoto
webu:<br>
      <ul>
        <li><a href="http://www.dav.cz/index.php">úvodní stránka</a></li>
        <li><a href="http://www.dav.cz/index-en.php">home page (english version)</a></li>
        <li><a href="http://www.dav.cz/index.php?pg=2">o nás</a></li>
        <li><a href="http://www.dav.cz/index.php?pg=3">služby pro firmy</a></li>
        <li><a href="http://www.dav.cz/index.php?pg=4">uchazeči o zaměstnání</a></li>
        <li><a href="http://www.dav.cz/index.php?pg=5">aktuální volná místa</a></li>
        <li><a href="http://www.dav.cz/index.php?pg=6">kontakt</a> </li>
      </ul>
      </td>
      <td>&nbsp; </td>
    </tr>
  </tbody>
</table>
<br>
<hr style="width: 100%; height: 2px;">
<table style="width: 100%; text-align: left;" border="0" cellpadding="2"
 cellspacing="2">
  <tbody>
    <tr>
      <td>
      <h2>Protokol o chybě 403<br>
      </h2>
      </td>
      <td>(bude odesl&aacute;n
administr&aacute;torovi)<br>
      </td>
    </tr>
    <tr>
      <td>REMOTE_ADDR<br>
      </td>
      <td style="text-align: left;"><?php echo $ip; ?> <br>
      </td>
    </tr>
    <tr>
      <td>SERVER_NAME<br>
      </td>
      <td><?php echo $servname; ?> <br>
      </td>
    </tr>
    <tr>
      <td>REQUEST_URI<br>
      </td>
      <td><?php echo $requri; ?> <br>
      </td>
    </tr>
    <tr>
      <td><span class="pi">HTTP_REFERER</span></td>
      <td><?php echo $httpref; ?> <br>
      </td>
    </tr>
    <tr>
      <td><span class="pi">HTTP_USER_AGENT</span></td>
      <td><?php echo $httpagent; ?> <br>
      </td>
    </tr>
    <tr>
      <td>TODAY<br>
      </td>
      <td><?php echo $today; ?> <br>
      </td>
    </tr>
  </tbody>
</table>
<hr style="width: 100%; height: 2px;">
<table style="width: 100%; text-align: left;" border="0" cellpadding="2"
 cellspacing="2">
  <tbody>
    <tr>
      <td>&copy; 2004 <a href="mailto:ondrejd@gmail.com">Ondřej
Doněk</a>.</td>
      <td style="text-align: right;"><a
 href="http://www.ondrejd.iglu.cz/products/mazaarCMS">mazaarCMS</a><br>
      </td>
    </tr>
  </tbody>
</table>
</body>
</html>
