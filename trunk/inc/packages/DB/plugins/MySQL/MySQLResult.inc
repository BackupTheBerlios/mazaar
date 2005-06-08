<?php
/**
 * @package     Mazaar
 * @author      Ondrej Donek, ondrejd@gmail.com
 * @version     0.1  
 */


/**
 * Trida pro zpracovani vysledku dotazu 
 * databazi.
 */
class MySQLResult extends DBResult
{
  protected $stmt;
  protected $result = array();
  private $rowIndex = 0;
  private $currIndex = 0;
  protected $max = 0;
  private $done = false;
  
  
  /**
   * Constructor.
   */
  public function __construct(MySQLStatement $stmt)
  {
    $this->stmt = $stmt;
  } // end MySQLResult::__construct(MySQLStatement $stmt)
  
  
  /**
   * Return named collumn in current index.
   * @var string Name of collumn.
   * @return mixed Return value of collumn or FALSE.
   */
  public function __get( $varname )
  {
    if( array_key_exists( $value, $this->result[$this->currIndex]) ) {
      return $this->result[$this->currIndex][$value];
    }
    else {
      return false;
    }
  } // end MySQLResult::__get( $varname )
  
  
  /**
   * Return first item.
   */
  public function first()
  {
    if( !$this->result ) {
      $this->result[$this->rowIndex++] = $this->stmt->fetch_assoc();
    }
    $this->currIndex = 0;
    return $this;
  } // end MySQLResult::first()
  
  
  /**
   * Return last item.
   */
  public function last()
  {
    if( !$this->done ) {
      array_push( $this->result, $this->stmt->fetchall_assoc() );
    }
    $this->done = true;
    $this->currIndex = $this->rowIndex = count( $this->result ) - 1;
    return $this;
  } // end MySQLResult::last()
  
  
  /**
   * Return next item.
   */
  public function next()
  {
    if( $this->done && $this->max == $this->currIndex ) {
      return false; 
    }
    $offset = $this->currIndex + 1;
    if( !$this->result[$offset] ) {
      $row = $this->stmt->fetch_assoc();
      if( !$row ) {
        $this->done = true;
        $this->max = $this->currIndex;
        return false;
      }
      $this->result[$offset] = $row;
      ++$this->rowIndex;
      ++$this->currIndex;
      return $this;
    }
    else {
      ++$this->currIndex;
      return $this;
    }
  } // end MySQLResult::next()
  
  
  /**
   * Return previous item.
   */
  public function prev()
  {
    if( $this->currIndex == 0 ) {
      return false;
    }
    --$this->currIndex;
    return $this;
  } // end MySQLResult::prev()
  
  
  /**
   * Rewind position to start point.
   */
  public function rewind()
  {
    $this->currIndex = 0;
  } // end MySQLResult::rewind()
  
  
  /**
   * Validate position.
   * @returns boolean Return TRUE if we don't reach end.
   */
  public function valid()
  {
    if( $this->done && $this->max == $this->currIndex ) {
      return false; 
    }
    return true;
  } // end MySQLResult::valid()
  
  
  /**
   * Key
   * @return integer Returns current index.
   */
  public function key()
  {
    return $this->currIndex;
  } // end MySQLResult::key()
  
  
  /**
   * Current value.
   * @return Returns value on current index.
   */
  public function current()
  {
    return $this->result[$this->currIndex];
  } // end MySQLResult::current()
  
  
} // End of class MySQLResult


?>