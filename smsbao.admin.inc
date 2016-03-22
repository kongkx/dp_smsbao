<?php

function smsbao_settings() {
  $form['smsbao_username'] = array(
    '#title' => t('SMSbao Username'),
    '#type' => 'textfield',
    '#default_value' => variable_get('smsbao_username', ''),
  );
  $form['smsbao_password'] = array(
    '#title' => 'password',
    '#type' => 'password',
    '#default_value' => variable_get('smsbao_password', ''),
  );
  $form['smsbao_template'] = array(
    '#title' => 'template',
    '#type' => 'textfield',
    '#default_value' => variable_get('smsbao_template', '[kongkx]您的短信验证码是%s'),
  );
  $form['smsbao_valid_time'] = array(
    '#title' => t('valid time'),
    '#type' => 'textfield',
    '#default_value' => variable_get('smsbao_valid_time', '5'),
    '#description' => t('sms code valid period. unit: min')
  );
  $form['smsbao_debug'] = array(
    '#title' => 'debug for front end',
    '#type' => 'checkbox',
    '#default_value' => variable_get('smsbao_debug', '')
  );
  return system_settings_form($form);
}


/**
 * Validation for the administrative settings form.
 *
 * @param form
 *   An associative array containing the structure of the form.
 * @param form_state
 *   A keyed array containing the current state of the form.
 */
function smsbao_settings_validate($form, &$form_state) {
  if (empty($form_state['values']['smsbao_username'])) {
    $form_state['values']['smsbao_password'] = '';
  }
  elseif (empty($form_state['values']['smsbao_password'])) {
    unset($form_state['values']['smsbao_password']);
  }
}