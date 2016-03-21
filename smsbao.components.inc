<?php

/**
 * Implements _webform_defaults_component()
 */
function _webform_defaults_smsbao() {
  return array(
    'name'      => '',
    'form_key'  => 'smsbao',
    'required'  => 1,
    'mandatory' => 0,
    'pid'       => 0,
    'weight'    => 0,
    'value'     => '',
    'extra'     => array(
      'title_display'              => 0,
      'width'                      => '',
      'disabled'                   => FALSE,
      'private'                    => FALSE,
      'attributes'                 => array(),
      'description'                => '',
      'placeholder'                => '',
      'binding_field'              => 'phone'
    ),
  );
}


function _webform_edit_smsbao($component) {
  $form = array();
  $form['extra']['binding_field'] = array(
    '#type' => 'smsbao_field',
    '#title' => t('binding field'),
    '#default_value' => $component['extra']['binding_field'],
    '#required' => TRUE,
  );
  $form['value'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Default value'),
    '#default_value' => $component['value'],
    '#description'   => t('The default value of the field.') . theme('webform_token_help'),
    '#size'          => 60,
    '#maxlength'     => 1024,
    '#weight'        => 0,
  );
  $form['display']['width'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Width'),
    '#default_value' => $component['extra']['width'],
    '#description'   => t('Width of the textfield.') . ' ' . t('Leaving blank will use the default size.'),
    '#size'          => 5,
    '#maxlength'     => 10,
    '#weight'        => 0,
    '#parents'       => array( 'extra', 'width' ),
  );
  $form['display']['placeholder'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Placeholder'),
    '#default_value' => $component['extra']['placeholder'],
    '#description'   => t('The text will be shown in the field until the user starts entering a value.'),
    '#weight'        => 1,
    '#parents'       => array( 'extra', 'placeholder' ),
  );
  $form['display']['disabled'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Disabled'),
    '#return_value'  => 1,
    '#description'   => t('Make this field non-editable. Useful for setting an unchangeable default value.'),
    '#weight'        => 11,
    '#default_value' => $component['extra']['disabled'],
    '#parents'       => array( 'extra', 'disabled' ),
  );
  return $form;
}

/**
 * Implements _webform_render_component().
 */
function _webform_render_smsbao($component, $value = NULL, $filter = TRUE) {
  $form_item = array(
    '#type'             => 'textfield',
    //    '#default_value'    => $filter ? webform_replace_tokens($component['value'], NULL, NULL, NULL, TRUE) : $component['value'],
    '#default_value'    => $filter ? _webform_filter_values($component['value']) : $component['value'],
    '#attributes'       => $component['extra']['attributes'],
    '#theme_wrappers'   => array( 'webform_element' ),
    //    '#description'      => $filter ? webform_filter_descriptions($component['extra']['description']) : $component['extra']['description'],
    '#description'      => $filter ? _webform_filter_descriptions($component['extra']['description']) : $component['extra']['description'],
//    '#element_validate' => array( 'webform_validate_smsbao' ), // todo how to define webform_validate_smsbao
    '#maxlength'        => '',
    '#required'         => $component['required'],
    '#size'             => 17,
    //    '#title'            => $filter ? webform_filter_xss($component['name']) : $component['name'],
    '#title'            => $filter ? _webform_filter_xss($component['name']) : $component['name'],
    '#title_display'    => $component['extra']['title_display'] ? $component['extra']['title_display'] : 'before',
    '#weight'           => $component['weight'],
    '#translatable'     => array( 'title', 'description' ),
  );
  if ($component['required']) {
    $form_item['#attributes']['required'] = 'required';
  }
  if (isset( $value )) {
    $form_item['#default_value'] = $value[0];
  }
  // Change the 'width' option to the correct 'size' option.
  if ($component['extra']['width'] > 0) {
    $form_item['#size'] = $component['extra']['width'];
  }
  // Show the placeholder text if used.
  if ($component['extra']['placeholder']) {
    $form_item['#attributes']['placeholder'] = $component['extra']['placeholder'];
  }
  if ($component['extra']['disabled']) {
    if ($filter) {
      $form_item['#attributes']['readonly'] = 'readonly';
    }
    else {
      $form_item['#disabled'] = TRUE;
    }
  }
  if (isset( $value[0] )) {
    $form_item['#default_value'] = $value[0];
  }
  return $form_item;
}

/**
 *
 */
function _webform_submit_smsbao() {

}

/**
 * Implements _webform_theme_component().
 */
function _webform_theme_smsbao() {
  return array( 'webform_display_smsbaofield' => array( 'render element' => 'element' ) );
}


/**
 * Format the output of data for this component.
 */
function theme_webform_display_smsbaofield($variables) {
  $element = $variables['element'];
  $plain_value = check_plain($element['#value']);
  if ($element['#format'] == 'html') {
    //Use smarter detection if available for formatting the output
    $is_mobile_device = module_exists('mobile_tools') ? mobile_tools_is_mobile_device() : strpos($_SERVER['HTTP_USER_AGENT'], 'iPhone') !== FALSE || strpos($_SERVER['HTTP_USER_AGENT'], 'Android') !== FALSE;
    $value = ( $is_mobile_device ) ? '<a href="tel:' . $plain_value . '">' . $plain_value . '</a>' : $plain_value;
  }
  else {
    $value = $plain_value;
  }
  return $value;
}

