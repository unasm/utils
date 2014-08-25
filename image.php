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

    //最小允许的图片大小
    const SIZE = 200;


    //网站的根目录
    const BASE = "http://www.caoqun5566.com/bbs/";

    //重新获取数据的次数
    const reGet = 3;
    var $imgPath;
    // image 保存路径
    /**
     * 根据指定的url获取对应的图片
     * @todo 通过添加多个curl进行图片的获取
     */
    protected function getData($url){

        $curl = curl_init();
        /*
        $header[] = "Accept: image/gif, image/x-bitmap, image/jpeg, image/pjpeg";
        $header[] = 'Connection: Keep-Alive';
        $header[] = 'Content-type: application/x-www-form-urlencoded;charset=UTF-8';

        curl_setopt($curl , CURLOPT_URL, $url);
        //curl_setopt($curl , CURLOPT_RETURNTRANSFER , 1);
        curl_setopt($curl , CURLOPT_SSL_VERIFYPEER, false);
        curl_setopt($curl , CURLOPT_CUSTOMREQUEST,'GET');

        $userAgent ='Mozilla/5.0 (X11; Linux x86_64) AppleWebit/537.36 ()HTML, like Gecko) Ubuntu Chromium/34.0.1847.116 Chrome/34.0.1847.116 Safari/537.36';
        curl_setopt($curl , CURLOPT_USERAGENT , $userAgent);
        curl_setopt($curl , CURLOPT_HTTPHEADER , $header);
         */
        $this->curlOptSet($curl);
        ob_start();
        curl_exec($curl);
        $opt = false;
        if(curl_errno($curl)){
            echo "curl error: " . curl_error($curl);
        }else{
            $opt = ob_get_contents();
        }
        ob_end_clean();
        curl_close($curl);
        return $opt;
    }

    /**
     * 对curl进行初始化
     *
     * @return void
     */
    protected function curlOptSet (&$curl)
    {
        static $header = array();
        $header[] = "Accept: image/gif, image/x-bitmap, image/jpeg, image/pjpeg";
        $header[] = 'Connection: Keep-Alive';
        $header[] = 'Content-type: application/x-www-form-urlencoded;charset=UTF-8';
        curl_setopt($curl , CURLOPT_URL, $url);
        //curl_setopt($curl , CURLOPT_RETURNTRANSFER , 1);
        curl_setopt($curl , CURLOPT_SSL_VERIFYPEER, false);
        curl_setopt($curl , CURLOPT_CUSTOMREQUEST,'GET');

        $userAgent ='Mozilla/5.0 (X11; Linux x86_64) AppleWebit/537.36 ()HTML, like Gecko) Ubuntu Chromium/34.0.1847.116 Chrome/34.0.1847.116 Safari/537.36';
        curl_setopt($curl , CURLOPT_USERAGENT , $userAgent);
        curl_setopt($curl , CURLOPT_HTTPHEADER , $header);
    }
    /**
     * 多线程，获取数据
     *
     * @return array
     */
    protected function curl_multi($urls)
    {
        $ch = array();
        $mh = curl_multi_init();
        foreach($urls as $url){
            $tmp = curl_init();
            curl_setopt($tmp, CURLOPT_URL , $url);
            $this->curlOptSet($tmp);
            $ch[] = $tmp;
            curl_multi_add_handle($mh , $tmp);
        }
        do{
            $mrc = curl_multi_exec($mh , $active);
        }while($mrc === CURLM_CALL_MULTI_PERFORM);
        while($active && $mrc === CURLM_OK){
            if(curl_multi_select($mh) != -1){
                do{
                    $mrc = curl_multi_exec($mh , $active);
                }while($active == CURLM_CALL_MULTI_PERFORM);
            }
        }
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
    /**
    * 根据对应的url获取图片
    * @todo 增加检验，和重新获取的功能
    */
    public function getImage($URL , $name = -1){
        $file = "";
        if($name === -1){
            $name = basename($URL);
        }
        $name = $this->imgPath . $name ;
        if(file_exists($name)){
            echo "url为:{$URL}且name为{$name}已经存在了";
            return;
        }
        for($i = 0;$i < self::reGet;$i++){
            $data = trim($this->getData($URL , $name));
            //如果得到了html文档，则不再保存，返回错误
            if(preg_match('/.*\<\/html\>$/' , $data)){
                echo "非img文件\n";
                return false;
            }
            if($data){
                $this->saveImg($data , $name);
                $this->checkAfterDownLoad($name);
                return true;
            }
        }
        return false;
    }
    /**
     * 在下载完毕一个图片之后，检验图片是不是符合我们的规格要求，以免错下
     *
     */
    protected  function checkAfterDownLoad ($name)
    {
        $info = getimagesize($name);
        if($info && $info[1] > self::SIZE && $info[0] > self::SIZE){
            return true;
        }else{
            if(unlink($name)){
                return false;
            }else{
                throw new Exception("无法删除不合适的下载文件" . $name);
            }
        }
    }
    /**
     * 从 字符/dom 流中读取图片img的地址
     *
     * @param   string  $str    包含了image信息的dom str
     * @return array
     */
    protected  function getImgUrl ($domStr)
    {
        preg_match_all("/\<img[^>]+src\s*\=\s*[\'|\"]([^\'\"\>]+)[\'|\"][^>]*\>/",$domStr , $matches);
        $imgs =  $this->checkImgUrl($matches[1]);
        //$imgs = array("http://www.masterporn.me/images/fv8hpmfdm0rahfe53q6g.jpg");
        var_dump($imgs);
        foreach($imgs as $img){
            if(!$this->getImage($img)){
                //error("{$img}没有保存成功");
                echo ("{$img}没有保存成功");
            }
        }
    }
    /**
     * 检验图片before Download
     */
    protected function checkImgUrl($arr , $prefix = "jpg")
    {
        $ret = array();
        foreach($arr as $img){

            $pfx = substr($img ,strlen($img) - 3);
            if($pfx !== $prefix)continue;
            if(substr($img , 0, 4) === "http"){
                $ret[]= $img;
            }else if(substr($img, 0,2) === './'){
                //有可能是相对路径，虽然这个案例中是不应该的，但是考虑到实用性，应该添加相对路径
                $ret[] = self::BASE . $img;
            }
        }
        return $ret;
    }

    /**
     * 检查href是不是曾经搜索过
     *
     * @return boolen
     * @todo 通过其他的算法优化性能
     */
    protected   function isHrefBeen($href)
    {
        static $been = array();
        foreach($been as $url){
            if($url === $href)return false;
        }
        $been[] = $href;
        //echo "没有到过";
        return true;
    }
    /**
     * 根据根据对应的url获取并解析dom，提取其中的a link ,根据其中的base 和是否曾经检验过来作为是否进入并且抓取的依据
     * @param string $url ,需要进入，并且进行解析得到子url的url
     * @param int    $deep 搜索的深度，以免发生无法控制的事情
     * @return array
     */
    public  function getHtmlByUrl($url , $deep)
    {
        if(!$deep)return ;
        //$data = $this->getData($url);
        $data = file_get_contents($url ,FILE_USE_INCLUDE_PATH);
        //获取其中的图片
        $this->getImgUrl($data);
        preg_match_all("/\<a\s+href\s*\=\s*[\'|\"]([^\'\"\>]+)[\'|\"][^>]*\>/",$data, $matches);
        $len = strlen(self::BASE);
        //$toSea = array();
        //只保留base站以内的链接
        foreach($matches[1] as $href){
            //echo $href . "<br/>\n";
            if(substr($href , 0 ,7) != 'http://'){
                //检验是不是相对路径
                $href = self::BASE .  $href;
            }else if(!($this->checkHref($href , $len) && $this->isHrefBeen($href))){
                //不是相对路径情况下，站外href不考虑
                //echo "{$href}是不可以的";
                continue;
            }
            $this->getHtmlByUrl($href , $deep -1);
        }
    }

    /**
     * 检验是不是想要的站内链接
     *
     * @return boolen
     */
    protected function checkHref ($href , $len)
    {
        //其实这样不一定合适，因为二级域名也可以啊
        if(substr($href , 0 , $len) === self::BASE){
            //echo "相同域名";
            return true;
        }
        return false;
    }
    public function __construct()
    {
        $this->imgPath = rtrim(dirname(__FILE__)  , '/') . "/image/";
        $flag = $this->getHtmlByUrl("http://www.caoqun5566.com/bbs/", 2);
    }
}
$image = new Image();
//$image->parseHTML("http://i.imgbox.com/5ktjnOJ1.jpg");
//$image->parseHTML("http://imgbox.com/g/UaL0aW4cQH");
//$image->parseHTML("./getImage.html");
//$image->getImage("http://c4.mangafiles.com/Files/Images/140/101335/imanhua_003.png");
//$image->getImage("http://www.w3school.com.cn/i/site_photoref.jpg");
?>
