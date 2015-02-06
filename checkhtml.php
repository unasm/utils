<?php
/*************************************************************************
 * File Name :    file2.php
 * Author    :    unasm
 * Mail      :    unasm@sina.cn
 ************************************************************************/
define("DEBUG" , false);
class HtmlCheck{
	static $file  = './test.html'	;
	//static $file  = './doc.html'	;
	static $stack = array();
	static $lineNum = 0;
	public function __construct()
	{
		$fp = fopen(self::$file, 'r') or die('open failed');
		while(!feof($fp)){
			$line = trim(fgets($fp));
			self::$lineNum++;
			$this->getLine($line);
			//$this->getLine('asdf<style>sad</style>sdf<a>');
		}
		echo "yes, end of file\n";
	}

	/**
	 * 读取每一行的内容
	 *
	 * @return string
	 **/
	public function getLine($line)
	{
		//获取所有的标签
		preg_match_all('/(\<[^\>]+\>)/', $line , $tags);
		foreach($tags[0] as $tag){
			$tag = trim($tag);
			if(!$tag)continue;
			if(preg_match('/\/\s*\>/' , $tag ))	{
				//自闭标签,不处理
				continue;
			} elseif (preg_match("/\<\s*\/([\w]+)[\s\>]+/", $tag, $tagName)){
				//闭合标签
				if(DEBUG){
					var_dump($tag);
					echo "pop\n";
					sleep(1);
					continue;
				}
				$end = trim($tagName[1]);
				if(count(self::$stack) === 0){
					echo $line . "\n";
					echo self::$lineNum . "\n";
					echo "out of stack";
					die;
				}
				$node = array_pop(self::$stack);
				if($end === $node['tag']){
					var_dump(array('tag' => $end , 'num' => self::$lineNum));
					var_dump($node);
					echo "compared \n\n\n";
					sleep(1);
				} else {
					var_dump(array('tag' => $end , 'num' => self::$lineNum));
					var_dump($node);
					echo $line . "\n";
					echo "is not the same\n\n";
					die;
				}
			} elseif (preg_match('/\<\s*(\w+)[\s|\>]+/' , $tag , $tagName)){
				//开启标签
				if(DEBUG){
					var_dump($tag);
					echo "inter\n";
					sleep(1);
					continue;
				}	
				$struct['tag'] = trim($tagName[1]);
				$struct['num'] = self::$lineNum;
				array_push(self::$stack, $struct);
			} else {
				var_dump($line);
				die("nothing")	;
			}
		}
	}
}
new HtmlCheck();
