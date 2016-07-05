<?php

/**
 * An individual nodeinfo item.
 */
class NodeInfo extends WireData {

  protected $page;

  public function __construct() {
    // define the fields that represent our NodeInfo
    $this->set('ipv6', '');
    $this->set('lastconnect', '');
    $this->set('hardware', '');
    $this->set('firmware', '');
    $this->set('lat', '');
    $this->set('long', '');
    $this->set('address', '');
    $this->set('online', false);
  }

  /**
   * Set a value to the nodeinfo fields
   */
  public function set($key, $value) {
    if($key == 'page'){
      $this->page = $value;
      return $this;
    } else if($key == 'lastconnect') {
      //convert date/time string to unix timestamp
      if($value && !ctype_digit("$value")) $value = strtotime($value);

      // sanitized date value is always an integer
      $value = (int) $value;
    } else if($key == 'ipv6' ||
              $key == 'lat' ||
              $key == 'long' ||
              $key == 'firmware' ||
              $key == 'hardware' ||
              $key == 'address') {
      // regulare text sanitizer
      $value = $this->sanitizer->text($value);
    } else if($key == 'online') {
      // boolean sanitizer
      $value = $this->sanitizer->bool($value);
    }

    return parent::set($key, $value);
  }

  /**
   * Retrieve a value from the nodeinfo
   */
  public function get($key) {
    $value = parent::get($key);

    // if the page's output formatting is on, the we'll return formatted values
    if($this->page && $this->page->of()) {
      if($key == 'lastconnect'){
        // format a unix timestamp to a date string
        $value = date(self::dateFormat, $value);

      } else if($key == 'ipv6' ||
                $key == 'lat' ||
                $key == 'long' ||
                $key == 'firmware' ||
                $key == 'hardware' ||
                $key == 'address') {
        // return entity encoded versions of strings
        $value = $this->sanitizer->entities($value);
      } else if($key == 'online') {
        // boolean
        $value = $this->sanitizer->entities($value);
      }
    }

    return $value;
  }

  /**
   * Provide a default rendering for node information
   */
  public function renderNodeInfo(){
    // render page's output formatting state
    $of = $this->page->of();
    // turn on output formatting for our rendering (if it's not already on)
    if(!$of) $this->page->of(true);
    $out = "<p><strong>$this->date</strong><br /><em>$this->ipv6</em><br />$this->address</p>";
    if(!$of) $this->page->of(false);
    return $out;
  }

  /**
   * Return a string to representing this nodeinfo
   */
  public function __toString(){
    return $this->renderNodeInfo();
  }
}

 ?>
