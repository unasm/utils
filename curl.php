<?php
/**
 *    @name:       ./curl.php
 *    @author:     unasm<1264310280@qq.com>
 *    @since :     2014-07-20 14:36:06
 */
function curl2($url , $post){
    $curl = curl_init();
    //curl_setopt($curl , CURLOPT_RETURNTRANSFER , 1);
    //curl_setopt($curl , CURLOPT_SSL_VERIFYPEER, false);
    //curl_setopt($curl , CURLOPT_CUSTOMREQUEST,'POST');

    //$userAgent ='Mozilla/5.0 (X11; Linux x86_64) AppleWebit/537.36 ()HTML, like Gecko) Ubuntu Chromium/34.0.1847.116 Chrome/34.0.1847.116 Safari/537.36';
    //curl_setopt($curl , CURLOPT_USERAGENT , $userAgent);
    curl_setopt($curl , CURLOPT_RETURNTRANSFER , 1);
    curl_setopt($curl , CURLOPT_POST, true);

    curl_setopt($curl , CURLOPT_URL, $url);
    //curl_setopt($curl , CURLOPT_HTTPHEADER , $header);
    curl_setopt($curl , CURLOPT_POSTFIELDS , $post);
    curl_setopt($curl , CURLOPT_BINARYTRANSFER , true);
    $data = curl_exec($curl);
    curl_close($curl);
    echo $data;
}
$Post['file'] = "@/var/www/psb.jpg;type=image/jpeg";
$Post['name'] = "test";
//curl2("./upload.php" , $Post);
function execUpload($url,$post_data){

 //   $file = '/doucment/Readme.txt';
    $ch = curl_init();
    /*
    $post_data = array(
        'loginfield' => 'username',
        'username' => 'ybb',
        'password' => '123456',
        'file' => '@d:usrwwwtranslatedocumentReadme.txt'
    );
     */
    //$header = "Content-type: multipart/form-data";
    curl_setopt($ch ,CURLOPT_HTTPHEADER , $header);
    //curl_setopt($ch, CURLOPT_HEADER, false);
    //启用时会发送一个常规的POST请求，类型为：application/x-www-form-urlencoded，就像表单提交的一样。
    curl_setopt($ch, CURLOPT_POST, true);
    curl_setopt($ch,CURLOPT_BINARYTRANSFER,true);
    curl_setopt($ch, CURLOPT_POSTFIELDS,$post_data);
    curl_setopt($ch, CURLOPT_URL, $url);
    $info= curl_exec($ch);
    curl_close($ch);
    echo $info;
    //print_r($info);
}
execUpload("http://127.0.0.3:8080/utils/upload.php" , $Post);
?>
