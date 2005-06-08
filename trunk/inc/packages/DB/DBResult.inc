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
abstract class DBResult implements Iterator
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
  public function __construct(DBStatement $stmt) {}  
  
  /**
   * Return named collumn in current index.
   * @var string Name of collumn.
   * @return mixed Return value of collumn or FALSE.
   */
  public function __get( $varname ) {}  
  
  /**
   * Return first item.
   */
  public function first() {}  
  
  /**
   * Return last item.
   */
  public function last() {}  
  
  /**
   * Return next item.
   */
  public function next() {}
  
  /**
   * Return previous item.
   */
  public function prev() {}  
  
  /**
   * Rewind position to start point.
   */
  public function rewind() {}  
  
  /**
   * Validate position.
   * @returns boolean Return TRUE if we don't reach end.
   */
  public function valid() {}  
  
  /**
   * Key
   * @return integer Returns current index.
   */
  public function key() {}  
  
  /**
   * Current value.
   * @return Returns value on current index.
   */
  public function current() {}
  
} // End of class DBResult


?>