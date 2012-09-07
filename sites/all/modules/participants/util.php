<?php
class ParticipantUtil{
  function participants(){
    $participants = db_select('node','n')
    ->fields('n')
    ->condition('type', 'participant')->execute()->fetchAll();
    $pk = array_map(function($x){return $x->nid;}, $participants);
    $pv = array_map(function($x){return $x->title;}, $participants);
    $participants_array = array_combine($pk, $pv);
    return $participants_array;
  }
  
  function tournaments(){
    $tournaments = db_select('node','n')
    ->fields('n')
    ->condition('type', array('round_robin'), 'IN')->execute()->fetchAll();
    $tk = array_map(function($x){return $x->nid;}, $tournaments);
    $tv = array_map(function($x){return $x->title;}, $tournaments);
    $tournaments_array = array_combine($tk, $tv);
    return $tournaments_array;
  }
  
  function matches($tid){
    $matches = db_select('node','n');
    $matches->join('matches', 'm', 'n.nid = m.nid');
    $matches->fields('m');
    $matches->orderBy('m.match_date', 'ASC');
    $matches = $matches->condition('m.tid', $tid)->execute()->fetchAll();
    return $matches;
  }
  
  function handle_participants($content){
    $names = preg_split("/((\r?\n)|(\r\n?))/", $content);
    $participants = db_select('node','n')
    ->fields('n')
    ->condition('type', 'participant')->execute()->fetchAll();
      
    foreach ($names as $name) {
      $exits = array_filter($participants, function($x) use($name){
        return $x->title == $name;
      });
      if(!$exits){
        $node = new stdClass();
        $node->type = 'participant';
        node_object_prepare($node);
        $node->title = $name;
        $node->language = LANGUAGE_NONE;
        node_save($node);
        drupal_set_message("Participant created: $name");
      }
    }
    drupal_set_message("Participants saved");
  }

  function hours_map(){
    $hours = array();
    $start = 10;
    $end = 17;
    $range = range($start, $end);
    foreach ($range as $h) {
      $hours[$h] = "$h";
    }
    return $hours;
  }
  function minutes_map(){
    $minutes = array();
    $range = array(0,15,30,45);
    foreach ($range as $m) {
      $hours[$m] = "$m";
    }
    return $hours;
  }
  
  function isWeekend($timestamp) {
    return (date('N', $timestamp) >= 6);
}
}
