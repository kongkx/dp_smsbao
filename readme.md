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


### Todo

- add message log
- add test form to module configuration page

### Others

Order your sms service: [smsbao index](http://www.smsbao.com)