### Features

- custom form element "smsbao_field"
- custom webform component "smsbao_validator"
- use session to store validation code
- use "smsbao" to send sms 

### Usage

1. cd to modules folder

    ```
    git clone https://github.com/kongkx/dp_smsbao smsbao
    ```

2. enable module

    ```
    drush en smsbao -y
    ```

3. basic setup, browse to `?q=admin/config/system/smsbao` 

4. implements `theme_preprocess_smsbao_field()` to add theming class

    ```php
    // sample
    function mytheme_preporcess_smsbao_field(&variables) {
        $element = &$variables['element'];
        $element['#smsbao_field_attributes']['group_class'][]='input-form-group';
        $element['#smsbao_field_attributes']['extra_button_class'][] = 'btn btn-smsbao';
        $element['#smsbao_field_attributes']['class'][] = 'form-control';
    }
    ```


### Todo

- add message log
- add test form to module configuration page
- generalize page callback
- add the ability to attach custom js

### Others

Order your sms service: [smsbao index](http://www.smsbao.com)