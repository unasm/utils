/*************************************************************************
 * 一个利用nodejs和websocket做的简单的聊天室
 * File Name :  node.js
 * Author  :      unasm
 * Mail :         unasm@sina.cn
 * Last_Modified: 2015-03-20 22:49:23
 ************************************************************************/
//客户端js代码,node.js
$(document).ready(function(){
	var url = 'ws://127.0.0.1:8010/';
	var w = new WebSocket(url);
	w.onopen = function(){
		$('#chat-box').append('已经连接到服务器<br/>');
	}
	w.onmessage = function(e){
		var msg = e.data;
		console.log(msg);
		console.log(e);
		$('#chat-box').append(msg);
	}
	function send(){
		var talk = $("#talk").val();
		var nike = $('#nike').val();
		if(talk && nike){
			w.send("<strong style = 'color:red'>" + nike  + ":</strong>" + talk);
		}else {
			alert('failed first');
		}
	}
	$("#btn").click(function(){
		send()	;
	})
})
////////////////////////////////////////////////////////////////////////////////////
//浏览器代码
<!DOCTYPE html> 
<html lang = "zh-cn">
<head>
	<meta http-equiv="content-type" content="text/html; charset=utf-8">

	<title>test</title>
	<script type="text/javascript" charset="utf-8" src = "http://jiamin.tmp.joy.sina.com.cn/js/joyb/lib/jquery.js"></script>
	<script type="text/javascript" charset="utf-8" src = "./node.js"></script>
</head>
<body>
	<div id="chat-box">
		昵称：
		<input type="text" name="nike" id = "nike"><br/>
		内容：
		<input type="text" name="talk" id = "talk"><br/>
		<input type="button" name="btn" value="提交" id = "btn">
	</div>
</body>
</html>
////////////////////////////////////////////////////////////////////////////////////
//服务器代码
console.log("Server started");
var connects = new Array();
var WebSocketServer = require('ws').Server
, wss = new WebSocketServer({port: 8010});
wss.on('connection', function(ws) {
	connects.push(ws);
	ws.on('message', function(msg) {
		//ws.send(msg);
		for(var i = 0,len = connects.length; i < len;i++){
			if(connects[i] !== ws)	{
				connects[i].send(msg)	;
			}
		}
	});
	console.log("connection");
});
