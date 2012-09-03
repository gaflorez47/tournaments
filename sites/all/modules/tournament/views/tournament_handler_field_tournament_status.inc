<?php

/**
 * @file
 * Views handler for Tournament module
 */

class tournament_handler_field_tournament_status extends views_handler_field {
  function render($values) {
    return _tournament_get_status($values->{$this->field_alias});
  }
}
