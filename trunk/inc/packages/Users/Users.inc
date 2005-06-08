<?php
/**
 * @package  Users
 * @author Ondrej Donek, ondrejd@gmail.com
 * @since 14.Apr, 2005
 */


require_once dirname(__FILE__).'/UsersException.inc';
require_once dirname(__FILE__).'/User.inc';
 

class Users extends Package
{
    /** @var object Actually logged user. */
    private $user;
    
    
    /**
     * Constructor.
     */
    public function __construct($name)
    {
        parent::__construct($name);
    } // end Users::__construct($name);
    
    
    /**
     * Load users data from db.
     */
    private function getUser()
    {
        if($this->user instanceof User) {
            return $this->user;
        } else {
            return false;
        }
    } // end Users::_getUser()
    
} // End of class Users
?>
