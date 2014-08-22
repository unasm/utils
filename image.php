<?php
/**
 *  通过curl的方式获取网页上面的图片,
 *  应该通过cli的方式执行本文件
 *    @name:       image.php
 *    @author:     unasm<1264310280@qq.com>
 *    @since :     2014-07-19 00:14:29
 *    @todo 进行整站的扫描，从index页面进行开始，
 *    @todo 练习php中的C扩展，保存已经获取过的链接不再进行解析
 *    @todo curl多个进程和单个进程的阻塞
 */
class Image {
    const SIZE = 200;
    /**
     * 根据指定的url获取对应的图片
     * @todo 通过添加多个curl进行图片的获取
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
    protected function saveImg($data , $name){
        $file = fopen($name , "w") or die("can't open file");
        fwrite($file, $data);
        fclose($file);
        return $name;

    }
    public function getImage($URL , $name = -1){
        $file = "";
        if($name === -1){
            $file = $this->saveImg($this->getData($URL) , basename($URL));
        }else{
            $file = $this->saveImg($this->getData($URL) , $name);
        }
    }
    /**
     * 在下载完毕一个图片之后，检验图片是不是符合我们的规格要求，以免错下
     *
     * @return void
     */
    public  function checkAfterDownLoad ($name)
    {
        $info = getimagesize($name);
        if($info && $info[1] > self::SIZE && $info[0] > self::SIZE){
            echo "yes";
        }else{
            if(unlink($name)){
                echo "delete success";
            }else{
                echo "delete failed";
            }
        }
    }
    /**
     * 从 字符/dom 流中读取图片img的地址
     *
     * @param   string  $str    包含了image信息的dom str
     * @return array
     */
    public  function getImgUrl ($domStr)
    {
        preg_match_all("/\<img\s+src\s*\=\s*[\'|\"]([^\'\"\>]+)[\'|\"][^>]*\>/",$domStr , $matches);
        return $this->checkImgUrl($matches[1]);
    }

    /**
     * 检验图片before Download
     */
    protected function checkImgUrl($arr , $prefix = "jpg")
    {
        $ret = array();
        foreach($arr as $img){
            $pfx = substr($img ,strlen($img) - 3);
            if(substr($img , 0, 4) === "http" && $pfx === $prefix){
                $ret[]= $img;
            }
        }
        return $ret;
    }
    public function __construct()
    {
        /*
        $domStr = $this->getData("http://www.caoqun5566.com/bbs/index.php?app=forum&act=threadview&tid=361598");
        $imgs = $this->getImgUrl($domStr);
        foreach($imgs as $img){
            $this->getImage($img);
        }
         */
        $this->checkAfterDownLoad("/var/www/html/utils/psb.jpg");
    }
}
$image = new Image();
//$image->parseHTML("http://i.imgbox.com/5ktjnOJ1.jpg");
//$image->parseHTML("http://imgbox.com/g/UaL0aW4cQH");
//$image->parseHTML("./getImage.html");
//$image->getImage("http://c4.mangafiles.com/Files/Images/140/101335/imanhua_003.png");
//$image->getImage("http://www.w3school.com.cn/i/site_photoref.jpg");
?>
