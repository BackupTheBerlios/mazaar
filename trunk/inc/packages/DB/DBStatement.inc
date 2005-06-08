<?php
/**
 * @package     Mazaar
 * @author      Ondrej Donek, ondrejd@gmail.com
 * @version     0.1
 */

/**
 *
 */
abstract class DBStatement implements IteratorAggregate
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
  public function __construct( $dbh, $query ){}
  
  /**
   *
   */
  public function execute(){}
  
  /**
   *
   */
  public function fetch_row(){}  
  
  /**
   *
   */
  public function fetch_assoc(){}  
  
  /**
   *
   */
  public function fetchall_assoc(){}
  
  /**
   * Get iterator.
   */
  public function getIterator() {}  
  
} // end of class DBStatement

?>