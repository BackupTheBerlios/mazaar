<?php
/**
 * Class for handling MySQL exceptions.
 */
abstract class DBException extends PackageException
{
  public function __construct( $mess=false, $code=false ) {}
} // end of Class DBException

?>