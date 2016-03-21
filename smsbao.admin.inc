<?php

function smsbao_settings() {
  $form['smsbao_username'] = array(
    '#title' => t('SMSbao Username'),
    '#type' => 'textfield',
    '#default_value' => variable_get('smsbao_username', ''),
    '#required' => TRUE,
  );
  $form['smsbao_password'] = array(
    '#title' => 'password',
    '#type' => 'textfield',
    '#default_value' => variable_get('smsbao_password', ''),
    '#required' => TRUE,
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



function smsbao_test() {
  $form['#action'] = "/smsbao/test_validate";
  $form['phone'] = array(
    '#title' => t('Phone'),
    '#type' => 'textfield',
    '#default_value' => '',
    '#required' => TRUE,
  );
  $form['code'] = array(
    '#title' => t('Code'),
    '#type' => 'smsbao_field',
    '#required' => TRUE,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'submit'
  );


//  $form['another'] = array(
//    '#title' => t('Another'),
//    '#type' => 'textfield',
//    '#default_value' => '',
//    '#theme' => array('smsbao_custom')
//  );
  return $form;
}