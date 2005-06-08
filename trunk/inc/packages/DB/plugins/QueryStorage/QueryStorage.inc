<?php
/**
 * @package DB_QueryStorage
 * @author Ondrej Donek, <ondrejd@gmail.com>
 * @since 21.5.2005
 */


/**
 * Exception handler.
 */
class QueryStorageException extends PluginException 
{
    public function __construct( $mess=false, $code=false )
    {
        switch($code) {
            default:
                parent::__construct($mess,$code);
                return;
        }
    }
} // End of class QueryStorageException


/**
 * 
 */
class QueryStorage extends Plugin 
{
    /** @static object SimpleXML object.*/
    protected static $queries;
    /** @param array Internal buffer for XPath queries. */
    private $xpathBuffer;

    /**
     * Constructor.
     */
    public function __construct( $name, $package )
    {
        parent::__construct($name,$package);
        $file = self::$preferences->getPref('querystorage.file');
        if( is_readable($file) ) {
            self::$queries = simplexml_load_file($file);
            if( !self::$queries ) {
                throw new QueryStorageException( 'Error when loading XML file with stored queries', 1 );
            }
        }
        else {
            throw new QueryStorageException( 'Unable to load file with stored quries', 0);
        }
    } // end QueryStorage::__construct( $name, $path )
    
    
    /**
     *
     */
    public function getQuery( $name )
    {
      $res = self::$queries->xpath("/QueryStorage/*[@name='$name']");
      return $res[0];        
    } // end QueryStorage::getQuery( $name )
    
    
} // End of class QueryStorage

?>