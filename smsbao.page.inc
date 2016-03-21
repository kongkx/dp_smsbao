<?php
function smsbao_callback() {

  $smsbao_debug = variable_get('smsbao_debug');
  $smsbao_username = variable_get('smsbao_username');
  $smsbao_password = hash('md5', variable_get('smsbao_password'));
  $smsbao_valid_time = variable_get('smsbao_valid_time');
  $valid_time_string = "有效期为".$smsbao_valid_time."分钟";
  $smsbao_template = variable_get('smsbao_template', '[kongkx]您的短信验证码是%s');



  $phone = $_GET['phone'] ? trim($_GET['phone']) : 0000;
  $formID = $_GET['formID'] ? trim($_GET['formID']) : exit('no proper arguments');


  $code = get_sms_code($formID);
  $content = urlencode(sprintf($smsbao_template, $code). $valid_time_string);

  $url_template = "http://api.smsbao.com/sms?u=%s&p=%s&m=%u&c=%s";

  if ($smsbao_debug) {
    $result = array(
      'status' => 'success',
      'message' => '验证码('.$code.')发送成功,请查收.',
      'formID' => $_GET['formID'],
      'phone' => $phone,
      'content' => sprintf($smsbao_template, $code)
    );
  } else {
    $url = sprintf($url_template, $smsbao_username, $smsbao_password, $phone, $content);
    $return = file_get_contents($url);
    switch($return) {
      case '0':
        $result = array(
          'status' => 'success',
          'message' => '验证码发送成功,请查收'
        );
        break;
      case '51':
        $result = array(
          'status' => 'failed',
          'message' => '验证码发送失败, 手机号码不正确'
        );
        break;
      default:
        $result = array(
          'status' => 'failed',
          'message' => '验证码发送失败,请联系网站客服'
        );
    }
  }

  drupal_json_output($result);
  drupal_exit();
}

function sms_code_validate($formID, $code) {
  return $code == get_valid_sms_code($formID);
}

function get_valid_sms_code($formID) {
  $sessionName = _getSessionName($formID);
  if ( isset($_SESSION[$sessionName]) && $_SESSION[$sessionName] && $_SESSION[$sessionName]['timestamp'] > time()) {
    return $_SESSION[$sessionName]['code'];
  } else {
    return null;
  }
}

function get_sms_code($formID, $length = 6) {

  if ($code = get_valid_sms_code($formID)) {
    return $code;
  } else {
    $code = init_sms_code($formID, $length);
    return $code;
  }
}

function init_sms_code($formID, $length) {
  $code = _generate_number($length);
  $sessionName = _getSessionName($formID);
  $valid_time = variable_get('smsbao_valid_time');
  $_SESSION[$sessionName] = array(
    'code' => $code,
    'timestamp' => time() + $valid_time * 60
  );
  return $code;
}

function destroy_sms_code($formID)  {
  $sessionName = _getSessionName($formID);
  unset($_SESSION[$sessionName]);
}

function _generate_number($length = 6) {
  return rand(pow(10, ($length-1)), pow(10, $length) -1 );
}

function _getSessionName($formID) {
  return 'smsbao_code-'.$formID;
}