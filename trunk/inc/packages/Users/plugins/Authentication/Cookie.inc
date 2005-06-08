<?php
/**
 * @package Users
 * @author Ondrej Donek, ondrejd@gmail.com
 * @version 1.0
 * @since 18.Apr, 2005
 */


/**
 * CookieException handling.
 */
class CookieException extends MyException 
{
    public function __construct( $mess=false, $code=false )
    {
        switch($code) {
            case 1100: // Cookie not found.
            case 1101: // Incomplete or not valid cookie.
            case 1102: // Inconsistence in version of cookie.
            case 1103: // Cookie expired.
                // this are not critical error so we push user through 
                // and destroy cookie
                unset($_COOKIE[(string)Cookie::$cookiename]);
                return;
            default:
                parent::__construct($mess,$code);
                return;
        }
    }
} // End of class CookieException



/**
 * Cookies handling
 */
class Cookie
{
    /** @var date Date of cookie's creation.. */
    private $created;
    /** @var string UserID of passed cookie. */
    private $userid;
    /** @var string Version of passed cookie. */
    private $version;
  
    /** @var resource Mcrypt handler. */
    private $td;
  
    /** @static string Used alghoritm. */
    static $cypher;
    /** @static string Mode of mcrypt. */
    static $mode;
    /** @static string Security key. */
    static $key;
  
    /** @static string Cookie name. */
    static $cookiename;
    /** @static string Cookie version. */
    static $myversion = '1';
  
    /** @static int Time of cookies's expiration. */
    static $expiration = 600; // 30 dnu
    /** @static int Time when cookie's renew. */
    static $warning = 300;
  
    /** @static char Glue in cookie string. */
    static $glue = '|';
  
  
  
    /**
     * Constructor.
     * @param string User ID.
     */
    public function __construct($userid=false,$key,$name,$cypher,$mode)
    {
        self::$key = md5($key);
        self::$cookiename = $name;
        self::$cypher = $cypher;
        self::$mode = $mode;
        $this->td = mcrypt_module_open( self::$cypher, '', self::$mode, '' );
        if($userid) {
            $this->userid = $userid;
            if( !key_exists("".self::$cookiename."",$_COOKIE) ) {
                $this->set();
                return;
            }
        } else {
            if( key_exists("".self::$cookiename."",$_COOKIE) ) {
                $buffer = $this->_unpackage( $_COOKIE["".self::$cookiename.""] );
            } else {
                throw new CookieException( 'Cookie not found.', 1100 );
            }
        }
    } // end Cookie::__construct( $userid = false )
  
  
    /**
     * Set cookie.
     */
    public function set()
    {
        $cookie = $this->_package();
        setcookie( self::$cookiename, $cookie, time() + self::$expiration );
    } // end Cookie::set()
  
  
    /**
     * Check cookie validity. If's cookie valid but before expiration set cookie again.
     * @return userid.
     */
    public function validate()
    {
        if( !$this->version || !$this->created || !$this->userid ) {
            throw new CookieException( 'Incomplete or not valid cookie.', 1101 );
        }
        if( $this->version != self::$myversion ) {
            throw new CookieException( 'Inconsistence in version of cookie.', 1102 );
        }
        if( time() - $this->created > self::$expiration ) {
            throw new CookieException( 'Cookie expired.', 1103 );
        }
        else if( time() - $this->created > self::$warning ) {
            $this->set();
        }
        return $this->userid;
    } // end Cookie::validate()
  
  
    /**
     * Logout user (set cookie validity up to 0 time).
     */
    public function logout()
    {
        setcookie( self::$cookiename, '', 0 );
    } // end Cookie::logout()
  
  
    /**
     * Package cookie.
     * @return string Encrypted and packaged cookie.
     */
    private function _package() 
    {
        $parts = array( self::$myversion, time(), $this->userid );
        $cookie = implode( self::$glue, $parts );
        return $this->_encrypt( $cookie );
    } // end Cookie::_package()
  
  
    /**
     * Unpackage cookie.
     * @param array Array of cookie fields.
     */
    private function _unpackage( $cookie )
    {
        $buffer = $this->_decrypt( $cookie );
        list( $this->version, $this->created, $this->userid ) = explode( self::$glue, $buffer );
        if( $this->version != self::$myversion || !$this->created || !$this->userid ) {          
            throw new CookieException( 'Inconsistence in version of cookie.', 1102 );
        }
    } // end Cookie::_unpackage( $cookie )
  
  
    /**
     * Encrypt cookie.
     * @param string Packaged cookie.
     * @return string Encrypted cookie.
    */
    private function _encrypt( $plaintext )
    {
        $iv = mcrypt_create_iv( mcrypt_get_iv_size( self::$cypher, self::$mode ), MCRYPT_RAND );
        mcrypt_generic_init( $this->td, self::$key, $iv );
        $crypttext = mcrypt_generic( $this->td, $plaintext );
        mcrypt_generic_deinit( $this->td );
        return $iv.$crypttext;
    } // end Cookie::_encrypt( $plaintext )
  
  
    /**
     * Decrypt cookie.
     * @param string Encrypted cookie.
     * @return string Decrypted but packaged cookie.
     */
    private function _decrypt( $crypttext )
    {
        $ivsize = mcrypt_get_iv_size( self::$cypher, self::$mode );
        $iv = substr( $crypttext, 0, $ivsize );
        $crypttext = substr( $crypttext, $ivsize );
        mcrypt_generic_init( $this->td, self::$key, $iv );
        $plaintext = mdecrypt_generic( $this->td, $crypttext );
        mcrypt_generic_deinit( $this->td );
        return $plaintext;
    } // end Cookie::_decrypt( $crypttext )
  
  
    /**
     * Set cookie's time of creation.
     */
    private function _reissue()
    {
        $this->created = time();
    } // end Cookie::_reissue()
    
  
} // End of class Cookie
?>