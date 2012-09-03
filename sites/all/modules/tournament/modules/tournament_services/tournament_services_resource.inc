<?php

/**
 * @file
 * Tournament resource.
 */

/**
 * Define the tournament CRUD
 */
function _tournament_resource_definition() {
  return array(
    'tournament_details' => array(
      'index' => array(
        'file' => array('type' => 'inc', 'module' => 'tournament_services', 'name' => 'tournament_services_resource'),
        'help' => 'Retrieves tournament data',
        'callback' => '_tournament_details_resource_retrieve',
        'access callback' => 'user_is_logged_in',
        'access arguments' => array('view'),
        'access arguments append' => TRUE,
        'args' => array(
          array(
            'name' => 'tid',
            'type' => 'int',
            'description' => 'The id of the tournament for which to retrieve the details.',
            'source' => array('param' => 'tid'),
            'optional' => FALSE,
          ),
        ),
      ),
    ),
    'tournament_participants' => array(
      'index' => array(
        'file' => array('type' => 'inc', 'module' => 'tournament_services', 'name' => 'tournament_services_resource'),
        'help' => 'Retrieves tournament participant data',
        'callback' => '_tournament_participants_resource_retrieve',
        'access callback' => 'user_is_logged_in',
        'access arguments' => array('view'),
        'access arguments append' => TRUE,
        'args' => array(
          array(
            'name' => 'tid',
            'type' => 'int',
            'description' => 'The id of the tournament for which to retrieve the participants.',
            'source' => array('param' => 'tid'),
            'optional' => FALSE,
          ),
        ),
      ),
    ),
    'tournament_match_list' => array(
      'index' => array(
        'file' => array('type' => 'inc', 'module' => 'tournament_services', 'name' => 'tournament_services_resource'),
        'help' => 'Retrieves tournament data',
        'callback' => '_tournament_match_list_resource_retrieve',
        'access callback' => 'user_is_logged_in',
        'args' => array(
          array(
            'name' => 'tid',
            'type' => 'int',
            'description' => 'The id of the tournament for which to retrieve the match list.',
            'source' => array('param' => 'tid'),
            'optional' => FALSE,
          ),
          array(
            'name' => 'status',
            'type' => 'string',
            'description' => 'The status of the matches sought. I.e. "active" or "finished".',
            'source' => array('param' => 'status'),
            'optional' => TRUE,
          ),
        ),
      ),
    ),
  );
}

/**
 * Get details about a given tournament
 *
 * @param $nid
 *   Number. Tournament node ID
 * @return
 *   The tournament object
 */
function _tournament_details_resource_retrieve($nid) {
  $tournament = node_load($nid);

  // If no such node exists, return error
  if($tournament === FALSE){
    return services_error(t('There is no tournament with ID @nid.', array('@nid' => $nid)), 404);
  }

  // If node is NOT a tournament, return error
  if(tournament_supported_type($tournament->type) === FALSE){
    return services_error(t('Node with nid @nid is not a supported tournament type.', array('@nid' => $nid)), 404);
  }

  // Allow custom modules to hook in before delivering
  module_invoke_all('tournament_service', 'retrieve', 'detail', $tournament);
  return $tournament;
}

/**
 * Get a participant list from a given tournament
 *
 * @param $nid
 *   Number. Tournament node ID
 * @return
 *   The tournament participant list
 */
function _tournament_participants_resource_retrieve($nid) {
  $tournament = node_load($nid);

  // If no such node exists, return error
  if($tournament === FALSE){
    return services_error(t('There is no tournament with ID @nid.', array('@nid' => $nid)), 404);
  }

  // If node is NOT a tournament, return error
  if(tournament_supported_type($tournament->type) === FALSE){
    return services_error(t('Node with nid @nid is not a supported tournament type.', array('@nid' => $nid)), 404);
  }

  $participants = tournament_participants_data($tournament);

  // Allow custom modules to hook in before delivering
  module_invoke_all('tournament_service', 'retrieve', 'participant', $participants);
  return $participants;
}

/**
 * Get a match list for a given tournament
 *
 * An example request might look like
 *
 * http://domain/tournament/tournament_match_list?tid=6&status=active
 *
 * Which would return all active matches for tournament with nid = 6
 *
 * @param $nid
 *   Number. Tournament ID
 * @param $ststus
 *   Status of match (active or finished)
 * @return
 *   The tournament match list
 */
function _tournament_match_list_resource_retrieve($nid, $status = 'active') {

  // Only allow "active" or "finished" statuses
  if($status != 'active' && $status != 'finished'){
    return services_error(t('Status @status cannot be used.  Use "active" or "finished"', array('@status' => $status)), 404);
  }

  $tournament = node_load($nid);

  // If no such node exists, return error
  if($tournament === FALSE){
    return services_error(t('There is no tournament with ID @nid.', array('@nid' => $nid)), 404);
  }

  // If node is NOT a tournament, return error
  if(tournament_supported_type($tournament->type) === FALSE){
    return services_error(t('Node with nid @nid is not a supported tournament type.', array('@nid' => $nid)), 404);
  }

  $matches = match_list($tournament, $status);

  // Allow custom modules to hook in before delivering
  module_invoke_all('tournament_service', 'retrieve', 'match', $matches);
  return $matches;
}



