<?php
/**
 * @package DB
 * @author Ondrej Donek, <ondrejd@gmail.com>
 * @since 21.5.2005
 */


require_once dirname(__FILE__).'/DBException.inc';
require_once dirname(__FILE__).'/DBConnect.inc';
require_once dirname(__FILE__).'/DBStatement.inc';
require_once dirname(__FILE__).'/DBResult.inc';
    

/**
 * Serves database connection and data handling.
 */
class DB extends Package implements DBConnect
{
    /** @var object DB connection provider. */
    private $provider;
    /** @var object QueryStorage provider. */
    private $query_storage;
  
  
    /**
     * Constructor.
     */
    public function __construct($name)
    {
        parent::__construct('DB');
        // create DB connection provider
        if(class_exists((string)self::$preferences->getPref('provider'))) {
            $prov = (string)self::$preferences->getPref('provider');
            $this->provider = new $prov($prov,$name);
        }
        // create QueryStorage provider
        if(class_exists((string)self::$preferences->getPref('querystorage.provider'))) {
            $qprov = (string)self::$preferences->getPref('querystorage.provider');
            $this->query_storage = new $qprov($qprov,$name);
        }
        $this->connect();
    } // end DB::__construct( $user, $pass, $dbhost, $dbname )
  
  
    /**
     * Create connection to DB.
     * 
     */
    public function connect()
    {
        return $this->provider->connect();
    } // end DB::connect();
  
  
    /**
     * Check if is driver connected to database.
     * @return boolean 
     */
    public function isConnected()
    {
        if( !$this->provider->isConnected() ) {
            return false;
        } else {
            return true;
        }
    } // end DB::isConnected(); 
  
  
    /**
     * Execute pre-prepared query.
     * @param string SQL query.
     */
    public function execute( $query )
    {
        if( !$this->provider->isConnected() ) {
            $this->connect();
        }
        return $this->provider->execute($query);
    } // end DB::execute( $query )
  
  
    /**
     * Prepare SQL query.
     * @param string $query
     */
    public function prepare( $query )
    {
        if( !$this->provider->isConnected() ) {
            $this->connect();
        }
        return $this->provider->prepare($query);
    } // end DB::prepare( $query )
  
  
    /**
     * Returns query string.
     * @param string Query title.
     * @return string
     */
    public function getQuery($query)
    {
        return $this->query_storage->getQuery($query);
    } // end DB::getQuery($query)
       
} // End of class DB

?>