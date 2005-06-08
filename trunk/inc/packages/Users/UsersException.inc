<?php
/**
 * @package  Users
 * @author Ondrej Donek, ondrejd@gmail.com
 * @since 5.Jun, 2005
 */


/**
 * UsersExceptions handler.
 */
class UsersException extends PackageException 
{
    public function __construct( $mess=false, $code=false )
    {
        switch($code) {
            default:
                parent::__construct($mess,$code);
                return;
        }
    }
} // End of class UsersException 

?>