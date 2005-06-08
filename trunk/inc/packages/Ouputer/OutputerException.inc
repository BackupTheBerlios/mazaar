<?php
#$Id: OutputerException.inc,v 1.1 2005/06/08 09:06:41 ondrejd Exp $
/**
 * @package Outputer
 * @author Ondrej Donek, <ondrejd@gmail.com>
 * @since Apr 29, 2005
 */


/**
 * Outputer exception handling.
 */
class OutputerException extends Core_exception
{
	
	public function __construct($mess=false, $code=false)
	{
		switch($code)
		{
			// Outputer exceptions
			case 101: //
			case 110: // DOMDocument is already inicialized!		
			case 111: // Could not return DOMDocument. DOMDocument is not initialized.		
			case 112: // Could not return DOMElement. DOMDocument is not initialized.
			case 113: // Could not validate DOMDocument. DOMDocument is not initialized.
			case 114: // Tranformation driver not founded.
			case 115: // Class of transformation driver not founded.
				return;
			
			// Driver exceptions
			case 201: // Driver couldn\'t found template file.
			case 202: // Driver couldn\'t load given DOMDocument.
			case 203: // Driver couldn\'t create XSLTProcessor.
			case 204: // Driver couldn\'t load template file.
				return;
			
			default:
				parent::__construct($mess,$code);
				return;
		}
	} // end OutputerException::__construct($mess=false,$code=false)
	
} // End of class OutputerException

?>
