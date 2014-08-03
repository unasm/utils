<?php
/**
*    @name:       ./curl.php
*    @author:     unasm<1264310280@qq.com>
*    @since :     2014-07-20 14:36:06
*/
function curl2($url , $post){
    $curl = curl_init();
    curl_setopt($curl , CURLOPT_URL, $url);
    //curl_setopt($curl , CURLOPT_RETURNTRANSFER , 1);
    curl_setopt($curl , CURLOPT_SSL_VERIFYPEER, false);
    curl_setopt($curl , CURLOPT_CUSTOMREQUEST,'POST');

    $userAgent ='Mozilla/5.0 (X11; Linux x86_64) AppleWebit/537.36 ()HTML, like Gecko) Ubuntu Chromium/34.0.1847.116 Chrome/34.0.1847.116 Safari/537.36';
    curl_setopt($curl , CURLOPT_USERAGENT , $userAgent);
    curl_setopt($curl , CURLOPT_RETURNTRANSFER , 1);
    curl_setopt($curl , CURLOPT_POST, 1);
    //curl_setopt($curl , CURLOPT_HTTPHEADER , $header);
    curl_setopt($curl , CURLOPT_POSTFIELDS , $post);
    $data = curl_exec($curl);
    curl_close($curl);
    echo $data;
}
?>
