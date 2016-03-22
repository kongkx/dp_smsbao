<?php

/**
 * Implements _webform_defaults_component()
 */
function _webform_defaults_smsbao() {
  return array(
    'name'      => '',
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
      'binding_field'              => ''
    ),
  );
}


function _webform_edit_smsbao($component) {
  $form = array();
  $form['extra']['binding_field'] = array(
    '#type' => 'textfield',
    '#title' => t('binding field'),
    '#default_value' => $component['extra']['binding_field'],
    '#description' => t("The name of the input element where the phone number come from"),
    '#required' => TRUE,
  );
  $form['display']['width'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Width'),
    '#default_value' => $component['extra']['width'],
    '#description'   => t('Width of the textfield.') . ' ' . t('Leaving blank will use the default size.'),
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
    '#type'             => 'smsbao_field',
    //    '#default_value'    => $filter ? webform_replace_tokens($component['value'], NULL, NULL, NULL, TRUE) : $component['value'],
    '#attributes'       => $component['extra']['attributes'],
    '#theme_wrappers'   => array( 'webform_element' ),
    '#description'      => $filter ? webform_filter_descriptions($component['extra']['description']) : $component['extra']['description'],
    '#required'         => $component['required'],
    '#title'            => $filter ? webform_filter_xss($component['name']) : $component['name'],
    '#title_display'    => $component['extra']['title_display'] ? $component['extra']['title_display'] : 'before',
    '#weight'           => $component['weight'],
    '#translatable'     => array( 'title', 'description' ),
    '#smsbao_field_attributes' => array(
      'class' => array('form-text'),
      'group_class' => array('group'),
      'extra_button_class' => array('smsbao-getcode'),
    )
  );
  // add bind-field to attributes, formatted as webform element naming style
  $form_item['#smsbao_field_attributes']['binding_field'] = 'submitted['.$component['extra']['binding_field'].']';
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

