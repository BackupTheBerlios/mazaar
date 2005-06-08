<?php
/**
 * @package     Mazaar
 * @author      Ondrej Donek, ondrejd@gmail.com
 * @version     0.1
 * @desc        Interface for DB connection.
 */
 

require_once dirname(__FILE__).'/MySQLException.inc';
require_once dirname(__FILE__).'/MySQLStatement.inc';
require_once dirname(__FILE__).'/MySQLResult.inc';


/**
 * Trida obsluhujici pripojeni k MySQL databazi.
 *
 * <code>
 *   $dbh = new DB_Mysql('testuser','testpass','localhost','testdb');
 *   $stmt = $dbh->prepare( "SELECT *
 *                           FROM users 
 *                           WHERE name = :1");
 *   $stmt->execute($name);
 * </code>
 */
class MySQL extends Plugin implements DBConnect 
{
    /**
     * Variables for connection to database.
     * @var string User name.
     * @var string User password.
     * @var string Database host.
     * @var string Database name.
     */
    protected $username;
    protected $userpass;
    protected $dbhost;
    protected $dbname;
    /** @var resource DB connection handler. */
    protected $dbh; 
  
  
    /**
     * Constructor of driver (generic mazaar plugin).
     * @param string Driver (plugin) name.
     * @param string Parent package name.
     */
    public function __construct($driver,$package)
    {
        parent::__construct($driver,$package);
        $this->username = self::$preferences->getPref('username');
        $this->userpass = self::$preferences->getPref('userpass');
        $this->dbhost = self::$preferences->getPref('dbhost');
        $this->dbname = self::$preferences->getPref('dbname');
    } // end MySQL::__construct($user,$pass,$dbhost,$dbname )
  
  
    /**
     * Create connection to database.
     */
    public function connect()
    {
        $this->dbh = mysql_pconnect($this->dbhost,$this->username,$this->userpass);
        if( !is_resource($this->dbh) ) {
            throw new MySQLException( 'DB connnection is not valid resource', 0 );
        }
        if( !mysql_select_db($this->dbname, $this->dbh) ) {
            throw new MySQLException( 'Unable to select DB table', 1 );
        }
    } // end MySQL::connect()
  
  
    /**
     * Check if is driver connected to database.
     * @return boolean 
     */
    public function isConnected()
    {
        if(!$this->dbh) {
            return false;
        } else {
            return true;
        }
    } // end MySQL::isConnected(); 
  
  
    /**
     * Execute pre-prepared MySQL query.
     * @param string MySQL query
     * @return object MySQLStatement object.
     */
    public function execute( $query )
    {
        if(!$this->isConnected()) {
            $this->connect();
        }
        $ret = mysql_query($query, $this->dbh);
        if( !$ret ) {
            throw new MySQLException( 'MySQL query failed', 2 );
        }
        else if( !is_resource($ret) ) {
            return true;
        } else {
            $stmt = new MySQLStatement( $this->dbh, $query );
            $stmt->result = $ret;
            return $stmt;
        } 
    } // end MySQL::execute( $query )
  
  
    /**
     * Prepare MySQL query for execute.
     * @param string MySQL query.
     * @return object MySQLStatement object.
     */
    public function prepare( $query )
    {
        if(!$this->isConnected()) {
            $this->connect();
        }
        return new MySQLStatement( $this->dbh, $query );
    } // end MySQL::prepare( $query )
  
  
} // end of class MySQL


?>