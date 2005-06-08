<?php
/**
 * Exceptions handler.
 */
class MySQLException extends DBException 
{
    public function __construct( $mess=false, $code=false )
    {
        switch($code) {
            case 0: // DB connnection is not valid resource
            case 1: // Unable to select DB table
            case 2: // MySQL query failed
            case 3: // Query not executed
            default:
                parent::__construct($mess,$code);
                return;
        }
    }
} // End of class MySQLException

?>