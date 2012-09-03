<?php

/**
 * @file
 * Admin page callback file for the tournament module.
 */

/**
 * Form builder; Configure tournament settings for this site.
 *
 * @ingroup forms
 * @see system_settings_form()
 */
function tournament_admin_settings() {
  $form = array();

  $form['tournament_title_lock'] = array(
    '#type' => 'checkbox',
    '#title' => t('Node title cannot be changed after a tournament has been started'),
    '#default_value' => variable_get('tournament_title_lock', 0),
  );
  $form['tournament_user_picture'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show user pictures on user tournament participant lists'),
    '#default_value' => variable_get('tournament_user_picture', 0),
  );

  return system_settings_form($form);
}
