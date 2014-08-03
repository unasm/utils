<?php
/**
*    @name:       upload.php
*    @author:     unasm<1264310280@qq.com>
*    @since :     2014-08-03 14:26:27
*/
/**
 * 上传的
 */
function upload($name = 'file')
{
    $file = $_FILES[$name];
    $flag = 0;
    if($_FILES[$name]['error']){
        $flag = "Error: " . $_FILES[$name]['error'];
    }elseif($_FILES[$name]['size'] > 2 * 1024 * 1024){
        $flag = "Error: 超过了最大的文件限制";
    }else{
        $mark = move_uploaded_file($_FILES[$name]['tmp_name'] , "./" . $_FILES[$name]['name']);
        if($mark){
            $flag = "上传成功";
        }else{
            $flag = "上传失败";
        }
    }
    /* elseif(($_FILES[$name]["type"] != "image/gif") && ($_FILES[$name]["type"] != "image/jpeg")&& ($_FILES[$name]["type"] != "image/pjpeg")){
        $flag = "Error: 文件类型不对";
    }
     */
    echo $flag;
}
upload();
?>
