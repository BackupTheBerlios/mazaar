<?php
/**
 * @package Users
 * @author Ondrej Donek, ondrejd@gmail.com
 * @version 1.0
 * @since 18.Apr, 2005
 * 
 * @todo    Remake for driver generalization. (This means that authentication will be served by drivers such as Cookie, SimpleDB etc.).
 * @todo    Add any simple default authentication driver.
 * @todo    Create interface (or abstract class) for driver.
 */

require_once dirname(__FILE__).'/Cookie.inc';


/**
 * Serves user authentication.
 */
class Authentication extends Plugin 
{
    
    /**
     * Constructor. Extends standard package 
     * constructor for includes.
     */
    public function __construct( $name, $path )
    {
        parent::__construct( $name, $path );
    } // end Authentication::__construct( $name, $path );
    
    
    /**
     * Overi platnost hesla.
     */
    static function check()
    {
        // stuff for cookie calling
        $key = self::$preferences->getPref('');
        $name = self::$preferences->getPref('');
        $cypher = self::$preferences->getPref('');
        $mode = self::$preferences->getPref('');
        
        // this stuff is hardly based on predication that 
        // login form is the standart one or based on.
        if(isset($_POST['username']) && isset($_POST['userpass'])) {
            $db = Mazaar::$packages['DB'];
            $res = $db->prepare($db->getQuery('verifyUser'));
            $usr = $res->execute($_POST['username'],$_POST['userpass'])->fetch_row();
            if($usr) {
                $cookie = new Cookie($usr['ID'],$key,$name,$cypher,$mode);
                return $usr['ID'];
            } else {
                return false;
            } 
        }
        else {        
            try {
                $cookie = new Cookie(false,$key,$name,$cypher,$mode);
                return $cookie->validate();
            }
            catch( CookieException $e ) {};
        }
  } // end Authentication::check( $name, $pass )
  
  
} // End of class Authentication
?>