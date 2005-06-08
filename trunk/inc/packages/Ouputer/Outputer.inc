<?php
#$Id: Outputer.inc,v 1.1 2005/06/08 09:06:41 ondrejd Exp $
/**
 * @package Outputer
 * @author Ondrej Donek, <ondrejd@gmail.com>
 * @since Apr 29, 2005
 */
 
 
require_once dirname(__FILE__).'/OutputerException.inc.php';
require_once dirname(__FILE__).'/OutputerDriver.inc.php';


/**
 * Outputer tranform XML data into any output.
 */
class Outputer
{
	/** @var string Output format. */
	private $output_format;
	/** @var string Template directory (stored in main config.xml). */
	private $template_dir;
	
	/** 
	 * These variables contain identifiers of plugin and it's' 
	 * action (this is needed for driver when finding appropriate 
	 * file with XSL template).
	 * 
	 * @var string Plugin identifier.
	 * @var string Action identifier.
	 */
	private $plugin;
	private $action;
	
	/** @var object Handler on transformer. */
	private $transformer;	
	/** @var object Proccessed DOMDocument. */
	private $DOM;
	/** @var object Root element of DOMDocument. */
	private $root_element;
	/** @var object Response element of DOMDocument. */
	private $response_element;
	
	/** @var boolean Debug mode. */
	private $debug = false;
	
	
	/**
	 * Constructor.
	 */
	public function __construct()
	{
		$url_parser = core::getInstance('url_parser');
		$config = core::getInstance('config');
		
		$this->output_format = $url_parser->get_output_format();
		$this->template_dir = $config->get_config()->template_dir;		
		$this->plugin = $url_parser->get_plugin();
		$this->action = $url_parser->get_action();		
		$this->debug = ($config->get_config()->debug == 'true') ? true : false;
	} // end Outputer::__construct()
	
	
	/**
	 * Returns output format.
	 * @return string
	 */
	public function getOutputFormat()
	{
		return (string)$this->output_format;
	} // end Outputer::getOutputFormat()
	
	
	/**
	 * Initialize DOMDocument. (Loads global DOMDocument and save into it
	 * DOCTYPE and create root element.)
	 * 
	 * @return object Created DOMDocument.
	 */
	public function InitDOM()
	{
		if($this->DOM instanceof DOMDocument) {
			throw new OutputerException( 'DOMDocument is already inicialized!',110 );
		} 
		
	} // end Outputer::InitDOM()
	
	
	/**
	 * Returns DOMDocument.
	 * @return object DOMElement.
	 */
	public function getDOM()
	{
		if($this->DOM instanceof DOMDocument) {
			return $this->DOM;
		}
		else {
			throw new OutputerException( 'Could not return DOMDocument. DOMDocument is not initialized.', 111 );
		}
	} // end Outputer::getDOM()
	
	
	/**
	 * Validates DOMDocument, if is correctly formed.
	 * @return boolean Returns TRUE if DOMDocument is valid.
	 */
	private function validateDOM()
	{
		if( $this->DOM instanceof DOMDocument ) {
			if( $this->DOM->schemaValidate() ) {
				return true;
			}
			else {
				return false;
			}
		} 
		else {
			throw new OutputerException( 'Could not validate DOMDocument. DOMDocument is not initialized.', 113 );
		}
	} // end Outputer::validateDOM()
	
	
	/**
	 * Returns root element of DOMDocument.
	 * @return object DOMElement.
	 */
	public function getRootElement()
	{
		if($this->root_element instanceof DOMElement){
			return $this->root_element;
		}
		else {
			throw new OutputerException( 'Could not return DOMElement. DOMDocument is not initialized.', 112 );
		}
	} // end Outputer::getRootElement()
	
	
	/**
	 * Returns response element of DOMDocument.
	 * @return object DOMElement.
	 */
	public function getResponseElement()
	{
		if($this->response_element instanceof DOMElement){
			return $this->response_element;
		}
		else {
			throw new OutputerException( 'Could not return DOMElement. DOMDocument is not initialized.', 112 );
		}
	} // end Outputer::getResponseElement()
	
	
	/**
	 * Load and set up transformer.
	 */
	private function loadTranformer()
	{
		$driver_file = dirname(__FILE__).'/drivers/'.$this->output_format.'.inc.php';
		
		if( !is_readable($driver_file)) {
			throw new OutputerException( 'Tranformation driver not founded.', 114 );
		}
		else { 
			require_once $driver_file;
			if( !class_exists($this->output_format) ) {
				throw new OutputerException( 'Class of transformation driver not founded.', 115 );
			}
			else {
				$this->transformer = new $this->output_format( $this->DOM, $this->template_dir, $this->plugin, $this->action );
			}
		}
	} // end Outputer::loadTransformer()
	
	
} // End of class Outputer

?>
