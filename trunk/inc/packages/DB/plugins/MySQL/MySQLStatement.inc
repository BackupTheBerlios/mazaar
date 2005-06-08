<?php
#$Id: MySQLStatement.inc,v 1.1 2005/06/08 09:06:41 ondrejd Exp $

/**
 * @package     Mazaar
 * @author      Ondrej Donek, ondrejd@gmail.com
 * @version     0.1
 */



/**
 *
 */
class MySQLStatement extends DBStatement
{
  /** @var resource Result of db query. */
  public $result;  
  /** @var string DB query itself. */
  public $query;
  /** @var resource Handler of DB connection. */
  protected $dbh;
  public $binds;
  
  
  /**
   * Constructor.
   */
  public function __construct( $dbh, $query )
  {
    $this->query = $query;
    $this->dbh = $dbh;
    if( !is_resource($this->dbh) ) {
      throw new MySQLException( 'DB connnection is not valid resource', 0 );
    }
  } // end MySQLStatement::__construct( $dbh, $query )
  
  
  /**
   *
   */
  public function execute()
  {
    $binds = func_get_args();
    foreach( $binds as $index => $name ) {
      $this->binds[$index+1] = $name;
    }
    $cnt = 1;
    $query = $this->query;
    foreach( $this->binds as $ph => $pv ) {
        $query = str_replace( ":$cnt", mysql_escape_string($pv), $query );
        $cnt++;
    }
    $this->result = mysql_query( $query, $this->dbh );
    if( !$this->result ) {
      throw new MySQLException( 'MySQL query failed', 2 );
    }
    return $this;
  } // end MySQLStatement::execute()
  
  
  /**
   *
   */
  public function fetch_row()
  {
    if( !$this->result) {
      throw new MySQLException( 'Query not executed', 3 );
    }
    return mysql_fetch_assoc( $this->result );
  } // end MySQLStatement::fetch_row()
  
  
  /**
   *
   */
  public function fetch_assoc()
  {
    return mysql_fetch_assoc( $this->result );
  } // end MySQLStatement::fetch_assoc()
  
  
  /**
   *
   */
  public function fetchall_assoc()
  {
    $retval = array();
    while( $row = $this->fetch_assoc() ) {
      $retval[] = $row;
    }
    return $retval;
  } // end MySQLStatement::fetchall_assoc()
  
  
  /**
   * Get iterator.
   */
  function getIterator()
  {
    return new MySQL_Result( $this );
  } // end MySQLStatement::getIterator()
  
  
} // end of class MySQLStatement

?>