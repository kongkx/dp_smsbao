(function($)  {
    jQuery().ready(function() {
        console.log('smsbao js loaded');
        $('.smsbao-getcode').click(function(e) {
            e.preventDefault();

            var button = e.target || e.srcElement;
            var form = button.form;
            var formID = form.elements['form_id'].value;
            var phone = form.elements[button.getAttribute('data-binding-field')].value.trim();
            if (phone == 0) {
                alert("请输入手机号码");
                return;
            } else if (! /^\d{11}$/.test(phone)) {
                alert("请输入11位手机号码");
                return;
            }
            var originText = button.value;
            button.setAttribute('disabled', 'disabled');
            CountDown(button, 60);
            function CountDown(element, total) {
                if (total>0) {
                    element.value = originText + "(" + total + "s)";
                    setTimeout(function() {
                        CountDown(element, total-1)
                    }, 1000)
                } else {
                    element.value = originText;
                    element.removeAttribute('disabled');
                }
            }

            $.ajax({
                url: '/',
                content: form,
                data: {
                    'q': 'smsbao',
                    'formID' : formID,
                    'phone': phone
                }
            }).done(function(data) {
                console.log(data);
                alert(data.message);
            })
        });
    });
}(jQuery));