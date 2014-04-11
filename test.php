<?php
/**
*    @name:       test.php
*    @author:     unasm<1264310280@qq.com>
*    @since :     2014-04-10 09:20:50
*/
require "Converter.php";
require "Reader.php";
require "Writer.php";
class test{
    public function index()
    {
        echo "tesing";
    }
    function testConverter()
    {
        $helper = new Converter();
        $arr = $helper->CsvToArray("sd,sda");
        var_dump($arr);
        $arr = $helper->ArrayToCsv(['ab' , 'cd']);
        var_dump($arr);
    }
    /**
     * 测试Writer这个文件
     */
    public function testWriter ()
    {
        $write = new Writer("write.csv");
        $arr = [
            ["asd,,sdfa" , "sd\"" ] ,
            ["ad , sda" , "ds323"],
            ["ad \"s中国" , "ds323"],
            ["adsd\'sda" , "ds323"],
            ["adsd's\nda" , "ds323"],
            ["adsd'sda" , "ds323"]
        ];
        $con = new Deyi\CSVUtils\Converter();
        //$con->CsvToArray("算法sdfssdf的");
        //return;
        $pos = 5;
        $this->format($arr[$pos]);
        $csv = $con->ArrayToCsv($arr[$pos]);
        $write->setMeta($csv);
        /*
        foreach ($arr  as $value) {
            $csv = $con->ArrayToCsv($value);
            $write->appendRow($csv);
        }
         */
        if(!$this->compare('format.csv' , 'write.csv')){
            echo "生成csv不相同";
        } else {
            echo "相同";
        }
    }
    /**
     * 对比两个文件的相同
     */
    public function compare($fileName1 , $fileName2)
    {
        $file1 = trim(file_get_contents($fileName1 , true));
        $file2 = trim(file_get_contents($fileName2 , true));
        if($file1 === $file2){
            return true;
        } else{
            return false;
        }
    }
    /**
     * 格式化正规的csv
     */
    PROTECTED function format (&$arr )
    {
        $file = fopen("format.csv" , "w" , true);
        fputcsv($file , $arr);
        /*
        foreach ($arr as $lineArr ) {
            fputcsv($file , $lineArr);
        }
         */
        fclose($file);
    }
    /**
     * 测试Reader这个文件
     */
    public function testReader()
    {
    }
}
$file = new test();
$file->testWriter();
//$file->index();
?>
