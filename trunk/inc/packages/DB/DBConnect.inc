<?php
/**
 * @package DB
 * @author Ondrej Donek, <ondrejd@gmail.com>
 * @since 21.5.2005
 */
    

interface DBConnect 
{ 
    function connect();
    function execute($query);
    function prepare($query);
} // End of class DB

?>