<?php
/**
 *  通过curl的方式获取网页上面的图片,
 *  应该通过cli的方式执行本文件
 *    @name:       image.php
 *    @author:     unasm<1264310280@qq.com>
 *    @since :     2014-07-19 00:14:29
 */
class Image {
    /**
     * 根据指定的url获取对应的图片
     */
    function getData($url){
        $header[] = "Accept: image/gif, image/x-bitmap, image/jpeg, image/pjpeg";
        $header[] = 'Connection: Keep-Alive';
        $header[] = 'Content-type: application/x-www-form-urlencoded;charset=UTF-8';

        $curl = curl_init();

        curl_setopt($curl , CURLOPT_URL, $url);
        //curl_setopt($curl , CURLOPT_RETURNTRANSFER , 1);
        curl_setopt($curl , CURLOPT_SSL_VERIFYPEER, false);
        curl_setopt($curl , CURLOPT_CUSTOMREQUEST,'GET');

        $userAgent ='Mozilla/5.0 (X11; Linux x86_64) AppleWebit/537.36 ()HTML, like Gecko) Ubuntu Chromium/34.0.1847.116 Chrome/34.0.1847.116 Safari/537.36';
        curl_setopt($curl , CURLOPT_USERAGENT , $userAgent);
        curl_setopt($curl , CURLOPT_HTTPHEADER , $header);
        ob_start();
        curl_exec($curl);
        $opt = ob_get_contents();
        ob_end_clean();
        curl_close($curl);
        return $opt;
    }
    /**
     * 解析HTML 第二种方案
     *
     * @return array
     * @author <doujiamin@qq.com>
     */
    public function parseHTML2 ($url)
    {
        $html = file_get_html($url);
        $div = $html->find("div[id = 'gallery-view-content']");
        var_dump($div);
        //echo $div;
    }
    /**
     * 解析html文档，获取对应的href链接
     */
    public function parseHTML ($URL)
    {
        include "HtmlParserModel.php";
        $html = file_get_contents($URL);
        $parser = new HtmlParserModel();
        $parser->parseStr($html);
        $div = $parser->find("div#gallery-view-content");
        $cnt = 0;
        foreach ($div[0]->child  as $node ) {
            if(is_array($node->attribute) && array_key_exists("href" , $node->attribute)){
                if(($cnt % 3) === 0 ){
                    $this->getImage("http://i.imgbox.com" . $node->attribute['href'] . ".jpg" , $cnt . '.jpg');
                }
                $cnt++;
            }
        }
    }
    /**
     * @param binary    $data  要保存的图片二进制数据
     * @param string    $name   图片的名字
     */
    function saveImg($data , $name){
        $file = fopen($name , "w") or die("can't open file");
        fwrite($file, $data);
        fclose($file);
    }
    function getImage($URL , $name = -1){
        if($name === -1){
            $this->saveImg($this->getData($URL) , basename($URL));
        }else{
            $this->saveImg($this->getData($URL) , $name);
        }
    }
    /**
     * 从字符流中读取图片img的地址
     *
     * @param   string  $str    包含了image信息的dom str
     * @return array
     */
    public  function getImgUrl ($domStr)
    {
        preg_match_all("/\<img\s+src\s*\=\s*[\'|\"]([^\'\"\>]+)[\'|\"]\s*\\\\?\s*\>/",$domStr , $matches);
        return $matches[1];
    }
    public function __construct()
    {
        $this->getImgUrl("<p><img src = 'http://i.imgaa.com/201405/29/7f1de29e6da19d22b51c68001e7e0e54.jpg'>  sdf
            <img src='http://i.imgaa.com/2014/05/29/7f1de29e6da19d22b51c68001e7e0e54.jpg'></p>");
    }
}
$image = new Image();
//$image->parseHTML("http://i.imgbox.com/5ktjnOJ1.jpg");
//$image->parseHTML("http://imgbox.com/g/UaL0aW4cQH");
//$image->parseHTML("./getImage.html");
//$image->getImage("http://c4.mangafiles.com/Files/Images/140/101335/imanhua_003.png");
//$image->getImage("http://www.w3school.com.cn/i/site_photoref.jpg");
?>
