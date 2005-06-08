<?php
#$Id: OutputerDriver.inc,v 1.1 2005/06/08 09:06:41 ondrejd Exp $
/**
 * @package Outputer
 * @author Ondrej Donek, <ondrejd@gmail.com>
 * @since Jun 1, 2005
 */
 

/**
 * Interface for Outputer driver.
 */
interface OutputerDriver
{
	
	/**
	 * Initialize of the driver.
	 * @param object DOMDocument.
	 * @param string Path to directory with templates.
	 * @param string Plugin identificator.
	 * @param string Action identificator.
	 */
	public function __construct( $DOM, $templates_dir, $plugin, $action );
	
	/**
	 * Perform transformation.
	 */
	public function execute();	 
	
} // End of interface OutputerDriver

?>
