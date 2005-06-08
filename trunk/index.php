<?php
//ob_start();
header( "Content-Type: text/html;charset=UTF-8 \r\n" );

require_once 'inc/core/Mazaar.inc';

// Mazaar initialization
$site = new Mazaar('Mazaar','inc/config/Mazaar.xml');

// loading core modules (this modules depends 
// on installation and they couldn't be updated 
// removed or added without re-installation.

highlight_string("
require_once 'inc/Mazaar.inc';
\$site = new Mazaar('Mazaar','inc/config/Mazaar.xml');
\$db = Mazaar::getPackage('DB',true);
\$res = \$db->prepare($db->getQuery('loadUser'));
\$usr = $res->execute(1)->fetch_row();
echo \$usr['username'];
");

$db = Mazaar::getPackage('DB',false);
$res = $db->prepare($db->getQuery('loadUser'));
$usr = $res->execute(1)->fetch_row();
echo $usr['username'];

highlight_string("
echo \$site->DB->getQuery('verifyUser');
");

// echo $site->DB->getQuery('verifyUser');

// $user = Mazaar::getPackage('User',false);

/**
$templater = new Templater()
$user = Mazaar::getInstance('User');

// page holds main template
$page = $templater->prepareTemplate( 'index.html' );

if(!$user->isLogged()) {
  $page->setBinding('loginform',$templater->printTemplate('login.html'));
}
else {
  $t = $templater->prepareTemplate('logout.html');
  $t->setBinding('username',$user->user['username']);
  $page->setBinding('logoutform',$t->getTemplate());
  unset($t);
}

echo $page->getTemplate();
*/
//ob_end_flush();
?>