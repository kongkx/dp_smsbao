(function($)  {
    jQuery().ready(function() {
        console.log('smsbao js loaded');
        $('.btn-smsbao').click(function(e) {
            e.preventDefault();
            console.log('button clicked');
            var button = e.target || e.srcElement;
            var form = button.form;
            var formID = form.elements['form_id'].value;
            var phone = $(form).find('.for_smsbao')[0].value.trim();
            if (phone == 0) {
                alert("请输入手机号码");
                return;
            } else if (! /^\d{11}$/.test(phone)) {
                alert("请输入11位手机号码");
                return;
            }
            var originText = button.value;
            console.log(originText);
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
                url: '/smsbao',
                content: form,
                data: {
                    'formID' : formID,
                    'phone': phone
                }
            }).done(function(data) {
                console.log(data);
                if (data.status === 'success') {
                    alert(data.message);
                }
            })
        });
    });
}(jQuery));