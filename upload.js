/**
 *    @name:       ./upload.js
 *    @author:     unasm<1264310280@qq.com>
 *    @since :     2014-08-03 16:33:52
 */
file.onchange = function(event){
    event = event || window.event;
    console.log("sdfa");
    var xml = new XMLHttpRequest();
    xml.onreadystatechange = function (event) {
        event = event || window.event;
        console.log(event);
        if(xml.readyState === 4 && xml.status === 200){
            var doc = xml.responseText;
            console.log(doc);
        }
    }
    xml.open("POST" , "http://127.0.0.3:8080/utils/upload.php");
    var data = new FormData('formTab');
    //console.log(document.forms.namedItem('formTab'));
    var data = new FormData(document.forms.namedItem('formTab'));
    console.log(data);
    xml.send(new FormData(document.forms.namedItem('formTab')));
    //xml.send(new FormData('formTab'));
    event.preventDefault();
}
